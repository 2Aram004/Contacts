#ifndef _CONTACT_H
#define _CONTACT_H

#include <iostream>
#include <unordered_map>
#include <fstream>
#include <string>
#include <regex>

class Contact
{
public:
	Contact() noexcept;
	void start();
	~Contact() {}
	
private:
	struct Datas
	{
		std::string name;
		std::string lastname;
		std::string number;
		std::string address;
		std::string email;
	}; // Datas

	void addContact();
	void deleteContact();
	void changeUserData();
	void readAllContacts();
	void stop();
	void findContact();
	void getDatas();
	void changeInFile();
	void setMap();
	std::pair<bool, int> find(const std::string&);
	bool checkFirstLetter(char);
	bool checkNumber(const std::string&);
	bool checkEmail(const std::string&);

private:
	std::ofstream write;
	std::ifstream read;
	std::string nameOfFile;
	int idOfContact = 0;
	std::string str;
	std::string command;
	Datas userDatas;
	std::unordered_map<std::string, void(Contact::*)()> userCommand;
	std::unordered_map<int, Datas> contacts;
	std::unordered_map<std::string, void(Contact::*)(std::unordered_map<int, Datas>::iterator)> changedData;
	int changeContactNumber;
	std::string changeData;
	std::string changeContactData;
	std::string changeContactName;
};
#endif // _CONTACT_H
