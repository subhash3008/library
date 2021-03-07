#include "Book.h"
#include <string>

Book::Book() {}

Book::Book(std::string title, std::string author):
	m_title{ title }, m_author{ author }, m_checkedOut{ false }
{}

bool Book::isCheckedOut() const {
	return m_checkedOut;
}

void Book::setCheckedOut(bool checkedOut) {
	m_checkedOut = checkedOut;
}

void Book::setId(int id) {
	m_id = id;
}

int Book::getId() const {
	return m_id;
}

bool Book::operator==(const Book& book) const {
	if (m_title.compare(book.m_title) == 0) {
		return true;
	}
	return false;
}

std::string Book::getBookFileData() const {

	return std::to_string(m_id) + "|" + m_title + "|" + m_author + "|" + (m_checkedOut ? "1" : "0");
}