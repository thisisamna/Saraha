#include "User.h"
#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
#include <stack>
#include <deque>
#include <queue>
using namespace std;

User::User()
{
}
User::User(string name, string pass, int ID)
{
	username = name;
	password = pass;
	id = ID;
	reported = 0;
	newMsgs = 0;

}
User::User(string name, string pass, int ID, int _reported, int _newMsgs)
{
	username = name;
	password = pass;
	id = ID;
	reported = _reported ;
	newMsgs = _newMsgs;


}
bool User:: operator<(const User& other) const {
	return id < other.id;
}
int User::getid() 
{
	return id;
}
string User::getUsername()
{
	return username;
}

string User::getPassword()
{
	return password;
}

void User::viewContactMessages(User &contact) { //khira -- not sure if it works because i cant test it ):
	int j = 0;
	for (int i = 0; i < inbox.size(); i++) {
		if (inbox[i].getSenderID() == contact.getid()) 
		{
			cout << ++j << ". " << inbox[i].getContent() << endl;
		}
	}
	if (j == 0)
		cout << "No messages found!"; //if they were unsent
}
void User::addcontact(User contact)
{
	bool userExists = false; // ترو لو اليوزر موجود بالفعل عندي
	// to check if user already exists
	for (auto i : contacts) {
		if (i.first.id == contact.getid()) {
			userExists = true;
			cout << "\nThis user is already in your contacts.\n";
			break;
		}
	}
	
	if(!userExists) {// لو اليوزر مش عندي ضيفه
		contacts[contact]=msgcounter(contact);
		//cout << liveUser.contacts.size() << '\n';
		//cout << Added.getUsername() << ' ' << Added.getid() << '\n';
		cout << "\nSender added to contacts.\n";

	}

}



int User::msgcounter(User contact)
{
	int numOfmsgs = 0;
			//count number of sent messages for this contact 
	
	if (!sent.empty()) {
		for (int i = 0; i < sent.size(); i++) {
			if (sent.front().getReceiverID() == contact.getid()) {
				numOfmsgs++;
			}
			sent.push_back(sent.front());
			sent.pop_front();
		}
	}

	if (!inbox.empty()) {
		for (int i = 0; i < inbox.size(); i++) {
			if (inbox[i].getSenderID() == contact.getid()) 
				numOfmsgs++;
		}
	}
	
	return numOfmsgs;
}



Message User::getInboxMessage(int msgID)
{
	return inbox[msgID];
}

bool User::comparePassword(string pass)
{
	if (password == pass)
	{
		return true;
	}
	else 
	{
		return false;

	}
}

void User::addToSent(Message msg) // only used in load
{
	sent.push_front(msg);
}

void User::addToSent(Message msg,User &receiver)
{
	sent.push_front(msg);
	if (contacts.find(receiver) != contacts.end())
	{
		contacts[receiver]++;
	}
}
void User::addToInbox(Message msg) // only used in load
{
	inbox.push_back(msg);
}
void User::addToInbox(Message msg, User &sender)  //used in program
{
	inbox.push_back(msg);
	if (contacts.find(sender) != contacts.end())
	{
		contacts[sender]++;
	}
	newMsgs++;

}

Message User::popSent()
{
	Message msg = sent.front();
	sent.pop_front();
	return msg;
}
void User::removeFromInbox(Message msg)
{
	Message inboxMsg;
	for (int i=0; i<inbox.size(); i++)
	{
		inboxMsg = inbox[i];
		if (inboxMsg.equals(msg))
		{
			inbox.erase(inbox.begin() + i);
			break;
		}
	}
}

void User::beReported()
{
	reported++;
}

bool User::isBanned()
{
	if (reported >= 2)
		return true;
	else
		return false;
}

void User::blockContact(User & contact)
{
	blockedContacts.push_back(contact);
}

bool User::Blocked(int ID)
{
	for (int i = 0; i < blockedContacts.size(); i++)
	{
		
		if (blockedContacts.at(i).getid() == ID)
		{
			return true;
		}
	}
	return false;
}

map<User, int> User::getContacts()
{
	return contacts;
}

deque<Message> User::getFavouriteMessages()
{
	return FavouriteMessages;
}

vector<Message> User::getInbox()
{
	return inbox;
}

deque<Message> User::getSent()
{
	return sent;
}

int User::getReported()
{
	return reported;
}



void User::notify()
{
	if (newMsgs != 0)
		cout << "you have " << newMsgs << " unread messages. \n";

}



void User::removecontact(User contact)
{
	for (auto it = contacts.begin(); it != contacts.end();) {
		if (it->first.id == contact.id)
		{
			it = contacts.erase(it);
			cout << "Contact removed. \n";
			break;
		}
	}
}

void User::viewSent()
{
	cout << "\n"; //line
	if (sent.empty())
	{
		cout << "You haven't sent any messages yet.\n";
	}
	else
	{
		cout << "Sent messages from latest to oldest: " << endl;
		for (int i = 0; i < sent.size(); i++) 
		{
			sent.front().viewAsSent();
			sent.push_back(sent.front());
			sent.pop_front();
		}
	}
}

void User::viewReceived()
{
	if (inbox.empty())
	{
		cout << "Your inbox is empty.\n";
	}
	else
	{
		
		for (int i = 0; i < inbox.size(); i++) 
		{
			cout << i+1 << ". " << inbox[i].getContent() << endl;
			inbox[i].setIsRead(true);
		}
	}
	newMsgs = 0; //all messages are read

}



void User::viewcontacts() {
	cout << "\n"; //line
	if (contacts.size() == 0) {
		cout << "You don't have any contacts yet!\n";
	}
	else {
		cout << "Contacts: " << endl;
		vector<pair<User, int>>sorted_contacts;
		for (auto i : contacts) {
			sorted_contacts.push_back(i);
		}
		sort(sorted_contacts.begin(), sorted_contacts.end(), [](const pair<User, int>& a, const pair<User, int>& b) {
			return a.second > b.second;
			});
		for (auto i : sorted_contacts) {
			cout << "- ID: " << i.first.getid() << "\t\tNumber of messages: " << i.second << '\n';
		}
	}
}


void User::favourite(Message msg) {
	//bool MessageIsFavourite = false;
	//char answer;
	//for (int i = 0; i < FavouriteMessages.size(); i++) {

	//	if (msg.getContent() == FavouriteMessages.at(i).getContent()) {
	//		MessageIsFavourite = true;
	//		cout << "Message is already favourite press 'Y' if you want to remove it \n";
	//		cout << "Or 'N' to remain it\n";
	//		cin >> answer;
	//		if (answer == ('y') || answer == 'Y')
	//			FavouriteMessages.erase(FavouriteMessages.begin() + i);
	//		else if (answer == ('N') || answer == 'n')
	//			break;
	//	}

	//}
	//if (!MessageIsFavourite) {
		FavouriteMessages.push_back(msg);
	/*}*/
}
void User::RemoveOldestFavorite(){
   FavouriteMessages.pop_front();
   cout << "Oldest favorite removed.\n";
}

void User::viewFavorites()
{
	if (FavouriteMessages.empty())
	{
		cout << "You don't have any favorite messages yet.\n";
	}
	else
	{
		cout << "Favorite messages from oldest to latest: " << endl; //3ashan ne3raf ha pop mnen
		for (int i = 0; i < FavouriteMessages.size(); i++)
		{
			FavouriteMessages.front().viewAsReceived();
			FavouriteMessages.push_back(FavouriteMessages.front());
			FavouriteMessages.pop_front();
		}
	}
}


//search contact by his id
void User::searchContact(int id) {
	bool found = false;
	for (auto i : contacts) {
		if (i.first.id == id) {
			found = true;
			break;
		}
	}
	if (found) {
		cout << "Contact Found !\n";
	}
	else {
		cout << "Contact not Found ! \n";
	}
}


//The next fucntion goes against the requirements
// 
//void User::searchContactbyname(string username) {
//	bool found = false;
//	User it;
//	for (auto i : contacts) {
//		if (i.first.username == username) {
//			found = true;
//			it = i.first;
//			break;
//		}
//	}
//	if (found) {
//		cout << "Contact Found !\n Name : " << username << "\t Id : " << it.getid() << '\n';
//	}
//	else {
//		cout << "Contact not Found ! , check if the entered username is correct \n";
//	}
//
//}