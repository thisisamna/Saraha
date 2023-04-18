#include "User.h"
#include "Message.h"
#include <iostream>
#include <unordered_map>

//global objects & variables
unordered_map<int, User> users;

//function declarations
User getUser(int id);

using namespace std;

int main() {

	return 0;
}

//function definitions

User getUser(int id)
{
	User user;
	auto it = users.find(id);
	user = it->second;
	return user;
}


