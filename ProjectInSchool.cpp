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
                    Append(group);
                }
                group = new Group(); // Create new group;
                group->nameOfGroup = groupInformation;
            }
            else {
                group->nameOfStudentList.push_back(groupInformation);
            }
        }
        if (!group->nameOfGroup.empty()) {
            Append(group);
        }

    }
    void InputInformation() {
        group = new Group();
        std::vector<std::string> nameOfStudentEnteredList;
        int numberOfGroup = 0;
        std::cout << "(!)Class already have " << listOfGroup.size() << " group. You must enter number of group larger than available number of group" << "\n";
        while (numberOfGroup < listOfGroup.size()) {
            std::cout << "(-)Enter number of group in the class: "; std::cin >> numberOfGroup;
            std::cout << "-------------------------------------------------------------\n";
            if (numberOfGroup < listOfGroup.size()) {
                std::cout << "(!) You entered number of group smaller than available number of group. Please re-enter\n";
            }
        }
        for (int i = listOfGroup.size(); i < numberOfGroup; i++) {
            group->nameOfGroup = "Group " + std::to_string(i + 1);
            int numberOfStudentInAGroup = 0;
            std::cout << "Enter information of group " << i + 1 << "\n";
            while (numberOfStudentInAGroup <= 0) {
                std::cout << "(-)Enter number of student if a group: "; std::cin >> numberOfStudentInAGroup;
            }
            std::cin.ignore();
            for (int j = 0; j < numberOfStudentInAGroup; j++) {
                std::string nameOfStudent = "";
                bool isDuplicate = true;
                while (isDuplicate) {
                    std::cout << "(-)Enter name of student number " << j + 1 << ": ";
                    int checkIsDuplicate = 0;
                    std::getline(std::cin, nameOfStudent);
                    for (auto group : listOfGroup) {
                        for (auto& nameOfStudentInList : group->nameOfStudentList) {
                            if (nameOfStudentInList == nameOfStudent) {
                                isDuplicate = true;
                                checkIsDuplicate = 1;
                                std::cout << "(!)Student already have in another group. Please re-enter\n";
                                break;
                            }
                        }
                        if (checkIsDuplicate == 1) {
                            break;
                        }
                    }
                    for (auto& nameOfStudentEntered : nameOfStudentEnteredList) {
                        if (nameOfStudentEntered == nameOfStudent) {
                            isDuplicate = true;
                            checkIsDuplicate = 1;
                            std::cout << "(!)Student already have in another group. Please re-enter\n";
                        }
                    }
                    if (checkIsDuplicate == 0) {
                        isDuplicate = false;
                    }
                    if (!isDuplicate) {
                        group->nameOfStudentList.push_back(nameOfStudent);
                        nameOfStudentEnteredList.push_back(nameOfStudent);
                    }
                }
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
    void Append(Group* group) {
        listOfGroup.push_back(group);
    }
    //Option 2
    Project* project = new Project();
    std::vector<Project*> listOfProject;
    void UpdateProjectInformation() {
        
    }
    void DisplayInfProject() {
        
    }
    void AppendProject(Project* project) {
        listOfProject.push_back(project);
    }
    //Option 3
    Group::ProjectDateSubmitOfGroup* projectDateSubmitGroup = new Group::ProjectDateSubmitOfGroup();
    void UpDateTimeToSubmit() {
        
    }
    void DisplayDateOfSubmit() {
        
    }
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

