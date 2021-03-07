#ifndef BOOK_H
#define BOOK_H

#include <iostream>

class Book {
	private:		
		int m_id = 0;
		std::string m_title = "";
		std::string m_author = "";
		bool m_checkedOut = false;

	public:
		Book();
		Book(std::string title, std::string author);
		bool isCheckedOut() const;
		void setCheckedOut(bool checkedOut);
		int getId() const;
		void setId(int id);
		bool operator==(const Book& book) const;
		std::string getBookFileData() const;

		friend std::ostream& operator<<(std::ostream& out, const Book& book) {
			out << book.m_id << '\t' << book.m_title << '\t' << book.m_author << '\n';
			return out;
		}
};

#endif

