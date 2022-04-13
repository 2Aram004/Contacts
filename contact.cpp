#include "contact.h"

Contact::Contact() noexcept
{
	user_command.emplace("add", &Contact::addContact);
	user_command.emplace("read", &Contact::readAllContacts);
	user_command.emplace("delete", &Contact::deleteContact);
	user_command.emplace("change", &Contact::changeData);
	user_command.emplace("find", &Contact::findContact);
	user_command.emplace("stop", &Contact::stop);

	changed_data.emplace("name", &Contact::changeName);
	changed_data.emplace("lastname", &Contact::changeLastName);
	changed_data.emplace("address", &Contact::changeAddress);
	changed_data.emplace("number", &Contact::changeNumber);
	changed_data.emplace("email", &Contact::changeEmail);

	start();
}

void Contact::stop()
{
	exit(0);
}

void Contact::start()
{
	std::cout << "\nEnter the name of your file please ";
	std::cin >> name_of_file;

	write.open(name_of_file, std::ofstream::app);
	commandList();
	getDatas();
	changeInFile();
}

void Contact::changeName(const std::unordered_map<int, Datas>::iterator it)
{
	do {
		std::cout << "\nEnter new name ";
		std::cin >> it->second.name;

	} while(!(checkFirstLetter(it->second.name[0])));

	changeInFile();
}

void Contact::changeLastName(const std::unordered_map<int, Datas>::iterator it)
{
	do {
		std::cout << "\nEnter new lastname ";
		std::cin >> it->second.lastname;

	} while(!(checkFirstLetter(it->second.lastname[0])));

	changeInFile();
}

void Contact::changeNumber(const std::unordered_map<int, Datas>::iterator it)
{
	do {
		std::cout << "\nEnter new number ";
		std::cin >> it->second.number;

	} while(!(checkNumber(it->second.number)));

	changeInFile();
}

void Contact::changeAddress(const std::unordered_map<int, Datas>::iterator it)
{
	std::cout << "\nEnter new address ";
	std::cin >> it->second.address;

	changeInFile();
}

void Contact::changeEmail(const std::unordered_map<int, Datas>::iterator it)
{
	do {
		std::cout << "\nEnter new email ";
		std::cin >> it->second.email;

	} while(!(checkEmail(it->second.email)));

	changeInFile();
}

void Contact::changeInFile()
{
	write.close();
	write.open(name_of_file);

	for(auto it = contacts.begin(); it != contacts.end(); ++it) {
		write << it->first << '\n';
		write << it->second.name << '\n';
		write << it->second.lastname << '\n';
		write << it->second.address << '\n';
		write << it->second.number << '\n';
		write << it->second.email << '\n';
	}
	    write.close();
}

void Contact::commandList() const
{
	std::cout << "\nEnter add to add contact\n";
	std::cout << "Enter change to change data\n";
	std::cout << "Enter delete to delete contact\n";
	std::cout << "Enter read to read all contacts\n";
	std::cout << "Enter find to find contact\n";
	std::cout << "Enter stop to stop\n";
}

void Contact::deleteContact()
{
	setMap();

	std::unordered_map<int, Datas>::iterator it = contacts.end();

	do {
		std::cout << "Which contact do you want to delete (Enter your contact's ID) ";
		std::cin >> delete_contact_number;

		it = contacts.find(delete_contact_number);

		} while(it == contacts.end());

	contacts.erase(it);
	--ID_of_contact;
	changeInFile();

}

void Contact::addContact()
{
	setMap();
	ID_of_contact = contacts.size() + 1;

	std::cout << "This contact's ID is " << ID_of_contact << '\n';

	do {
		std::cout << "Enter name please ";
		std::cin >> datas.name;

	} while(!checkFirstLetter(datas.name[0]));	

	
	do {
		std::cout << "\nEnter lastname please ";
		std::cin >> datas.lastname;

	} while(!(checkFirstLetter(datas.lastname[0])));


	do {
		std::cout << "\nEnter phone number please ";
		std::cin >> datas.number;

	} while(!(checkNumber(datas.number)));


	std::cout << "\nEnter address please ";
	std::cin >> datas.address;


	do {
		std::cout << "\nEnter email address please ";
		std::cin >> datas.email;

	} while(!(checkEmail(datas.email)));

	contacts.emplace(ID_of_contact, datas);
	++ID_of_contact;
	changeInFile();
}

bool Contact::checkFirstLetter(char first_letter)
{
	return (datas.name[0] >= 'A' && datas.name[0] <= 'Z');
}

bool Contact::checkNumber(const std::string& current_number)
{
	for(int i = 0; i < current_number.size(); ++i) {
		if(current_number[i] >=! 48 && current_number[i] <! 58) {
			return false;
		}
	}

	for(auto it = contacts.begin(); it != contacts.end(); ++it) {

		if(it->second.number == current_number) {
			return false;
		}
	}
	return true;
}

bool Contact::checkEmail(const std::string& current_email)
{
	for(auto it = contacts.begin(); it != contacts.end(); ++it) {

		if(it->second.email == current_email) {
			return false;
		}
	}
	return true;
}


void Contact::getDatas()
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

void Contact::readAllContacts()
{
	read.open(name_of_file);
	while(!read.eof()) {
		getline(read, str);
		std::cout << str;
		std::cout << '\n';
	}
	read.close();
}

void Contact::findContact()
{
	setMap();
	int ID;
	auto it = contacts.end();

	do {
		std::cout << "\nEnter the ID of contact you want to find ";
		std::cin >> ID;
		it = contacts.find(ID);

	} while(it == contacts.end());

	std::cout << it->second.name << '\n';
	std::cout << it->second.lastname << '\n';
	std::cout << it->second.number << '\n';
	std::cout << it->second.address << '\n';
	std::cout << it->second.email << '\n';
}

void Contact::setMap()
{
	read.open(name_of_file);
	Datas datas;
	int tmp {};
	int count_of_datas = 0;

	while(!read.eof()) {
		read >> tmp;
		getline(read, str);

	 while(count_of_datas < 5) {
		getline(read, str);
		
	if(count_of_datas == 0) {
		datas.name = str;
		++count_of_datas;

	 } else if(count_of_datas == 1) {
		datas.lastname = str;
		++count_of_datas;

	 } else if(count_of_datas == 2) {
		datas.number = str;
		++count_of_datas;

	 } else if(count_of_datas == 3) {
		datas.address = str;
		++count_of_datas;

	 } else if(count_of_datas == 4) {
	 	datas.email = str;
		++count_of_datas;
	 }

	}
	 if(tmp != 0) {
		contacts.emplace(tmp, datas);
	 }
	count_of_datas = 0;
	
}
	read.close();
}
void Contact::changeData()
{
	setMap();
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
