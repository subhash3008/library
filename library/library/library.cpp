#include <iostream>
#include <string>
#include <fstream>
#include "Book.h"
#include "Inventory.h"
#include "User.h"

Inventory _inventory;
std::vector<User> _users;

User _loggedInUser;

std::string usersFileName = "users.txt";

void loadUsers() {
	std::ifstream inFile{ usersFileName };
	std::string linedata[2];
	std::string userLine;
	while (std::getline(inFile, userLine)) {
		std::size_t index = userLine.find('|');
		linedata[0] = userLine.substr(0, index);
		linedata[1] = userLine.substr(index + 1);

		User loadedUser;
		loadedUser.m_username = linedata[0];
		loadedUser.m_role = static_cast<Role>(std::stoi(linedata[1]));

		_users.push_back(loadedUser);
	}
}

void createAccount() {
	User newUser;
	/*std::cout << "First Name : \n";
	std::string firstname;
	std::getline(std::cin, firstname);
	std::cout << "Last Name : \n";
	std::string lastname;
	std::getline(std::cin, lastname);*/
	std::cout << "Username : \n";
	std::getline(std::cin, newUser.m_username);

	std::cout << "Choose a role : \n";
	std::cout << "1. Admin\n";
	std::cout << "2. Employee\n";
	std::cout << "3. Member\n";

	int roleOption;
	std::cin >> roleOption;
	std::cin.ignore();

	newUser.m_role = static_cast<Role>(roleOption - 1);
	_users.push_back(newUser);

	std::ofstream oFile{ usersFileName, std::ios_base::app };
	oFile << newUser.m_username << '|' << static_cast<int>(newUser.m_role) << std::endl;
	oFile.close();
}

void login() {
	std::cout << "Choose an option : " << std::endl;
	std::cout << "1. Login" << std::endl;
	std::cout << "2. Create account" << std::endl;

	int option;
	std::cin >> option;
	std::cin.ignore();

	if (option == 2) {
		createAccount();
	}

	while (true) {
		std::cout << "Enter Username : ";
		std::string username;
		getline(std::cin, username);

		std::vector<User>::const_iterator it{ std::find(_users.begin(), _users.end(), User(username)) };
		if (it != _users.end()) {
			_loggedInUser = _users[it - _users.begin()];
			break;
		}
	}
}

int listOptions() {
	std::cout << "Please choose an option : " << std::endl;
	if (_loggedInUser.m_role == Role::Admin || _loggedInUser.m_role == Role::Employee) {
		std::cout << "1. Add book" << std::endl;
		std::cout << "5. Remove a book" << std::endl;
		std::cout << "6. List all checked out books" << std::endl;
	}
	std::cout << "2. List all books" << std::endl;
	std::cout << "3. Checkout a book" << std::endl;
	std::cout << "4. Checkin a book" << std::endl;
	std::cout << "0. Exit" << std::endl;
	int input;
	std::cin >> input;
	std::cin.ignore();
	return input;
}

void addNewBook() {
	std::cout << "Enter title : ";
	std::string title;
	std::getline(std::cin, title);
	std::cout << "Enter author : ";
	std::string author;
	std::getline(std::cin, author);
	Book newBook{ title, author };

	_inventory.addBook(newBook);
}

void checkInOrOutBook(bool checkout) {
	std::string inOrOut = checkout ? "out" : "in";
	std::cout << "Enter the book title to check" + inOrOut + ": ";
	std::string title;
	std::getline(std::cin, title);

	CheckedInOrOutResult result = _inventory.checkInOrOutBook(title, checkout);
	switch (result) {
		case CheckedInOrOutResult::Success:
			std::cout << "Book successfully checked " + inOrOut + ".\n";
			break;
		case CheckedInOrOutResult::BookNotFound:
			std::cout << "Book not found!!\n";
			break;
		case CheckedInOrOutResult::Failure:
			std::cout << "Book already checked " + inOrOut + ".\n";
			break;
		default:
			std::cout << "Invalid Result.";
	}
}

void deleteBook() {
	std::cout << "Enter title : ";
	std::string title;
	std::getline(std::cin, title);

	_inventory.removeBook(title);
	std::cout << "Reqested book is deleted.\n";
}


int main() {
	loadUsers();
	login();
	while (true) {
		int input{ listOptions() };

		switch (input) {
			case 0:
				std::cout << "Thank you. Goodbye!!";
				return 0;
			case 1:
				addNewBook();
				break;
			case 2:
				_inventory.listAllBooks();
				break;
			case 3:
				checkInOrOutBook(true);
				break;
			case 4:
				checkInOrOutBook(false);
				break;
			case 5:
				deleteBook();
				break;
			case 6:
				_inventory.displayCheckedOutBooks();
				break;
			default:
				std::cout << "Invalid selection. Try again.";
				break;
		}
	}
	return 0;
}