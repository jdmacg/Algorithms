#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <sstream>
#include <fstream>
#include <climits>
#include <algorithm>
#include <random>

using namespace std;

vector<vector<int> > readFile(string fileName, int & numWeeks);

int main()
{
    cout <<"hello";
    int weeks;
    vector<vector<int> > projects = readFile("Qooqle_Projects_1.txt",weeks);
    cout << "size: " << projects.size()<< " ";
    /*for (int i = 0; i < projects.size(); i++){
        for(int j = 0; j < projects.at(i).size(); j++){
            cout<<i<<" "<<j<<": ";
            cout<<projects.at(i).at(j)<<" "<<endl;
        }
        cout << endl;
    }*/
    return 0;
}

/*
Function to read in n number of projects. Each project has a start date, ending date, and value.
Inputs: file name as a string, reference to an integer of number of weeks
Outputs: 2d vector of projects
*/
vector<vector<int> > readFile (string fileName, int & numWeeks){
    ifstream file(fileName);
    string line;
    int numProjects = 0;
    getline(file,line);
    istringstream iss(line);
    iss >> numProjects;
    vector<vector<int> > arr;
    getline(file,line);
    iss.clear();
    iss.str(line);
    iss >> numWeeks;

    int x =0;
    while (getline(file, line))
    {
        vector<int> lineValues;
        iss.clear();
        iss.str(line);
        int value;
        for(int i = 0; i < 4; i ++){//loop for times for the number of data points per project
             if(!(iss >> value)){cout << "error"<<endl;}
             lineValues.push_back(value);
        }
        arr.push_back(lineValues);
        x++;
    }
    return arr;
}
