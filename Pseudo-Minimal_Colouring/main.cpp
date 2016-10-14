#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <sstream>
#include <fstream>
#include <climits>
#include <algorithm>

using namespace std;

vector <vector <int> > readFile(string fileName, int &count); //file input
int computeColors ( vector<vector<int> > people, vector<int>& output); //assign each person to a table

struct Comparator //sorting indexes based on values in another array
{
    const vector<int> & value_vector;
    Comparator(const vector<int> & val_vec):
        value_vector(val_vec) {}
    bool operator()(int i1, int i2)
    {
        return value_vector[i1] > value_vector[i2];
    }
};

int main(){
    int num_vertices;
    vector<vector<int> > graph;
    graph = readFile("Graph4.txt",num_vertices);
    ofstream output;
    output.open ("output.txt");
    output << "Jordan McGregor - 10052770\nVictor Mimo - xxxxxxxx\n";
    vector<int> tables(graph.size(),-1);
    output << "Minimal number of tables is: ";
    output << computeColors(graph,tables);
    return 0;
}

/*
Function that finds a good seating arragement using heuristic algorithm
Inputs: vertex table colours of size people set to -1, 2d vector of vertices and its neighbours
Outputs: Table number/colour for each person and max number of tables required
*/
int computeColors(vector<vector<int> > people, vector<int>& output){
    int n = people.size();
    vector<int> degrees (people.size(), -1); // vector to store the degree of each vetex.
    for(int i = 0; i < degrees.size(); i++){//find degrees of each vertex
        degrees[i]=people[i].size();
    }
    vector<int> sortedVertices (people.size()-1);
    for(int i = 0 ; i < sortedVertices.size(); i++){ //intialize array for sorting
        sortedVertices[i]=i+1;
    }
    sort(sortedVertices.begin(), sortedVertices.end(),Comparator(degrees));
    output[sortedVertices[1]]=1; // set highest degree vertex to colour one

    for (int i = 2; i < sortedVertices.size(); i++){
        vector<bool> colourUsed (n,0);//vector used to check if a colour has already been used
        for (int j = 0; j < people[sortedVertices[i]].size(); j++){
            if(output[people[sortedVertices[i]][j]]>0){//if a colour has already been used in the vertex's neighbour
                colourUsed[output[people[sortedVertices[i]][j]]]=true;
            }
        }
        for(int k = 1; k < colourUsed.size(); k++){
            if(!colourUsed[k]){
                output[sortedVertices[i]]=k; // set the colour of the vertex to the lowest unused by neighbours
                break;
            }
        }
    }
    int highest = 1;
    for(int i = 1; i < output.size(); i++){//find highest table number/colour used
        if(output[i]>highest){highest=output[i];}
    }
    return highest;
}

//file input into a 2d vector
vector<vector<int> > readFile (string fileName, int &count){

    ifstream file(fileName);
    string line;
    getline(file,line);
    istringstream iss(line);
    iss >> count; // number of vertecies
    vector<vector<int> > arr(count+1);//not 0 indexed
    int vertex; // which vertex is being read.
    while (getline(file, line))
    {
        vector<int> neighbours;
        istringstream iss(line);
        char colon; //read in colon
        int vertex; // vertex number
        int neighbour; // holds neighbour value while reading in from file
        if (!(iss >> vertex >> colon)) { cout<<"error"; break; } // expect int followed by colon
        while(iss >> neighbour){
            neighbours.push_back(neighbour);
        }
        arr[vertex] = neighbours;
    }
    return arr;
}
