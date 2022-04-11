#include "contact.h"

Contact::Contact() noexcept
{
	user_command.emplace("add", &Contact::Add);
	user_command.emplace("read", &Contact::Read);
	user_command.emplace("delete", &Contact::Delete);
	user_command.emplace("change", &Contact::Change);
	user_command.emplace("stop", &Contact::Stop);

	changed_data.emplace("name", &Contact::ChangeName);
	changed_data.emplace("lastname", &Contact::ChangeLastName);
	changed_data.emplace("address", &Contact::ChangeAddress);
	changed_data.emplace("number", &Contact::ChangeNumber);

	Start();
}

void Contact::Stop()
{
	exit(0);
}

void Contact::Start()
{
	fout.open("Contact.txt", std::ofstream::app);
	CommandList();
	GetDatas();
	ChangeInFile();
}

void Contact::ChangeName(const std::unordered_map<int, Datas>::iterator it)
{
	std::cout << "\nEnter new name ";
	std::cin >> it->second.name;
	ChangeInFile();
}

void Contact::ChangeLastName(const std::unordered_map<int, Datas>::iterator it)
{
	std::cout << "\nEnter new lastname ";
	std::cin >> it->second.lastname;
	ChangeInFile();
}

void Contact::ChangeNumber(const std::unordered_map<int, Datas>::iterator it)
{
	std::cout << "\nEnter new number ";
	std::cin >> it->second.number;
	ChangeInFile();
}

void Contact::ChangeAddress(const std::unordered_map<int, Datas>::iterator it)
{
	std::cout << "\nEnter new address ";
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
		fout << it->second.address << '\n';
		fout << it->second.number << '\n';
	}
	    fout.close();
}

void Contact::CommandList() const
{
	std::cout << "\nEnter add to add\n";
	std::cout << "Enter change to change\n";
	std::cout << "Enter delete to delete\n";
	std::cout << "Enter read to read\n";
	std::cout << "Enter stop to stop\n";
}

void Contact::Delete()
{
	SetMap();

	std::unordered_map<int, Datas>::iterator it = contacts.end();

	do {
		std::cout << "Which contact do you want to delete (Enter your contact's ID) ";
		std::cin >> delete_contact_number;

		it = contacts.find(delete_contact_number);

		} while(it == contacts.end());

	contacts.erase(it);
	ChangeInFile();

}

void Contact::Add()
{
	SetMap();
	ID_of_contact = contacts.size() + 1;

	std::cout << "This contact's ID is " << ID_of_contact << '\n';

	std::cout << "Enter name please ";
	std::cin >> datas.name;

	std::cout << "\nEnter lastname please ";
	std::cin >> datas.lastname;

	std::cout << "\nEnter phone number please ";
	std::cin >> datas.number;

	std::cout << "\nEnter address please ";
	std::cin >> datas.address;

	contacts.emplace(ID_of_contact, datas);
	++ID_of_contact;
	ChangeInFile();
}

void Contact::GetDatas()
{
	using Fptr = void(Contact::*)();
	std::unordered_map<std::string, Fptr>::const_iterator iter;

	while(command != "stop") {

	do {
		std::cout << "\n\nEnter your command please ";
		std::cin >> command;
	
		iter = user_command.find(command);
		
	} while(iter == user_command.end());
	
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

void Contact::SetMap()
{
	fin.open("Contact.txt");
	Datas datas;
	int tmp {};
	int count2 = 0;

	while(!fin.eof()) {
		fin >> tmp;
		getline(fin, str);

	 while(count2 < 4) {
		getline(fin, str);
		
	if(count2 == 0) {
		datas.name = str;
		++count2;

	 } else if(count2 == 1) {
		datas.lastname = str;
		++count2;

	 } else if(count2 == 2) {
		datas.number = str;
		++count2;

	 } else if(count2 == 3) {
		datas.address = str;
		++count2;
	 }
	}
	contacts.emplace(tmp, datas);
	count2 = 0;
	
}
	fin.close();
}
void Contact::Change()
{
	SetMap();
	using fptr = void(Contact::*)(std::unordered_map<int, Contact::Datas>::iterator);

    do {    
	    std::cout << "\nWhich contact do you want do change (Enter your contact's ID) ";
	    std::cin >> change_contact_number;

    } while(change_contact_number > ID_of_contact);

	const std::unordered_map<int, Contact::Datas>::iterator it = contacts.find(change_contact_number);
	auto it2 = changed_data.end();	

	do {
		std::cout << "Which data do you want to change? ";
		std::cin >> change_data;

		it2 = changed_data.find(change_data);

	} while(it2 == changed_data.end());

		fptr function = changed_data[change_data];
		(this->*function)(it);

}

int main()
{
	Contact contact;
	contact.Start();
}
