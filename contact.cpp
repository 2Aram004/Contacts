#include "contact.h"

Contact::Contact() noexcept
{
	userCommand.emplace("add", &Contact::addContact);
	userCommand.emplace("read", &Contact::readAllContacts);
	userCommand.emplace("delete", &Contact::deleteContact);
	userCommand.emplace("change", &Contact::changeUserData);
	userCommand.emplace("find", &Contact::findContact);
	userCommand.emplace("stop", &Contact::stop);

	start();
}

void Contact::stop()
{
	exit(0);
}

void Contact::start()
{
	std::cout << "\nEnter the name of your file please ";
	std::cin >> nameOfFile;

	commandList();
	getDatas();
}

void Contact::changeInFile()
{
	write.open(nameOfFile);

	for(auto it : contacts) {
		write << it.first << '\n';
		write << it.second.name << '\n';
		write << it.second.lastname << '\n';
		write << it.second.number << '\n';
		write << it.second.address << '\n';
		write << it.second.email << '\n';
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
	std::string deleteData;

	std::cout << "Which contact do you want to delete (Enter any data you remembre of that contact) ";

	do {
		std::cin >> deleteData;
	
	} while(find(deleteData).first);

	auto it = contacts.find(find(deleteData).second);
	contacts.erase(it);
	--idOfContact;
	changeInFile();

}

void Contact::addContact()
{
	setMap();
	int idOfContact; 
	
	for(auto it = contacts.begin(); it != contacts.end(); ++it) {
		idOfContact = it->first;
	}

	Datas user;
	do {
		std::cout << "\nFirst letter must be capital\n";
		std::cout << "Enter name please ";
		std::cin >> user.name;

	} while(!checkFirstLetter(user.name[0]));	

	
	do {
		std::cout << "\nFirst letter must be capital\n";
		std::cout << "Enter lastname please ";
		std::cin >> user.lastname;

	} while(!(checkFirstLetter(user.lastname[0])));


	do {
		std::cout << "\nNumber must contain 9 digits and can't be repeated\n";
		std::cout << "Enter phone number please ";
		std::cin >> user.number;

	} while(!(checkNumber(user.number)));


	std::cout << "\nEnter address please ";
	std::cin >> user.address;


	do {
		std::cout << "\nEnter email address please ";
		std::cin >> user.email;

	} while(!(checkEmail(user.email)));

	++idOfContact;
	contacts.emplace(idOfContact, user);
	changeInFile();
}

bool Contact::checkFirstLetter(char firstLetter)
{
	return (firstLetter >= 'A' && firstLetter <= 'Z');
}

bool Contact::checkNumber(const std::string& currentNumber)
{
	if(currentNumber.size() != 9) return false;

	for(int i = 0; i < currentNumber.size(); ++i) {
		if(!(currentNumber[i] >= '0' && currentNumber[i] <= '9')) {
			return false;
		}
	}

	for(auto it = contacts.begin(); it != contacts.end(); ++it) {

		if(it->second.number == currentNumber) {
			return false;
		}
	}
	return true;
}

bool Contact::checkEmail(const std::string& currentEmail)
{
	for(auto it = contacts.begin(); it != contacts.end(); ++it) {

		if(it->second.email == currentEmail) {
			return false;
		}
	}

	const std::regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
    		return std::regex_match(currentEmail,pattern);
	
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
	
		iter = userCommand.find(command);
		
	} while(iter == userCommand.end());
	
		Fptr function_pointer = userCommand[command];
   		(this->*function_pointer)();
	}
}

void Contact::readAllContacts()
{
	setMap();
	for(auto it = contacts.begin(); it != contacts.end(); ++it) {
		if(it->second.name.size() != 0) {
			std::cout << "Name\t" << it->second.name << "\tLastname\t" << it->second.lastname << "\tNumber\t" << it->second.number << "\tAddress\t" << it->second.address << "\tEmail\t" << it->second.email << '\n';
		}

	}
}

void Contact::findContact()
{
	setMap();
	std::string findNameData;

	std::cout << "\nWhich contact do you want to find(Enter any data of that contact please)\n";
	std::cout << "\nEnter name of data\n";
	std::cin >> findNameData;
	find(findNameData);
}

std::pair<bool, int> Contact::find(const std::string& data)
{
	setMap();

	bool noData = false;
	int count = 0;
	auto it = contacts.begin();
	auto currentIterData = contacts.begin();

	for(; it != contacts.end(); ++it) {
		if(it->second.name == data || it->second.lastname == data || it->second.number == data || it->second.address == data || it->second.email == data) {
			noData = true;
			++count;
			currentIterData = it;
			std::cout << "Name\t" << it->second.name << "\tLastname\t" << it->second.lastname << "\tNumber\t" << it->second.number << "\tAddress\t" << it->second.address << "\tEmail\t" << it->second.email << '\n';
		}
	}
	if(!noData) {
	std::cout << "\nData was not found\n";
	}

	std::pair<bool, int> Pair;

	if(count > 1) {
		std::cout << "Please enter extra data about user\n";
		Pair.first = true;
		Pair.second = 0;
		return Pair;

	} else {
		Pair.first = false;
		Pair.second = currentIterData->first;
		return Pair;
	}
	return Pair;
}

void Contact::setMap()
{
	read.open(nameOfFile);
	if(!read.is_open()) {
		std::cout << "Could not open file";
		exit(0);
	}
	int tmp {};
	int countOfDatas = 0;

	while(!read.eof()) {
	read >> tmp;

	read >> str;
	userDatas.name = str;

	read >> str;
	userDatas.lastname = str;

	read >> str;
	userDatas.address = str;

	read >> str;
	userDatas.number = str;

	read >> str;
	userDatas.email = str;

	contacts.emplace(tmp, userDatas);
	++countOfDatas;
	}

	read.close();
}
void Contact::changeUserData()
{
	setMap();
	std::cout << "Enter any data of contact you want to change";

	do {
		std::cin >> changeContactData;

	} while(find(changeContactData).first);


	do {

	std::cout << "Enter name of the data";
	std::cin >> changeContactName;
	auto it = contacts.end();

	if(changeContactName == "name") {

		do {
			std::cout << "\nFirst letter must be capital\n";
			std::cout << "Enter new name for\t";
			it = contacts.find(find(changeContactData).second);
			std::cin >> it->second.name;
	
		} while(!(checkFirstLetter(it->second.name[0])));

		changeInFile();
		return;

	} else if(changeContactName == "lastname") {

		do {
			std::cout << "\nFirst letter must be capital\n";
			std::cout << "Enter new lastname";
			it = contacts.find(find(changeContactData).second);
			std::cin >> it->second.lastname;

	
		} while(!(checkFirstLetter(it->second.lastname[0])));

		changeInFile();
		return;
		
	} else if(changeContactName == "address") {

			std::cout << "\nEnter new address\n";
			it = contacts.find(find(changeContactData).second);
			std::cin >> it->second.address;

			changeInFile();
			return;

	} else if(changeContactName == "emal") {

		do {
			std::cout << "Email address must not be repeated";
			std::cout << "Enter new email";
			it = contacts.find(find(changeContactData).second);
			std::cin >> it->second.email;
		
		} while(!(checkEmail(it->second.email)));

		changeInFile();
		return;

	} else if(changeContactName == "number") {
	
		do {
			std::cout << "Phone number must not be repeated";
			std::cout << "Enter new number";
			it = contacts.find(find(changeContactData).second);
			std::cin >> it->second.number;

		} while(!(checkNumber(it->second.number)));

		changeInFile();
		return;
	 }

	} while(changeContactName != "name" || changeContactName != "lastname" || changeContactName != "address" || changeContactName != "email" || changeContactName != "number");
}
