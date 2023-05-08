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
	id = 0;
	username = "please";
	password = "work";

}
User::User(string name, string pass, int ID)
{
	username = name;
	password = pass;
	id = ID;
	reported = 0;
	
} // added the id to constructor to set the id for every user
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

void User::viewContactMessages(User contact) { //khira -- not sure if it works because i cant test it ):
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
			cout << "This user is already in your contacts.\n";
			break;
		}
	}
	
	if(!userExists) {// لو اليوزر مش عندي ضيفه
		contacts[contact]=msgcounter(contact);
		//cout << liveUser.contacts.size() << '\n';
		//cout << Added.getUsername() << ' ' << Added.getid() << '\n';
		cout << "Sender added to contacts.\n";

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

void User::addToSent(Message msg,User &receiver)
{
	sent.push_front(msg);
	if (contacts.find(receiver) != contacts.end())
	{
		contacts[receiver]++;
	}
}

void User::addToInbox(Message msg, User &sender) 
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

void User::notify()
{
	if (newMsgs != 0)
		cout << "you have " << newMsgs << " unread messages. \n";

}

void User::removecontact(User &u)
{
	/*int i = -1;

	for (User it : contacts)
	{
		i++;
		if (it.id == u.id)
			break;
	}
	contacts.erase(contacts.begin() + i);*/
}

void User::viewSent()
{
	if (sent.empty())
	{
		cout << "You haven't sent any messages yet.\n";
	}
	else
	{
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
		}
	}
	newMsgs = 0; //all messages are read

}



void User::viewcontacts() {
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
		int cnt = 1;
		for (auto i : sorted_contacts) {
			cout << cnt << ' ' << i.first.getid() << "   number of messages : " << i.second << '\n';
		}
	}
}


void User::favourite(Message msg) {
	bool MessageIsFavourite = false;
	char answer;
	for (int i = 0; i < FavouriteMessages.size(); i++) {
		
		if (msg.getContent() == FavouriteMessages.at(i).getContent()) {
			MessageIsFavourite = true;
			cout << "Message is already favourite press 'Y' if you want to remove it \n";
			cout << "Or 'N' to remain it\n";
			cin >> answer;
			if(answer==('y' )||answer=='Y')
			FavouriteMessages.erase(FavouriteMessages.begin()+i);
			else if (answer == ('N')||answer== 'n')
				break;
		}

	}
	if(!MessageIsFavourite){
		if(FavouriteMessages.size()<=10){
			FavouriteMessages.push_back(msg);
		}
		else{
			RemoveOldestFavorite();
			FavouriteMessages.push_back(msg);
		}
		cout << "Message added to favorites." << endl;
	}
	
}
//Favourites have 10 only if more we remove the oldest favourite
void User::RemoveOldestFavorite(){
   FavouriteMessages.erase(FavouriteMessages.begin()+0);
}

void User::viewFavorites(){
	for(int i = 0; i < FavouriteMessages.size(); i++){
		FavouriteMessages[i].viewAsReceived();
	}
}


//search contact by his id
void User::searchContactbyid(int id) {
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