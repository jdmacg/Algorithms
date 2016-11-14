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

#define THROW(exceptionClass, message) throw exceptionClass(__FILE__, __LINE__, (message) )

struct project{
    int projectNum;
    int startWeek;
    int length;
    int value;
};

bool projectComparataor(project p1, project p2)
{
    return (p1.startWeek + p1.length < p2.startWeek + p2.length);
}

vector<project > readFile(const string fileName, int & numWeeks);
vector<int> projectSelection (const vector<project> projects, const int numWeeks);
void projectSelectionHelper(const vector<project> & projects,vector<vector<int> > & values);


int main()
{
    int numWeeks;
    vector<project> projects = readFile("Qooqle_Projects_4.txt",numWeeks);

    sort(projects.begin(),projects.end(),projectComparataor);
    //for (int i = 0; i < projects.size(); i++){
        //for(int j = 0; j < projects.at(i).size(); j++){
            //cout<<i<<" ";
            //cout<<projects.at(i).projectNum<<" "<<projects.at(i).startWeek<<projects.at(i).length<<projects.at(i).value;
        //}
        //cout << endl;
    //}
    cout <<numWeeks;
    projectSelection(projects,numWeeks);
    return 0;
}

vector<int> projectSelection (const vector<project> projects, const int numWeeks){
    vector<vector<int> > values;
    for(int i = 0; i < projects.size(); i++){
        vector<int> weeks (numWeeks,-1);
        values.push_back(weeks);
    }
    cout <<" "<<projects.size()-1<<" "<<numWeeks<<endl;
    cout <<values.size()<<values.at(0).size();
    projectSelectionHelper(projects,values);
    cout <<endl;
    //for(int i = 0; i < values.size(); i ++){
        //for (int j = 0; j < values.at(i).size(); j++){
            cout << "value: " << values.at(values.size()-1).at(values.at(1).size()-1)<< " ";
        //}
       // cout << endl;
    //}
    vector<int> selection;
    return selection;
}

void projectSelectionHelper(const vector<project> & projects,vector<vector<int> > & values){
    for(int projectIter = 0; projectIter < values.size(); projectIter++){
        for(int weekIter = 0; weekIter < values.at(projectIter).size(); weekIter++){
            int projectEndingWeek = projects.at(projectIter).startWeek+projects.at(projectIter).length-2;
            if(projectIter == 0){
                if(projectEndingWeek<=weekIter){
                    values.at(projectIter).at(weekIter)=projects.at(projectIter).value;
                }
                else
                    values.at(projectIter).at(weekIter)= 0;
            }
            else{//project index greater than 0
                if(projectEndingWeek==weekIter){
                    int dontSelectProject =  values.at(projectIter-1).at(weekIter);
                    int selectProject=0;
                    if(projects.at(projectIter).startWeek-2 < 0){
                        selectProject+=projects.at(projectIter).value;
                    }
                    else
                        selectProject =  values.at(projectIter).at(projects.at(projectIter).startWeek-2)+projects.at(projectIter).value;
                    values.at(projectIter).at(weekIter) = max(dontSelectProject,selectProject);
                }
                else if(projectEndingWeek<weekIter)
                    values.at(projectIter).at(weekIter)= values.at(projectIter).at(weekIter-1);
                else
                    values.at(projectIter).at(weekIter)= values.at(projectIter-1).at(weekIter);
            }
        }
    }
}

/*
int projectSelectionHelper(const vector<project> & projects, vector<vector<int> > & currValues, const int projectIndex, const int weekIndex){
    if(currValues.at(projectIndex).at(weekIndex)==-1){
        int projectEndingWeek = projects.at(projectIndex).startWeek+projects.at(projectIndex).length-2;
        if(projectIndex == 0){
            if(projectEndingWeek<=weekIndex){
                return projects.at(projectIndex).value;
            }
            else
                return 0;
        }
        else{
            if(projectEndingWeek==weekIndex){
                int dontSelectProject =  projectSelectionHelper(projects,currValues,projectIndex-1,weekIndex);
                int selectProject = projectSelectionHelper(projects,currValues,projectIndex,projects.at(projectIndex).startWeek-2)+projects.at(projectIndex).value;
                return max(dontSelectProject,selectProject);
            }
            else if(projectEndingWeek<weekIndex)
                return projectSelectionHelper(projects,currValues,projectIndex,weekIndex-1);//return max(projectSelectionHelper(projects,currValues,projectIndex,weekIndex-1),projectSelectionHelper(projects,currValues,projectIndex-1,weekIndex));
            else
                return projectSelectionHelper(projects,currValues,projectIndex-1,weekIndex);
        }

    }
    else return currValues.at(projectIndex).at(weekIndex);
}
*/

/*
Function to read in n number of projects. Each project has a start date, length, and value.
Inputs: file name as a string, reference to an integer of number of weeks
Outputs: 2d vector of projects
*/
vector<project> readFile (string fileName, int & numWeeks){
    ifstream file(fileName);
    string line;
    int numProjects = 0;
    getline(file,line);
    istringstream iss(line);
    iss >> numWeeks;
    vector<project> arr;
    getline(file,line);
    iss.clear();
    iss.str(line);
    iss >> numProjects;
    int x =0;
    while (getline(file, line))
    {
        iss.clear();
        iss.str(line);
        int val1,val2,val3,val;
        project aProject;
        if(!(iss >> aProject.projectNum>>aProject.startWeek>>aProject.length>>aProject.value)){cout << "error"<<endl;}
        arr.push_back(aProject);
        x++;
    }
    return arr;
}
