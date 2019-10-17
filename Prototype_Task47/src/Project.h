#ifndef PROJECT_H
#define PROJECT_H

#include <string>

class Project
{
    public:
        Project();
        Project(std::string projID, std::string sponID, char t, int p);
        virtual ~Project();
        int calc_min_team_size(int teamSize);
        int calc_projects(int numStudents, int teamSize, int minTeamSize);
        int calc_projects(int numStudents, int teamSize);

    protected:

    private:

};

#endif // PROJECT_H
