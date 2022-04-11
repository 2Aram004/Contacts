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
	void Start();
	~Contact(){fout.close();}
	
private:
	struct Datas; // forward decleration
	void Add();
	void Delete();
	void Change();
	void Read();
	void Stop();
	void GetDatas();
	void CommandList() const;
	void ChangeInFile();
	void SetMap();
	void ChangeName(std::unordered_map<int, Datas>::iterator);
	void ChangeLastName(std::unordered_map<int, Datas>::iterator);
	void ChangeAddress(std::unordered_map<int, Datas>::iterator);
	void ChangeNumber(std::unordered_map<int, Datas>::iterator);

private:
	struct Datas
	{
		std::string name;
		std::string lastname;
		std::string number;
		std::string address;
	};

	std::ofstream fout;
	std::ifstream fin;
	int ID_of_contact = 1;
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
