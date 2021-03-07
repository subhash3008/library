#ifndef USER_H
#define USER_H

#include <string>
#include "Role.h"

class User {
	public:
		int m_id = 0;
		std::string m_firstName = "";
		std::string m_lastName = "";
		std::string m_username = "";
		Role m_role;

		User();
		User(std::string& username);

		bool operator==(const User& user) const;
};

#endif

