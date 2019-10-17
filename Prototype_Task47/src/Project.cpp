#include "Project.h"
#include <string>
#include <math.h>

// Default constructor
Project::Project()
{
    std::string projectID = "Default Project ID";
    std::string sponsorID = "Default Sponsor ID";
    char type = 'H';
    int priority = 0;
}

// Constructor with arguments
Project::Project(std::string projID, std::string sponID, char t, int p)
{
    std::string projectID = projID;
    std::string sponsorID = sponID;
    char type = t;
    int priority = p;
}

Project::~Project()
{
    //dtor
}

// calc_min_team_size Function
// Task #36 - Cristi DeLeo
// Calculates the minimum team size.
int Project::calc_min_team_size(int teamSize){
    int minTeamSize;
    double percentFactor = 0.80; // 80%

    minTeamSize = floor(percentFactor * teamSize);

    return minTeamSize;
}

// calc_projects Function
// Task #7 - Cristi DeLeo
// Calculates the number of projects required for any given
// number of students with a specified minimum team size.
int Project::calc_projects(int numStudents, int teamSize, int minTeamSize){
    int numProjects;
    int numStudentsModTeamSize;
    int currentProjectCount;
    int numStudentsNeeded;

    numStudentsModTeamSize = numStudents % teamSize;

    if(numStudentsModTeamSize == 0) {
        numProjects = numStudents / teamSize;
    } else if (numStudentsModTeamSize >= minTeamSize) {
        numProjects = ((numStudents - numStudentsModTeamSize) / teamSize) + 1;
    } else if (numStudentsModTeamSize < minTeamSize) {
        // Calculation to determine number of projects needed when
        // more than one team will be set at the minimum team size.
        currentProjectCount = numStudents / teamSize;
        numStudentsNeeded = minTeamSize - numStudentsModTeamSize;

        // Determines whether there are enough students to evenly
        // distribute projects based on the minimum team size
        if(numStudentsNeeded > currentProjectCount){
            if(teamSize > minTeamSize){
                teamSize--;
            } else if(teamSize == minTeamSize){
                teamSize--;
                minTeamSize--;
            } else{
                // Error catch
            }
            calc_projects(numStudents, teamSize, minTeamSize);
        } else if(numStudentsNeeded <= currentProjectCount){
            numProjects = ((numStudents - numStudentsModTeamSize) / teamSize) + 1;
        }
    }

    return numProjects;
}

// calc_projects Function
// Task #7 - Cristi DeLeo
// Calculates the number of projects required for any given
// number of students.
int Project::calc_projects(int numStudents, int teamSize){
    int numProjects;
    int numStudentsModTeamSize;
    int minTeamSize;
    int currentProjectCount;
    int numStudentsNeeded;

    minTeamSize = calc_min_team_size(teamSize);

    numStudentsModTeamSize = numStudents % teamSize;

    if(numStudentsModTeamSize == 0) {
        numProjects = numStudents / teamSize;
    } else if (numStudentsModTeamSize >= minTeamSize) {
        numProjects = ((numStudents - numStudentsModTeamSize) / teamSize) + 1;
    } else if (numStudentsModTeamSize < minTeamSize) {
        // Calculation to determine number of projects needed when
        // more than one team will be set at the minimum team size.
        currentProjectCount = numStudents / teamSize;
        numStudentsNeeded = minTeamSize - numStudentsModTeamSize;

        // Determines whether there are enough students to evenly
        // distribute projects based on the minimum team size
        if(numStudentsNeeded > currentProjectCount){
            if(teamSize > minTeamSize){
                teamSize--;
            } else if(teamSize == minTeamSize){
                teamSize--;
                minTeamSize--;
            } else{
                // Error catch
            }
            calc_projects(numStudents, teamSize, minTeamSize);
        } else if(numStudentsNeeded <= currentProjectCount){
            numProjects = ((numStudents - numStudentsModTeamSize) / teamSize) + 1;
        }
    }

    return numProjects;
}
