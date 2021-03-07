#include <vector>
#include <string>
#include <fstream>
#include "Book.h"
#include "Inventory.h"

void Inventory::addBook(Book& book) {
	int id = 0;
	if (m_books.size() > 0) {
		id = m_books.back().getId();
	}
	book.setId(id + 1);
	m_books.push_back(book);
	std::ofstream oFile{ "books.txt", std::ios_base::app };
	oFile << book.getBookFileData();
	oFile.close();
}

void Inventory::removeBook(std::string& title) {
	std::vector<Book>::const_iterator it{ std::find(m_books.cbegin(), m_books.cend(), Book(title, "")) };
	if (it != m_books.end()) {
		m_books.erase(it);
	}
}

void Inventory::listAllBooks() const {
	std::vector<Book>::const_iterator it{ m_books.begin() };
	std::cout << "*************************************\n";
	while (it != m_books.end()) {
		std::cout << *it;
		++it;
	}
	std::cout << "*************************************\n";
}

int Inventory::findBookByTitle(std::string& title) const {
	std::vector<Book>::const_iterator it{ std::find(m_books.cbegin(), m_books.cend(), Book(title, "")) };
	if (it == m_books.end()) {
		return -1;
	}
	int index = it - m_books.cbegin();
	return index;
}

CheckedInOrOutResult Inventory::checkInOrOutBook(std::string& title, bool checkOut) {
	int foundIndex = findBookByTitle(title);
	if (foundIndex >= 0) {
		if (m_books[foundIndex].isCheckedOut() == checkOut) {
			return CheckedInOrOutResult::Failure;
		}
		m_books[foundIndex].setCheckedOut(checkOut);
		return CheckedInOrOutResult::Success;
	} else {
		return CheckedInOrOutResult::BookNotFound;
	}
}

int Inventory::getNextBookId() {
	return m_books.back().getId() + 1;
}

int Inventory::getBooksSize() const {
	return m_books.size();
}

void Inventory::displayCheckedOutBooks() const {
	int checkedOutBooks = 0;
	for (int i = 0; i < getBooksSize(); ++i) {
		if (m_books[i].isCheckedOut()) {
			std::cout << m_books[i];
			++checkedOutBooks;
		}
	}
	if (checkedOutBooks == 0) {
		std::cout << "No Books checked out currently!!\n";
	}
}

void Inventory::loadBooks() {
	std::ifstream inFile{ "books.txt" };
	std::string bookData[4];
	std::string bookLine;
	while (std::getline(inFile, bookLine)) {
		std::size_t prevIndex = bookLine.find('|');
		bookData[0] = bookLine.substr(0, prevIndex);

		std::size_t nextIndex = bookLine.find('|', prevIndex + 1);
		bookData[1] = bookLine.substr(prevIndex + 1, nextIndex);
	}
}