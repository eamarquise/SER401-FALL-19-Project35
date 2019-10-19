#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
#include <forward_list>
#include <ctime>
#include <chrono>
#include <set>

using namespace std::chrono;

template <class ForwardIt>
    void quicksort(ForwardIt first, ForwardIt last)
    {
        if(first==last) return;
        auto pivot = *std::next(first, std::distance(first,last)/2);
        ForwardIt middle1 = std::partition(first, last, [pivot](const auto& em){return em < pivot;});
        ForwardIt middle2 = std::partition(middle1, last,
                            [pivot](const auto& em){return !(pivot < em);});
        quicksort(first, middle1);
        quicksort(middle2, last);
}

struct Project {
    int id;
    int sponsorID;
    int type; // 0 = Online | 1 = Ground | 2 = Hybrid
    int priority; // 0 = Not Required | 1 = Required
    int classID;
    int skills();
    std::string teamMembers();
    int compatibilityRating;
};

int getRandomInt(int min, int max){
	int value = rand() % (max-min +1) + min;
	return value;
}

int getUniqueInt(int min, int max){
    static std::vector<int> generatedValues;
    int value = getRandomInt(min, max);
    while (std::find(generatedValues.begin(), generatedValues.end(), value) != generatedValues.end()) {
        value = getRandomInt(min, max);
    }
    return value;
}

int main()
{
    auto start = high_resolution_clock::now();

    int MIN_PROJECTS = 1;
    int MAX_PROJECTS = 100;
    int NUM_PROJECT_ATTRIBUTES = 5;
    int NUM_SKILLS = 7;
    int NUM_STUDENTS = 500;
    int TEAM_SIZE = 5;

    std::vector<Project> projectPool(MAX_PROJECTS);
    std::vector<int> projectTypeArray(MAX_PROJECTS);
    Project project;

    for (int i = 0; i < MAX_PROJECTS; i++)
    {
        project.id = MIN_PROJECTS + i;
        project.sponsorID = getUniqueInt(1, MAX_PROJECTS);
        project.type = getRandomInt(0, 2);
        project.priority = getRandomInt(0, 1);

        projectPool[i] = project;
        projectTypeArray[i] = project.type;
    }

    std::cout << "Project ID" << " ";
    std::cout << "Sponsor ID" << " ";
    std::cout << "Type" << " ";
    std::cout << "Priority" << " ";
    std::cout << std::endl;

    for (int i = 0; i < MAX_PROJECTS; i++)
    {
        std::cout << projectPool[i].id << " ";
        std::cout << projectPool[i].sponsorID << " ";
        std::cout << projectPool[i].type << " ";
        std::cout << projectPool[i].priority << " ";
        std::cout << std::endl;
    }

    auto it = std::partition(projectPool.begin(), projectPool.end(), [](Project p){
        return p.type == 0;
    });



    std::cout << "Begin partitioned Project Pool:" << std::endl;

    for (int i = 0; i < MAX_PROJECTS; i++)
    {
        std::cout << projectPool[i].id << " ";
        std::cout << projectPool[i].sponsorID << " ";
        std::cout << projectPool[i].type << " ";
        std::cout << projectPool[i].priority << " ";
        std::cout << std::endl;
    }

    return 0;
}
