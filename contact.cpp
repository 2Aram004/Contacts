#include "contact.h"

Contact::Contact() noexcept
{
	user_command.emplace("add", &Contact::Add);
	user_command.emplace("read", &Contact::Read);
	user_command.emplace("delete", &Contact::Delete);
	user_command.emplace("change", &Contact::Change);
	
	changed_data.emplace("name", &Contact::ChangeName);
	changed_data.emplace("lastname", &Contact::ChangeLastName);
	changed_data.emplace("address", &Contact::ChangeLastName);
	changed_data.emplace("number", &Contact::ChangeLastName);

	Start();
}

void Contact::Start()
{
	fout.open("Contact.txt", std::ofstream::app);
	CommandList();
	GetDatas();
	Save();
}

void Contact::ChangeName(std::unordered_map<int, Datas>::iterator it)
{
	std::cin >> it->second.name;
	ChangeInFile();
}

void Contact::ChangeLastName(std::unordered_map<int, Datas>::iterator it)
{
	std::cin >> it->second.lastname;
	ChangeInFile();
}

void Contact::ChangeNumber(std::unordered_map<int, Datas>::iterator it)
{
	std::cin >> it->second.number;
	ChangeInFile();
}

void Contact::ChangeAddress(std::unordered_map<int, Datas>::iterator it)
{
	std::cin >> it->second.address;
	ChangeInFile();
}

void Contact::ChangeInFile()
{
	fout.close();
	fout.open("Contact.txt");

	for(auto it = contacts.begin(); it != contacts.end(); ++it) {
		fout << it->first << '\n';
		fout << it->second.name << '\n';
		fout << it->second.lastname << '\n';
		fout << it->number << '\n';
		fout << it->second.address << '\n';
	}
	fout.close();
}

void Contact::CommandList() const
{
	std::cout << "Enter add to add\n";
	std::cout << "Enter change to change\n";
	std::cout << "Enter delete to delete\n";
	std::cout << "Enter read to read\n";
	std::cout << "Enter stop to stop\n";
}

void Contact::Delete()
{
	std::cout << "Which contact do you want to delete  ";
	std::cin >> delete_contact_number;

	auto it = contacts.find(delete_contact_number);

	if(it != contacts.end()) {
		contacts.erase(it);
		ChangeInFile();

	}  else { std::cout << "Contact was not found"; }
}

void Contact::Add()
{
	std::cout << "Enter name please ";
	std::cin >> datas.name;

	std::cout << "\nEnter lastname please ";
	std::cin >> datas.lastname;

	std::cout << "\nEnter phone number please ";
	std::cin >> datas.number;

	std::cout << "\nEnter address please ";
	std::cin >> datas.address;

	contacts.emplace(count, datas);
	++count;
	ChangeInFile();
}

void Contact::Save()
{
	for(auto it = contacts.begin(); it != contacts.end(); ++it) {
		fout << it->first << '\n';
		fout << it->second.name << '\n';
		fout << it->second.lastname << '\n';
		fout << it->second.address << '\n';
		fout << it->second.number << '\n';
	}
}

void Contact::GetDatas()
{
	using Fptr = void(Contact::*)();

	while(command != "stop") {

	std::cout << "\n\nEnter your command please ";
	std::cin >> command;

	Fptr function_pointer = user_command[command];
   	(this->*function_pointer)();
	}
}

void Contact::Read()
{
	fin.open("Contact.txt");
	while(!fin.eof()) {
		getline(fin, str);
		std::cout << str;
		std::cout << '\n';
	}
	fin.close();
}

void Contact::Change()
{
	using fptr = void(Contact::*)(std::unordered_map<int, Contact::Datas>::iterator);
    do {    
	    std::cout << "\nWhich contact do you want do change(number) ";
	    std::cin >> change_contact_number;

    } while(change_contact_number <= count);

        std::unordered_map<int, Contact::Datas>::iterator it = contacts.find(change_contact_number);

		std::cout << "Which data do you want to change? ";
		std::cin >> change_data;

		fptr function = changed_data[change_data];
		(this->*function)(it);
}
