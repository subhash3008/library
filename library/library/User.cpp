#include "User.h"


User::User() 
{}

User::User(std::string& username):
	m_username { username }
{}

bool User::operator==(const User& user) const {
	return (m_username.compare(user.m_username) == 0);
}