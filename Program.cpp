#include "Program.h"

#include <iostream>

void Program::loop()
{
	loginMenu();

}

void Program::loginMenu()
{
	while (true) {
		printCentered("S a r a h a");
		printCentered("Annonymously send and receive messages.");
		cout << "Welcome!" << endl;
		cout << "Do you have an account?\n\n" << endl; //bug here, two newlines fix it but why?
		cout << "1. Yes (login)\n"
			<< "2. No (sign up)\n"
			<< "3. Exit\n";

		cin >> choice;

		switch (choice) {
		case 1:
		{
			//login
			printCentered("L o g   i n");
			string username, password;
			cout << "Username: ";
			cin >> username;
			cout << "Password: ";
			cin >> password;
			User liveUser(username, password);
			if (login(liveUser)) //if login returns null it will just break
			{
				userMenu(liveUser);

			}
			break;
		}
		case 2:
			printCentered("S i g n   u p");
			//signup
			break;
		case 3:
			//exit
			return;
		default:
			cout << "Invalid entry, try again!\n";
		}
	}
}

void Program::userMenu(User liveUser)
{
	while (true)
	{
		cout << "1. Send a message\n"
			<< "2. Inbox\n"
			<< "3. Favorites\n"
			<< "4. Sent messages\n"
			<< "5. My contacts\n"
			<< "6. Logout\n";
		cin >> choice;
		switch (choice)
		{
		case 1:
			//send a message
			break;
		case 2:
		{
			//inbox
			Inbox(liveUser);
		}
		case 3:
			//favorites
			break;
		case 4:
			//sent messages
			liveUser.viewSent();
			break;
		case 5:
			//contacts
			liveUser.viewcontacts();
			break;
		case 6:
			//logout
			return; //هيخرج برا اللوب وبرا الفنكشن
		default:
			cout << "Invalid entry, try again!\n";
		}
	}
}

void Program::Inbox(User liveUser)
{
	int msgIndex;
	liveUser.viewReceived();
	cout << "Enter message index to view details and options. \n"
		<< "0. Back to home. \n";
	cin >> msgIndex;
	if (msgIndex == 0)
	{
		return;
	}
	else
	{
		Message msg = liveUser.getInboxMessage(msgIndex);
		msg.viewAsReceived();
		cout << "1. Add/remove from favorites.\n"
			<< "2. Add sender to contacts\n"
			<< "0. Back to previous menu.\n";
		cin >> choice;
		switch (choice)
		{
		case 1:
			liveUser.favourite(msg);
			break;
		case 2:
		{
			addSender(msg);
		case 0:
			break;
		default:
			cout << "Invalid entry.";
		}
		break;
		}
	}
}

User* Program::login(User user) //Wessal
{
	User* liveUser = new User(); // السطر ده تمشية حال 
	return liveUser;
}
User Program::idToUser(int id)
{
	User user;
	auto it = usersToID.find(id);
	user = it->second;
	return user;
}

User Program::usernameToUser(string username)
{
	User user;
	auto it = usersToUsername.find(username);
	user = it->second.second; //accessing map of map
	return user;
}

void Program::addSender(Message msg)
{
	User sender = idToUser(msg.getSender());
	liveUser.addcontact(sender);
}

void Program::printCentered(string str)
{
	int maxwidth = 70;
	stringstream ss;
	int padding = maxwidth - str.size() / 2;
	for (int i = 0; i < padding;  i++) 
	{
		ss << " ";
	}
	ss << str;
	for (int i = 0; i < padding; i++)
	{
		ss << " ";
	}
	cout << ss.str() << endl;
}

