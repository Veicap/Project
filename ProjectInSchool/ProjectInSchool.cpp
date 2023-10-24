#include <iostream>
#include <string>
#include <fstream>
#include <vector>

const std::string FILE_NAME = "group.txt";
struct Group {
    std::string nameOfGroup;
    std::vector<std::string> nameOfStudentList;
    struct ProjectDateSubmitOfGroup {
        std::string projectNeedSubmitList;
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
                group = new Group();
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
    void InputProjectInformation() {
        int numberOfProject;
        std::cout << "Enter number of project: "; std::cin >> numberOfProject;
        for (int i = 1; i <= numberOfProject; i++) {
            std::cin.ignore();
            std::cout << "(*) Enter information of project" << i << "\n";
            project->nameOfProject = "Project " + std::to_string(i);
            std::cout << "(+) Enter a short description about project: ";
            std::getline(std::cin, project->shortDescriptionOfProject);
            std::cout << "(-) Enter a submission deadline of project\n";
            std::cout << "(+) Enter day of deadLine: "; std::cin >> project->dayOfDeadLine;
            std::cout << "(+) Enter month of deadLine: "; std::cin >> project->monthOfDeadLine;
            std::cout << "(+) Enter year of deadLine: "; std::cin >> project->yearOfDeadLine;
            AppendProject(project);
            project = new Project();
        }
    }
    void DisplayInfProject() {
        if (listOfProject.empty()) {
            std::cout << "Not found any project\n";
        }
        for (const auto project : listOfProject) {
            std::cout << "Name of Project: " << project->nameOfProject << "\n";
            std::cout << "Description of project: " << project->shortDescriptionOfProject << "\n";
            std::cout << "Submission Deadline of project: " << project->dayOfDeadLine << "/" << project->monthOfDeadLine << "/" << project->yearOfDeadLine << "\n";
        }
    }
    void AppendProject(Project* project) {
        listOfProject.push_back(project);
    }
    //Option 3
    Group::ProjectDateSubmitOfGroup* projectDateSubmitGroup = new Group::ProjectDateSubmitOfGroup();
    void UpDateTimeToSubmit() {
        for (const auto group : listOfGroup) {
            if (listOfProject.empty()) {
                std::cout << "You do not enter information for project, please do option2 first\n";
                break;
            }
            std::cout << "Enter submission's " << group->nameOfGroup << "\n";
            for (const auto project : listOfProject) {
                projectDateSubmitGroup->projectNeedSubmitList = project->nameOfProject;
                std::cout << "(-) " << project->nameOfProject << ":\n";
                std::cout << "(+) Enter day of submit: "; std::cin >> projectDateSubmitGroup->dayOfSubmit;
                std::cout << "(+) Enter month of submit: "; std::cin >> projectDateSubmitGroup->monthOfSubmit;
                std::cout << "(+) Enter year of submit: "; std::cin >> projectDateSubmitGroup->yearOfSubmit;
                group->projectDateSubmitOfGroupList.push_back(projectDateSubmitGroup);
                projectDateSubmitGroup = new Group::ProjectDateSubmitOfGroup();
            }
        }
    }
    void DisplayDateOfSubmit() {
        for (const auto group : listOfGroup) {
            std::cout << "Submission of " << group->nameOfGroup << "\n";
            for (const auto dateSubmitProject : group->projectDateSubmitOfGroupList) {
                std::cout << "(-)" << dateSubmitProject->projectNeedSubmitList << ":\n";
                std::cout << "(+) Date submit: " << dateSubmitProject->dayOfSubmit << "/" << dateSubmitProject->monthOfSubmit << "/" << dateSubmitProject->yearOfSubmit << "\n";
            }
        }
    }
    // Option 4
    std::string stateOnTime = "On Time";
    std::string stateLate = "Not submited yet";
    void HandleStateMent() {

        for (const auto group : listOfGroup) {
            for (const auto dateSubmitProjectOfGroup : group->projectDateSubmitOfGroupList) {
                for (const auto project : listOfProject) {
                    if (project->nameOfProject == dateSubmitProjectOfGroup->projectNeedSubmitList) {
                        if ((dateSubmitProjectOfGroup->yearOfSubmit < project->yearOfDeadLine
                            || (dateSubmitProjectOfGroup->yearOfSubmit == project->yearOfDeadLine
                                && dateSubmitProjectOfGroup->monthOfSubmit < project->monthOfDeadLine)
                            || (dateSubmitProjectOfGroup->yearOfSubmit == project->yearOfDeadLine
                                && dateSubmitProjectOfGroup->monthOfSubmit == project->monthOfDeadLine
                                && dateSubmitProjectOfGroup->dayOfSubmit <= project->dayOfDeadLine))) {
                            dateSubmitProjectOfGroup->statement = stateOnTime;
                        }
                        else {
                            dateSubmitProjectOfGroup->statement = stateLate;
                        }
                    }
                }

            }

        }
    }
    void DisplayStateOfProject() {
        std::cin.ignore();
        std::string nameOfProject;
        std::cout << "(+) Enter name of project: "; std::getline(std::cin, nameOfProject);
        bool isFoundName = false;
        for (const auto group : listOfGroup) {
            if (listOfProject.empty() && group->projectDateSubmitOfGroupList.empty()) {
                std::cout << "You do not update dealine or submission for project. Please go back to option 2 and 3 before do that.\n";
                break;
            }
            for (const auto dateSubmitProjectOfGroup : group->projectDateSubmitOfGroupList) {
                for (const auto project : listOfProject) {
                    if (project->nameOfProject == nameOfProject && project->nameOfProject == dateSubmitProjectOfGroup->projectNeedSubmitList) {
                        std::cout << "Sate submission " << nameOfProject << " of " << group->nameOfGroup << ": " << dateSubmitProjectOfGroup->statement << "\n";
                        isFoundName = true;
                    }
                }
            }
        }
        if (!isFoundName) {
            std::cout << nameOfProject << " dose not exist\n";
        }
    }
    void DisplayStateOfGroup() {
        std::cin.ignore();
        std::string nameOfGroup;
        std::cout << "(+) Enter name of group: "; std::getline(std::cin, nameOfGroup);
        bool isFoundName = false;
        for (const auto group : listOfGroup) {
            if (listOfProject.empty() && group->projectDateSubmitOfGroupList.empty()) {
                std::cout << "You do not update dealine or submission for project. Please go back to option 2 and 3 before do that.\n";
                break;
            }
            if (group->nameOfGroup == nameOfGroup) {
                isFoundName = true;
                for (const auto dateSubmitProjectOfGroup : group->projectDateSubmitOfGroupList) {
                    for (const auto project : listOfProject) {
                        if (project->nameOfProject == dateSubmitProjectOfGroup->projectNeedSubmitList) {
                            std::cout << "Sate submission " << project->nameOfProject << " of " << group->nameOfGroup << ": " << dateSubmitProjectOfGroup->statement << "\n";
                        }
                    }
                }
            }

        }
        if (!isFoundName) {
            std::cout << nameOfGroup << " dose not exist\n";
        }
    }
    // Option 5

    // Option 6

    void DisplayGroupSubmit() {
        std::cout << "Groups submit on time: ";
        for (const auto group : listOfGroup) {
            for (const auto inforDateSubmitOfGroup : group->projectDateSubmitOfGroupList) {
                if (inforDateSubmitOfGroup->statement == stateOnTime) {
                    std::cout << group->nameOfGroup << ", ";
                }
            }
        }
        std::cout << "\n";
    }
    void DisplayGroupNotSubmit() {
        std::cout << "Groups submit do not submit: ";
        for (const auto group : listOfGroup) {
            for (const auto inforDateSubmitOfGroup : group->projectDateSubmitOfGroupList) {
                if (inforDateSubmitOfGroup->statement == stateLate) {
                    std::cout << group->nameOfGroup << ", ";
                }
            }
        }
        std::cout << "\n";
    }

};
int main()
{
    HandleData* handleData = new HandleData();
    handleData->ReadFile();
    std::string option;
    while (true) {
        std::cout << "(1) Group Information\n"
            << "(2) Project deadline declaration\n"
            << "(3) Project Date Submitssion\n"
            << "(4) Statistic\n"
            << "(6) Find groups do not complete or submit on time\n";

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
        else if (option == "2") {
            std::string optionOf2;
            std::cout << "(1) Input Projects Information\n"
                << "(2) Display Information of Groups\n";
            std::cout << "Enter your option: ";
            std::cin >> optionOf2;
            if (optionOf2 == "1") {
                handleData->InputProjectInformation();
            }
            else if (optionOf2 == "2") {
                handleData->DisplayInfProject();
            }
        }
        else if (option == "3") {
            std::string optionOf3;
            std::cout << "(1) Input Project Date Submit's Groups\n"
                << "(2) Display Information of Date Submit's Groups\n";
            std::cout << "Enter your option: ";
            std::cin >> optionOf3;
            if (optionOf3 == "1") {
                handleData->UpDateTimeToSubmit();
            }
            else if (optionOf3 == "2") {
                handleData->DisplayDateOfSubmit();
            }
        }
        else if (option == "4") {
            std::string optionOf4;
            std::cout << "(1) Display Statement of project\n"
                << "(2) Display Information of Date Submit's Groups\n";
            std::cout << "Enter your option: ";
            std::cin >> optionOf4;
            handleData->HandleStateMent();
            if (optionOf4 == "1") {
                handleData->DisplayStateOfProject();
            }
            else if (optionOf4 == "2") {
                handleData->DisplayStateOfGroup();
            }
        }
        else if (option == "6") {
            std::string optionOf6;
            std::cout << "(1) Display Groups submit on time\n"
                << "(2) Display Groups submit late\n";
            std::cout << "Enter your option: ";
            std::cin >> optionOf6;
            handleData->HandleStateMent();
            if (optionOf6 == "1") {
                handleData->DisplayGroupSubmit();
            }
            else if (optionOf6 == "2") {
                handleData->DisplayGroupNotSubmit();
            }
        }
    }
}

