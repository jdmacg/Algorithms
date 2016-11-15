/*
Programming to solve the calculate the maximum value possible from project selection. This program uses dynamic programming to solve the problem
of weighted project selection.
Inputs: command line argument of name of text file of projects where each project has a start date, length and value
Output: programs writes to a text file the projects selected to maximize value, and the maximum value
*/
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

struct project{
    int projectNum;
    int startWeek;
    int length;
    int endingWeek;
    int value;
};

vector<project > readFile(const string fileName, int & numWeeks);
vector<int> projectSelection (const vector<project> projects, const int numWeeks);
void projectSelectionHelper(const vector<project> & projects,vector<vector<int> > & values);
vector<int> findProjectsSelected (const vector<vector<int> > values, const vector<project> projects);

//function used to sort projects by ending week
bool projectComparataor(project p1, project p2)
{
    return (p1.startWeek + p1.length < p2.startWeek + p2.length);
}

int main(int argc, char *argv[])
{
    string fileName = argv[1];
    int numWeeks;
    vector<project> projects = readFile(fileName,numWeeks);
    sort(projects.begin(),projects.end(),projectComparataor);
    vector<int> solution = projectSelection(projects,numWeeks);
    ofstream output;
    fileName.insert(fileName.size()-4,"_output");
    output.open (fileName);
    output << "Total income earned: " << solution.back()<<"\nProjects selected: ";
    for(int i = solution.size()-2; i >= 0; i--){
        output << solution.at(i)<<" ";
    }
    return 0;
}

/*
function that calculates th
Input: vector of projects, number of weeks to consider
Output: vector of the projects selected to produce the maximum value, last integer is the maximum value possible from the projects
*/
vector<int> projectSelection (const vector<project> projects, const int numWeeks){
    vector<vector<int> > values;
    for(int i = 0; i < projects.size(); i++){
        vector<int> weeks (numWeeks+1,-1);
        values.push_back(weeks);
    }
    projectSelectionHelper(projects,values);
  //  for(int i = 0; i < values.size(); i ++){
      //  for (int j = 0; j < values.at(i).size(); j++){
        //    cout << values.at(i).at(j)<<" ";
       // }
      // cout << endl;
    //}

    vector<int> selection = findProjectsSelected(values,projects);
    selection.push_back(values.at(values.size()-1).at(numWeeks));
    return selection;
}


/*
Function to generate 2d vector of maximim value gained by selecting projects. Table is built up by week only considering adding one project at a time.
Inputs: vector of projects, initialized vector of values
Output: 2d vector of values. the maximum value possible is held in the entry that considers all projects and all weeks.
*/
void projectSelectionHelper(const vector<project> & projects,vector<vector<int> > & values){
    for(int weekIter = 0; weekIter < values.at(0).size(); weekIter++){
        int projectEndingWeek = projects.at(0).startWeek+projects.at(0).length-1;
        if(projectEndingWeek<=weekIter){
            values.at(0).at(weekIter)=projects.at(0).value;
        }
        else
            values.at(0).at(weekIter)= 0;
    }
    for(int projectIter = 1; projectIter < values.size(); projectIter++){
        for(int weekIter = 0; weekIter < values.at(projectIter).size(); weekIter++){
            int projectEndingWeek = projects.at(projectIter).startWeek+projects.at(projectIter).length-1;
            if(projectEndingWeek==weekIter){
                int dontSelectProject =  values.at(projectIter-1).at(weekIter);
                int selectProject =  values.at(projectIter).at(projects.at(projectIter).startWeek-1)+projects.at(projectIter).value;
                values.at(projectIter).at(weekIter) = max(dontSelectProject,selectProject);
            }
            else if(projectEndingWeek<weekIter)
                values.at(projectIter).at(weekIter)= values.at(projectIter).at(weekIter-1);
            else
                values.at(projectIter).at(weekIter)= values.at(projectIter-1).at(weekIter);
        }
    }
}

/*
Function to find which projects were selected to produce maximum value
Inputs: 2d vector of values from dynamic programming solution of project selection, vector of projects
Output: vector of projects selected by project number
*/
vector<int> findProjectsSelected (const vector<vector<int> > values, const vector<project> projects){
    int lastProject = values.size() - 1;
    int projectIterator = lastProject;
    vector<int> selectedProjects;
    for(int weekIterator = values.at(lastProject).size()-1; weekIterator> 0; weekIterator--){
        if(values.at(lastProject).at(weekIterator)>values.at(lastProject).at(weekIterator-1)){
            bool projectFound=false;
            while(!projectFound){
                int projectLength = projects.at(projectIterator).length;
                if (projectLength<=weekIterator){
                    int valueGainedFromProject = projects.at(projectIterator).value+values.at(lastProject).at(weekIterator-projectLength);
                    if(valueGainedFromProject==values.at(lastProject).at(weekIterator)){
                        projectFound = true;
                        selectedProjects.push_back(projects.at(projectIterator).projectNum);
                        weekIterator = projects.at(projectIterator).startWeek;
                    }
                }
                projectIterator--;
            }
        }
    }
    return selectedProjects;
}

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
