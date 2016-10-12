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
vector <vector <int> > computeColors (int numCities, int source, int destination, vector<vector<int> > flightTimes);

int main(){
    cout << "hello" <<endl;
    int num_vertices;
    vector<vector<int> > graph;
    graph = readFile("Graph1.txt",num_vertices);
    cout << "hello" <<endl;
    cout << graph.size()<<endl;
    for(int i = 1; i <= 50; i ++){
        cout << i << ": ";
        for(int j = 0; j < graph[i].size(); j++){
            cout << graph[i][j] << " ";
        }
        cout << endl;
    }
    cout << "Jordan and Victor";
    return 0;
}


vector<vector<int> > computeBestPath (int numCities, int source, int destination, vector<vector<int> > flightTimes){
    //vector of calculated path times. INT_MAX is greatest possible int value. Assume flights do no take longer than this.
    vector<int> B(numCities+1,INT_MAX); //add one as num cities are not 0 indexed
    B[source]=0;
    vector<int> P(numCities+1,-1);//add one as num cities are not 0 indexed
    vector<int> R;
    vector<int> C(1,source);
    bool destInR = false; //is destination in R
    int index,x,y;
    while (!C.empty()&&!destInR){
        index = findSmallest(C,B);
        x = C[index];
        cout<<"x is: "<<x<<endl;
        R.push_back(x);
        C.erase(C.begin()+index);
        for(int i = 0; i < flightTimes.size(); i++){
            if (flightTimes[i][0]==x){//departure city is x
                cout<<"x:\t"<<flightTimes[i][0]<<endl;
                y=flightTimes[i][1];//destination city
                cout<<"y:\t"<<y<<endl;
                if(find(R.begin(),R.end(),y)==R.end()){//destination city is not in R
                    cout<<"Y not found in R"<<endl;
                    if(flightTimes[i][2]>B[x]){//departure time is greater than shortest time it takes to get to x
                        cout<<"departure time "<<flightTimes[i][2]<<"is greater than bx "<<B[x]<<endl;
                        if(flightTimes[i][3]<B[y]){//new shortest path is found{

                            if(B[y]==INT_MAX){//haven't seen y before
                                C.push_back(y);
                            }
                            B[y]=flightTimes[i][3];//update best path
                            P[y]=x;
                            cout<<"B[y]: "<<y<<"\t"<<B[y]<<endl;
                        }
                    }
                }
            }
        }
        if(x==destination) {destInR = true;}//exit loop
        cout<<"dest in r\t"<<destInR<<endl;
    }
    vector<vector<int> > paths;
    paths.push_back(B);
    paths.push_back(P);
    return paths;
}
*/
vector<vector<int> > readFile (string fileName, int &count){

    ifstream file(fileName);
    string line;
    getline(file,line);
    istringstream iss(line);
    iss >> count; // number of vertecies
    cout <<count<< endl;
    vector<vector<int> > arr(count+1);//not 0 indexed
    int vertex; // which vertex is being read.
    while (getline(file, line))
    {
        vector<int> neighbours;
        istringstream iss(line);
        char colon; //read in colon
        int vertex; // vertex number
        int neighbour; // holds neighbour value while reading in from file
        //douCoh.seekp(-1,douCoh.cur);
        if (!(iss >> vertex >> colon)) { cout<<"error"; break; } // expect int followed by colon
        while(iss >> neighbour){
            neighbours.push_back(neighbour);
        }
        cout << vertex <<endl;
        arr[vertex] = neighbours;
    }
    return arr;
}
