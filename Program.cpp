#include "Program.h"
#include <iostream>
#include<fstream>
Program::Program()
{
	loadfile();
}
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
			liveUserID = login();
			if (liveUserID !=-1)
			{
				liveUser = users[liveUserID];
				userMenu(liveUser);
			}
			break;
		}
		case 2:
			printCentered("S i g n   u p");
			//signup
			signup();
			break;
		case 3:
			//exit
			return;
		default:
			cout << "Invalid entry, try again!\n";
				break;
		}
		UpdateLiveUserData();
	}
	
}

void Program::userMenu(User &liveUser)
{
	while (true)
	{
		if (liveUser.newMsgs != 0) 
			cout << "you have " << liveUser.newMsgs << " unread messages\n";
			
		
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
			sendmessage(liveUser);
			UpdateLiveUserData();
			break;
		case 2:
		{
			//inbox
			Inbox(liveUser);
			liveUser.newMsgs = 0;
			break;
		}
		case 3:
			//favorites
			break;
		case 4:
			//sent messages
			cout << "Sent messages from latest to oldest: " << endl;
			liveUser.viewSent();
			cout << "1. Undo the latest message\n"
				<< "0. Back to previous menu\n";
			cin >> choice;
			if (choice == 1)
			{
				undolastmessage(liveUser);
			}
			UpdateLiveUserData();
			break;
		case 5:
			//contacts
			liveUser.viewcontacts(liveUser);
			break;
		case 6:
			//logout
			return; //هيخرج برا اللوب وبرا الفنكشن
		default:
			cout << "Invalid entry, try again!\n";
		}
		UpdateLiveUserData();
	}
}

void Program::Inbox(User &liveUser)
{
	int msgIndex;
	liveUser.viewReceived();
	cout << "Enter message index to view details and options. \n" << "0. Back to home. \n";
	cin >> msgIndex;
	msgIndex--;
	if (msgIndex == -1) // was 0 but 0 is an index in msg vector
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
			UpdateLiveUserData();
			break;
		case 2:
		{
			addSendertoContacts(msg);
			UpdateLiveUserData();
			break;

		case 0:
			break;
		default:
			cout << "Invalid entry.";
			break;

		}
		break;
		}
		UpdateLiveUserData();
	}
}


/*User Program::idToUser(int id)
{
	User user;
	if (users.find(id) != users.end()) {
		user = *users.find(id);
	}
	return user;
}*/
User* Program::idToUser(int id) {//returns pointer to user in hashmap, or nullptr if not found
	auto it = users.find(id);
	if (it != users.end()) {
		return &(it->second);
	}
	return nullptr;
}

int Program::usernameToID(string username)
{
	for (auto& it : users)
	{
		if (it.second.getUsername() == username)
			return it.first;
	}
	return -1; //not found
}

void Program::addSendertoContacts(Message msg)
{
	if (idToUser(msg.getSenderID()) != nullptr && idToUser(msg.getReceiverID()) !=nullptr) {
		User sender = *idToUser(msg.getSenderID());
		User receiver = *idToUser(msg.getReceiverID()); // liveuser
	    receiver.addcontact(receiver, sender);
	}
	else {
		cout << "Error During Adding Contact\n";
	}
	UpdateLiveUserData();
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

void Program::signup() { //wessal salah
	string username, pass;
	cout << "Please, enter your user name: \n";
	cin.ignore();
	getline(cin, username);
	cout << "Enter your password: \n";
	cin >> pass;
	if (usernameToID(username) != -1) {
		cout << "You already have an acount. please log in!";
	}
	else 
	{
		++userCount;
		users[userCount] = User(username, pass, userCount);
		cout << "Congratulation!!\nYou now have an account";
	}
}
	
	

int Program::login() { //wessal

	string name, pass;
	cout << "Enter your user name: \n";
	cin.ignore();
	getline(cin, name);
	cout << "Enter your password: \n";
	cin >> pass;
	liveUserID = usernameToID(name);
	if (liveUserID == -1)
	{
		cout << "The username is incorrect!\nplease try again\n";
		return -1;
	}
	else
	{
		auto it = users.find(liveUserID);
		User u = it->second;
		if (u.comparePassword(pass))
		{
			cout << "Welcome back!\n";
			return liveUserID;
		}
		else
		{
			cout << "The password is incorrect!\nplease try again\n";
			return -1;
		}
	}
}
	
void Program::sendmessage(User &liveUser) {
	// Data
	int receiverID;
	string username_receiver, msg; 
	char check;
	// Create Message

	cout << endl << "Enter your message:" << " ";
	cin.ignore();
	getline(cin, msg);

	cout << "Enter receiver username:" << " ";
	cin >> username_receiver;

	receiverID = usernameToID(username_receiver);

	
	if (receiverID == -1) 
	{
		cout << endl << "User does not exist, please try again." << endl;
	}
	else
	{
		User *receiver = &users[receiverID];

		Message msgg_object(liveUser.getid(), receiverID, username_receiver, msg);

		// Check
		cout << endl << "Send message? (y/n)" << " ";
		cin >> check;


		// Send Message
		if (check == 'y')
		{

			receiver->newMsgs++;
			// Push in Sender messages
			liveUser.addToSent(msgg_object, liveUser,*receiver);

			// push in reciver inbox
			receiver->addToInbox(msgg_object,liveUser,*receiver);
			cout << endl << "Message sent successfully." << " " << endl;
		}
		else
		{
			cout << endl << "Message canceled." << " " << endl;
		}
	}
	UpdateLiveUserData();

}

void Program::UpdateLiveUserData() {
	users[liveUserID] = liveUser;
}

void Program::undolastmessage(User &liveUser) {
	cout << endl << "Do You Want To Delete Last Message ? (y/n)" << " " << endl;
	char c;
	int cc;
	Message lastMsg;
	cin >> c;
	if (c == 'y') {
		// Pop in Sender messages and store popped message
		lastMsg = liveUser.popSent();
		cout << "1. Delete for me\n"
			<< "2. Delete for everyone\n";
		cin >> cc;
		switch (cc)
		{
		case 1:
			cout << "Message removed for you" << endl;
			break;
		case 2:
		{
			//Pop in receiver inbox //BUG HERE
			if (idToUser(lastMsg.getReceiverID()) != nullptr) {
				User* receiver = idToUser(lastMsg.getReceiverID());
				receiver->removeFromInbox(lastMsg);
				break;
			}
		}
		default:
			cout << "Invalid choice, please try again!";
		}
		UpdateLiveUserData();
	}
	else
		return;
}

void Program::savefile() {
	ofstream ourfile("ourdata.txt", ios::app);
	if (ourfile.is_open()) {
		for (auto data : users)
		{
			ourfile << data.first << ":  " << data.second.username << "\t" << data.second.password << "\t";
			for (auto& elem : data.second.sent) {
				ourfile << elem.getContent()<<"\t";
			}
			for (auto& elem : data.second.inbox) {
				ourfile << elem.getReceiverID()<<"\t"<<elem.getContent()<<"\t";
			}
			for (auto& elem : data.second.contacts) { // I don't know what should it return!
				ourfile << elem.second << "\t";
			}
			for (auto& elem : data.second.FavouriteMessages) {
				ourfile << elem.getReceiverID() << "\t" << elem.getContent();
			}
			ourfile << endl;
			/*for (int i = 0; i < data.second.sent.size(); i++) {
				ourfile << data.second.sent.front() << endl;
				data.second.sent.push_back(data.second.sent.front());
				data.second.sent.pop_front();

			}*/
			
		}
	}
		ourfile.close();
}
void Program::loadfile()
{
	ifstream ourfile("ourdata.txt");
	int id;
	User obj;
	while (ourfile >> id) {
		getline(ourfile, obj.username);
		getline(ourfile, obj.password);
		//users.insert(make_pair(id, obj));
		users[id] = User(obj.username, obj.password, id);
		/*for (auto it : users) {
			cout << it.first << it.second.username << " " << it.second.password;
		}*/
	}
	ourfile.close();
}
Program::~Program()
{
	users[liveUserID] = liveUser;
	savefile();
}

