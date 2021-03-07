#ifndef INVENTORY_H
#define INVENTORY_H

#include <vector>
#include "Book.h"
#include "CheckedOutResult.h"

class Inventory {
private:
	std::vector<Book> m_books;
public:
	void addBook(Book& book);
	void listAllBooks() const;
	void removeBook(std::string& title);
	int findBookByTitle(std::string& title) const;
	CheckedInOrOutResult checkInOrOutBook(std::string& title, bool checkOut);
	int getNextBookId();
	void displayCheckedOutBooks() const;
	int getBooksSize() const;
	void loadBooks();
};

#endif // INVENTORY_H

