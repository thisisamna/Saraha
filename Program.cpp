#include "Program.h"
#include <iostream>
#include<fstream>
#include<string>

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

		intChoice = getInt();
		printDivider();
		switch (intChoice) {
		case 1:
		{
			//login
			printCentered("L o g   i n");
			liveUserID = login();
			if (liveUserID !=-1)
			{
				printDivider();
				liveUser = &users[liveUserID];
				userMenu(*liveUser);
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
		printDivider();

	}
}

void Program::userMenu(User &liveUser)
{

	cout << "Welcome, " << liveUser.getUsername() << "!\n";
	while (true)
	{
		liveUser.notify();
	   cout << "\n"
		    << "1. Send a message\n"
			<< "2. Inbox\n"
			<< "3. Favorites\n"
			<< "4. Sent messages\n"
			<< "5. My contacts\n"
			<< "6. Logout\n";
		intChoice = getInt();
		printDivider();
		switch (intChoice)
		{
		case 1:
			//send a message
			printCentered("S e n d   a   m e s s a g e");

			sendmessage(liveUser);
			break;
		case 2:
		{
			//inbox
			printCentered("I n b o x");
			Inbox(liveUser);
			break;
		}
		case 3:
			//favorites
			printCentered("F a v o r i t e s");
			liveUser.viewFavorites();

			if (liveUser.getFavouriteMessages().size()!=0)
				cout << "1. Remove the oldest message\n";
			cout << "_______________\n";
			cout << "0. Back to previous menu\n";

			intChoice = getInt();
			if (intChoice == 1)
			{
				liveUser.RemoveOldestFavorite();
			}
			break;
		case 4:
			//sent messages
			printCentered("S e n t   m e s s a g e s");
			liveUser.viewSent();
			if (liveUser.getSent().size() != 0)
				cout << "1. Undo the latest message\n";
			cout << "_______________\n";
			cout << "0. Back to previous menu\n";

			intChoice = getInt();
			if (intChoice == 1)
			{
				undolastmessage(liveUser);
			}
			break;
		case 5:
			//contacts
			printCentered("C o n t a c t s");
			liveUser.viewcontacts();

			if (liveUser.getContacts().size() != 0) //changed
				cout << "\nEnter a contact ID for more options \n";
			cout << "_______________\n";
			cout << "0. Back to previous menu\n";

			intChoice = getInt();
			if (intChoice == 0)
				break;
			else
			{
				printDivider();
				contactMenu(liveUser, *idToUser(intChoice));
			}
			break;
		case 6:
			//logout
			return; //هيخرج برا اللوب وبرا الفنكشن
		default:
			cout << "Invalid entry, try again!\n";
		}
		printDivider();
	}

}

void Program::Inbox(User &liveUser)
{
	int msgIndex;
	cout << "\n"; //line

	if (liveUser.getInbox().size() != 0) //changed, كانت تطبع هذا اللاين حتى لو ما فيه مسج في الانبوكس
		cout << "Enter message index to view details and options. \n";
	liveUser.viewReceived();
	printDivider();
	cout << "0. Back to previous menu\n";

	msgIndex = getInt();
	msgIndex--;
	if (msgIndex == -1) // was 0 but 0 is an index in msg vector
	{
		return;
	}
	else
	{
		Message msg;
		while (true)
		{
			try
			{
				msg = liveUser.getInboxMessage(msgIndex);
				break;
			}
			catch(exception e)
			{
				cout << "Message does not exist, please choose an index from the list.\n";
			}
		}
		printDivider();
		msg.viewAsReceived();
		cout << "\n1. Add to favorites.\n"
			<< "2. Add sender to contacts\n"
			<< "3. Report sender\n"
			<< "0. Back to previous menu.\n";
		intChoice = getInt();
		switch (intChoice)
		{
		case 1:
			liveUser.favourite(msg);
			cout << "Message added to favorites." << endl;
			break;
		case 2:
			addSendertoContacts(liveUser, msg);
			break;

		case 3:
			cout << endl << "Report the sender of this message? (y/n) ";
			cin >> check;
			// Send Message
			if (check == 'y')
			{
				idToUser(msg.getSenderID())->beReported();
				cout << "Sender reported.\n";
			}
			break;
		case 0:
			break;
		default:
			cout << "Invalid entry.";
			break;

		}

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

void Program::addSendertoContacts(User& liveUser, Message msg)
{
	User sender = *idToUser(msg.getSenderID());


	if (sender.Blocked(liveUser.getid())) //check if blocked
		cout << "\nyou have been blocked by this user\n";
	else
	liveUser.addcontact(sender);
	cout << "\nSender added to contacts.\n";


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

	cout << "\n\n"; // line

	if (usernameToID(username) != -1) {
		cout << "You already have an acount. please log in! \n";
	}
	else 
	{
		++userCount;
		users[userCount] = User(username, pass, userCount);
		cout << "Congratulation!!\nYou now have an account \n";
	}
	printDivider();

}
	
	

int Program::login() { //wessal

	string username, pass;
	cout << "Enter your user name: \n";

	cin.ignore();
	getline(cin, username);
	cout << "Enter your password: \n";
	cin >> pass;

	cout << "\n\n"; //line
	liveUserID = usernameToID(username);
	if (liveUserID == -1)
	{
		cout << "The username is incorrect!\nplease try again\n";
		return -1;
	}
	else
	{
		auto it = users.find(liveUserID);
		User u = it->second;
		if (!u.comparePassword(pass))
		{
			cout << "The password is incorrect!\nplease try again\n";
			return -1;
		}
		else
		{
			if (u.isBanned())
			{
				cout << "Uh oh! Your account is banned :( \n"
					<< "Looks like you have been reported too many times.\n";
				return -1;
			}
			else
			{
				//cout << "Welcome back, " << u.getUsername() << "!\n"; -- فيه welcome in the main menu
				return liveUserID;
			}
		}
	}
}
	

	
void Program::sendmessage(User& liveUser) {
	// Data
	int receiverID;
	string username_receiver, msg;
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
		User* receiver = &users[receiverID];

		// check if blocked
		if (receiver->Blocked(liveUser.getid()))
			cout << "\nyou have been blocked by this user\n";
		


		//if (liveUser.Blocked(receiver))
		else
		{

			Message msgg_object(liveUser.getid(), receiverID, username_receiver, msg);
			// Check
			cout << "Send message? (y/n)" << " ";
			cin >> check;
			cout << "\n\n"; //line

			// Send Message
			if (check == 'y')
			{

				// Push in Sender messages
				liveUser.addToSent(msgg_object, *receiver);

				// push in reciver inbox
				receiver->addToInbox(msgg_object, *receiver);
				cout << "Message sent successfully." << " " << endl;
			}
			else
			{
				cout << "Message canceled." << " " << endl;
			}
		}
		cout << "\n"; //line
	}

}



void Program::undolastmessage(User &liveUser) {
	cout << endl << "Do You Want To Delete Last Message ? (y/n)" << " " << endl;
	char c;
	Message lastMsg;
	cin >> c;
	if (c == 'y') {
		// Pop in Sender messages and store popped message
		lastMsg = liveUser.popSent();
		cout << "1. Delete for you\n";

			cout << "\n1. Delete for me\n"
			<< "2. Delete for everyone\n";
		intChoice = getInt();
		switch (intChoice)
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
				if (!lastMsg.getIsRead())
					receiver->newMsgs--;
				break;
			}
			
		}
		default:
			cout << "Invalid choice, please try again!";
		}

	}
	else
		return;
}

//void Program::savefile() {
//	ofstream ourfile("ourdata.txt", ios::app);
//
//	if (ourfile.is_open()) {
//		for (auto it : users) {
//			ourfile << it.first << '|' << it.second.getUsername() << '|' << it.second.getPassword() << '|';
//			for (int i = 0; i < liveUser->sent.size(); i++) {
//				ourfile << it.second.sent[i].getSenderID() << '|' << it.second.sent[i].getReceiverID() << '|' << it.second.sent[i].getReceiverUsername() << '|' << it.second.sent[i].getContent() << "\n";
//			}
//			for (int i = 0; i < liveUser->inbox.size(); i++) {
//				ourfile << it.second.inbox[i].getSenderID() << '|' << it.second.inbox[i].getReceiverID() << '|' << it.second.inbox[i].getReceiverUsername() << '|' << it.second.inbox[i].getContent() << "\n";
//			}
//		}
//		/*for (auto elem : it.second.contacts) {
//		ourfile << elem.second << endl	}*/
//		//	for (auto elem : it.second.FavouriteMessages) {
//		//		ourfile << msg.getSenderID() << " " << msg.getReceiverID() << " " << msg.getReceiverUsername() << " " << msg.getContent() << "\n";
//		//	}
//
//	}
//	ourfile.close();
//}

//void Program::loadfile()
//{
//	ifstream ourfile("ourdata.txt");
//	string name,pass,n;
//	int id;
//	char delimiter = '|';
//	while (ourfile >> id) {
//		getline(ourfile, name, delimiter);
//		getline(ourfile, pass, delimiter);
//		users[id] = User(name, pass, id);
//	}
//}
/**void Program::loadfile()
{
	ifstream ourfile("ourdata.txt");
	string line;
	int id;
	string username;
	string password;
	stack<string> splitted;
//	while (ourfile) {*/
//		getline(ourfile, line);
//		splitted = split(line, ',');
//		while (!splitted.empty())
//		{
//			id = stoi(splitted.top());
//			splitted.pop();
//			username = splitted.top();
//			splitted.pop();
//			password = splitted.top();
//			splitted.pop();
//			//users.insert(make_pair(id, obj));
//			users[id] = User(username, password, id);
//			/*for (auto it : users) {
//				cout << it.first << it.second.username << " " << it.second.password;
//			}*/
//		}
//	}
//	ourfile.close();
//}
void Program::savefile()
{
	remove("data.txt");
	ofstream file("data.txt");
	file << userCount << endl;
	for (auto it : users)
	{
		file << it.second.getid() << " " << it.second.getUsername() << " " << it.second.getPassword() << " " << it.second.getReported() << " " << it.second.newMsgs << endl;
		//inbox
		file << it.second.getInbox().size() << endl;
		for (auto msg : it.second.getInbox())
		{
			file << msg.getSenderID() << " " << msg.getReceiverID() << " " << msg.getReceiverUsername() << endl;
			file << msg.getContent() << endl;
		}
		//sent
		file << it.second.getSent().size() << endl;
		for (auto msg : it.second.getSent())
		{
			file << msg.getSenderID() << " " << msg.getReceiverID() << " " << msg.getReceiverUsername() << endl;
			file << msg.getContent() << endl;
		}
		//favourites
		file << it.second.getFavouriteMessages().size() << endl;
		for (auto msg : it.second.getFavouriteMessages())
		{
			file << msg.getSenderID() << " " << msg.getReceiverID() << " " << msg.getReceiverUsername() << endl;
			file << msg.getContent() << endl;
		}
	}
	file.close();
	saveContacts();
}

void Program::saveContacts()
{
	remove("contacts.txt");
	ofstream file("contacts.txt");
	for (auto it : users) {
		file << it.first << endl;
		//contacts
		file << it.second.getContacts().size() << endl;
		for (auto c : it.second.getContacts())
		{
			file << c.first.getid() <<  " " << c.second << endl;
		}
		//blocked users
		file << it.second.getBlockedContacts().size() << endl;
		for (auto b : it.second.getBlockedContacts())
		{
			file << b.getid() << endl;
		}
	}
	file.close();
}
void Program::loadfile()
{
	ifstream file("data.txt");
	//user details
	int id, reported, newMsgs;
	string username;
	string password;
	//msg details
	Message msg;
	int containerSize, senderID, receiverID;
	string receiverUsername, content;

	file >> userCount;
	for (int i = 0; i < userCount; i++)
	{
		file >> id >> username >> password >> reported >> newMsgs;
		users[id] = User(username, password, id, reported, newMsgs);
		liveUser = &users[id];
		//inbox
		file >> containerSize;
		for (int i = 0; i < containerSize; i++)
		{
			file >> senderID >> receiverID >> receiverUsername;
			file.ignore();
			getline(file, content);
			msg = Message(senderID, receiverID, receiverUsername, content),
			liveUser->addToInbox(msg);
		}
		//sent
		file >> containerSize;
		for (int i = 0; i < containerSize; i++)
		{
			file >> senderID >> receiverID >> receiverUsername;
			file.ignore();
			getline(file, content);
			msg = Message(senderID, receiverID, receiverUsername, content),
				liveUser->addToSent(msg);
		}
		//favourites
		file >> containerSize;
		for (int i = 0; i < containerSize; i++)
		{
			file >> senderID >> receiverID >> receiverUsername;
			file.ignore();
			getline(file, content);
			msg = Message(senderID, receiverID, receiverUsername, content),
				liveUser->favourite(msg);
		}
		
	}
	loadContacts();
}

void Program::loadContacts()
{
	int liveUserID, containerSize, contactID, numOfMsgs;
	User contact;
	ifstream file("contacts.txt");
	for (int i = 0; i < userCount; i++)
	{
		file >> liveUserID;
		liveUser = idToUser(liveUserID);
		//contacts
		file >> containerSize;
		for (int i = 0; i < containerSize; i++)
		{
			file >> contactID >> numOfMsgs;
			contact = *idToUser(contactID);
			liveUser->addcontact(contact);
		}
		//blocked contacts
		file >> containerSize;
		for (int i = 0; i < containerSize; i++)
		{
			file >> contactID;
			contact = *idToUser(contactID);
			liveUser->blockContact(contact);
		}
	}
}

Program::~Program()
{
	savefile();
}

void Program::printDivider()
{
	printCentered("___________________________________________________");
}

void Program::contactMenu(User &liveUser, User &contact) {

	cout << "\n1. View sent messages\n"
		<< "2. Report\n"
		<< "3. Remove\n"
		<< "4. Block\n"
		<< "0. Back to previous menu \n";

	
	intChoice = getInt();
	switch (intChoice)
	{
	case 1:
		// view messages from contact
		cout << "\n";
		liveUser.viewContactMessages(contact);
		break;
	case 2:
		// report 
		cout << endl << "Report this contact? (y/n) ";
		cin >> check;
		if (check == 'y')
		{
			contact.beReported();
			cout << "Contact reported.\n";
		}
		break;
	case 3:
		liveUser.removecontact(contact);
		break;
	case 4:
		// block function
		liveUser.blockContact(contact);
		liveUser.removecontact(contact);
		cout << "Contact blocked. \n";
		break;
	case 0:
		break;
	default:
		cout << "Invalid entry! Please try again.";
	}
}

int Program::getInt()
{
	while (true) {
		string input;
		cin >> input ;
		try {
			 // Attempt to convert input to integer
			return stoi(input);
		}
		catch (invalid_argument& e) {
			cerr << "Invalid input! Please enter an integer." << endl;
		}
	}
}


//stack<string> Program::split(string s, char delim) 
//{
//	stack<string> result;
//	stringstream ss(s);
//	string item;
//
//	while (getline(ss, item, delim)) {
//		result.push(item);
//	}
//
//	return result;
//}
//usage
//vector<string> v = split(str, delimiter);
//for (auto i : v) cout << i << endl;