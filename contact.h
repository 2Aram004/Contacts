#ifndef _CONTACT_H
#define _CONTACT_H

#include <iostream>
#include <unordered_map>
#include <fstream>
#include <string>

class Contact
{
public:
	Contact() noexcept;
	void start();
	~Contact(){write.close();}
	
private:

	struct Datas
	{
		std::string name;
		std::string lastname;
		std::string number;
		std::string address;
		std::string email;
	};

	void addContact();
	void deleteContact();
	void changeData();
	void readAllContacts();
	void stop();
	void findContact();
	void getDatas();
	void commandList() const;
	void changeInFile();
	void setMap();
	bool checkFirstLetter(char);
	bool checkNumber(const std::string&);
	bool checkEmail(const std::string&);
	void changeName(const std::unordered_map<int, Datas>::iterator);
	void changeLastName(const std::unordered_map<int, Datas>::iterator);
	void changeAddress(const std::unordered_map<int, Datas>::iterator);
	void changeNumber(const std::unordered_map<int, Datas>::iterator);
	void changeEmail(const std::unordered_map<int, Datas>::iterator);

private:

	std::ofstream write;
	std::ifstream read;
	std::string name_of_file;
	int ID_of_contact = 0;
	std::string str;
	std::string command;
	Datas datas;
	std::unordered_map<std::string, void(Contact::*)()> user_command;
	std::unordered_map<int, Datas> contacts;
	std::unordered_map<std::string, void(Contact::*)(std::unordered_map<int, Datas>::iterator)> changed_data;
	int change_contact_number;
	std::string change_data;
	int delete_contact_number;
};
#endif
