#ifndef  PROJECT_H
#define PROJECT_H

#include <vector>
#include <string>


struct InfoContact {
    std::string phone_number;
    std::string name;
    std::string email;
};

void EditContact(std::vector<InfoContact>& contacts);
void DeleteContacts(std::vector<InfoContact>& contacts);
void AddInformation(std::vector<InfoContact>& contacts);
void ManageContactsMenu(std::vector<InfoContact>& contacts);

void PrintContacts(const std::vector<InfoContact>& contacts);

void Search(std::vector <InfoContact>& contacts);

void SortByName(std::vector <InfoContact>& contacts);

void WritingToFile(const std::vector<InfoContact>& contacts, const std::string& filename);
void OutputFromFile(std::vector<InfoContact>& contacts, std::string filename);
void FileOperationsMenu(std::vector <InfoContact>& contacts);

bool IsValidPhoneNumber(const std::string& phone);


bool IsValidEmail(const std::string& email);

int GetIndex(const std::vector<InfoContact>& contacts);
int GetEditChoice();
#endif