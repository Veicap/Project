#include <iostream>
#include <string>
#include <fstream>
#include <vector>

const std::string FILE_NAME = "group.txt";
struct Group {
    std::string nameOfGroup;
    std::vector<std::string> nameOfStudentList;
    struct ProjectDateSubmitOfGroup {
        std::string projectSubmitList;
        int dayOfSubmit, monthOfSubmit, yearOfSubmit;
        std::string statement;
    };
    std::vector<ProjectDateSubmitOfGroup*> projectDateSubmitOfGroupList;
};
struct Project {
    std::string nameOfProject;
    std::string shortDescriptionOfProject;
    int dayOfDeadLine;
    int monthOfDeadLine;
    int yearOfDeadLine;
};

struct HandleData {
    // Option 1:
    std::vector<Group*> listOfGroup;
    Group* group = new Group();

    void ReadFile() {

        std::ifstream groupFile(FILE_NAME);
        std::string groupInformation;
        while (std::getline(groupFile, groupInformation)) {

            if (groupInformation.find("Group") != std::string::npos) {
                if (!group->nameOfGroup.empty()) {
                    listOfGroup.push_back(group);
                }
                group = new Group(); // Create new group;
                group->nameOfGroup = groupInformation;
            }
            else {
                group->nameOfStudentList.push_back(groupInformation);
            }
        }
        if (!group->nameOfGroup.empty()) {
            listOfGroup.push_back(group);
        }

    }
    void InputInformation() {
        group = new Group();
        std::vector<std::string> nameOfStudentEnteredList;
        int numberOfGroupAdded = 0;
        std::cout << "(!)Class already have " << listOfGroup.size() << " groups." << "\n";
        while (numberOfGroupAdded <= 0) {
            std::cout << "(-)Enter number of groups in the class you want to add: "; std::cin >> numberOfGroupAdded;
            std::cout << "-------------------------------------------------------------\n";
            if (numberOfGroupAdded <= 0) {
                std::cout << "(!) You need to enter the number of added groups greater than 0 . Please re-enter\n";
            }
        }
        int numberOfGroups = numberOfGroupAdded + listOfGroup.size();
        for (int i = listOfGroup.size(); i < numberOfGroups; i++) {
            group->nameOfGroup = "Group " + std::to_string(i + 1);
            int numberOfStudentInAGroup = 0;
            std::cout << "Enter information of group " << i + 1 << "\n";
            while (numberOfStudentInAGroup <= 0) {
                std::cout << "(-)Enter number of students: "; std::cin >> numberOfStudentInAGroup;
                if (numberOfStudentInAGroup <= 0) {
                    std::cout << "(!) You need to enter the number of added students greater than 0. Please re-enter\n";
                }
            }
            std::cin.ignore();
            for (int j = 0; j < numberOfStudentInAGroup; j++) {
                std::string nameOfStudent = "";
                bool isDuplicate = false;
                do {
                    isDuplicate = false;
                    std::cout << "(-)Enter name of student number " << j + 1 << ": ";
                    std::getline(std::cin, nameOfStudent);
                    for (auto group : listOfGroup) {
                        for (auto& nameOfStudentInList : group->nameOfStudentList) {
                            if (nameOfStudentInList == nameOfStudent) {
                                isDuplicate = true;
                                std::cout << "(!)Student already have in another group. Please re-enter\n";
                                break;
                            }
                        }
                        if (isDuplicate) {
                            break;
                        }
                        
                    }
                    for (auto& nameOfStudentEntered : nameOfStudentEnteredList) {
                        if (nameOfStudentEntered == nameOfStudent) {
                            isDuplicate = true;
                            std::cout << "(!)Student already have in another group. Please re-enter\n";
                        }
                    }
                    if (!isDuplicate) {
                        group->nameOfStudentList.push_back(nameOfStudent);
                        nameOfStudentEnteredList.push_back(nameOfStudent);
                    }
                } while (isDuplicate);
            }
            std::cout << "-------------------------------------------------\n";
            listOfGroup.push_back(group);
            group = new Group();
            nameOfStudentEnteredList.clear();
        }
    }
    void SaveInformation() {
        std::ofstream groupFile(FILE_NAME);
        for (auto group : listOfGroup) {
            groupFile << group->nameOfGroup << "\n";
            for (auto& nameOfStudent : group->nameOfStudentList) {
                groupFile << nameOfStudent << "\n";
            }
        }
    }
    void DisplayData() {
        for (auto group : listOfGroup) {
            std::cout << group->nameOfGroup << ";";
            for (auto& nameOfStudent : group->nameOfStudentList) {
                std::cout << nameOfStudent << ";";
            }
            std::cout << "\n";
        }
    }
   
    //Option 2
    Project* project = new Project();
    std::vector<Project*> listOfProject;
    
    //Option 3
    Group::ProjectDateSubmitOfGroup* projectDateSubmitGroup = new Group::ProjectDateSubmitOfGroup();
    
    // Option 4
    
    // Option 5

    // Option 6

    

};
int main()
{
    HandleData* handleData = new HandleData();
    handleData->ReadFile();
    std::string option;
    while (true) {
        std::cout << "(1) Group Information\n";

        std::cout << "Enter your option: ";
        std::cin >> option;
        if (option == "1") {
            std::string optionOf1 = "";
            std::cout << "(1) Input information of groups\n"
                << "(2) Display information\n"
                << "(3) Save groups information\n";

            std::cout << "Enter your option: ";
            std::cin >> optionOf1;
            if (optionOf1 == "1") {
                handleData->InputInformation();
            }
            else if (optionOf1 == "2") {
                handleData->DisplayData();
            }
            else if (optionOf1 == "3") {
                handleData->SaveInformation();
            }
        }
        
        
    }
}

