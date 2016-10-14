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
bool computeColors ( vector<vector<int> > people, vector<int>& output);

int main(){
    int num_vertices;
    vector<vector<int> > graph;
    graph = readFile("Graph1.txt",num_vertices);
    ofstream output;
    output.open ("output.txt");
    output << "Jordan McGregor - 10052770\nVictor Mimo - xxxxxxxx\n";

    vector<int> tables(graph.size(),-1);
    if(computeColors(graph,tables)){
        output << "Possible to sit everyone at two tables.\n\nSitting at the Red Table:\n";
        for(int i = 1; i < tables.size(); i++){
            if(tables[i]==0){output<<i<<endl;}
        }
        output<<"\nSitting at the Blue Table:\n";
        for(int i = 1; i < tables.size(); i++){
            if(tables[i]==1){output<<i<<endl;}
        }
    }
    else output << "Not possible to seat everyone at two tables"<<endl;

    return 0;
}

/*
Function that checks if a graph can be seated at two tables
Inputs: 2d vector of vertices and its neighbours
Outputs: Table number/colour for each person and if graph can be seated at two tables
*/
bool computeColors(vector<vector<int> > people, vector<int>& output){
    vector<bool> seen (people.size(),0); //vector to keep track of which verticies have been visited
    vector<int> nextVertex(1,1); //vector to act as a stack of which verticies to visit next
    seen[1] = true;
    output[1] = 0;
    bool seetingError = false; //keep track if consntraints don't allow a person to sit at either table
    while(nextVertex.size()!=0&&!seetingError){//loop through all vertecies
        int current = nextVertex.back(); //set current vertex to back
        nextVertex.pop_back();
        for(int i = 0; i < people[current].size(); i++){ //loop through all neighbours
            if(seen[people[current][i]]==false) // if haven't seen before
                nextVertex.push_back(people[current][i]);
                seen[people[current][i]]=true;
            if(output[current]==0){ // if current vertex is at table 0
                if(output[people[current][i]]==-1){output[people[current][i]]=1;}
                else if(output[people[current][i]]==1){}
                else if(output[people[current][i]]==0){seetingError = true;} //assigning a neighbour to a different table
                else cout<<"error"<<endl;
            }
            else if(output[current]==1){ //if current vertex is at table 1
                if(output[people[current][i]]==-1){output[people[current][i]]=0;}
                else if(output[people[current][i]]==0){}
                else if(output[people[current][i]]==1){seetingError = true;} //assigning a neighbour to a different table
                else cout<<"error"<<endl;
            }
        }
    }
    return (!seetingError)? true: false;

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
