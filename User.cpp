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

void User::addcontact(User  &liveUser ,User &Added)
{
	bool userExists = false; // ترو لو اليوزر موجود بالفعل عندي
	int s = (int)liveUser.contacts.size();
	map<User, int>temp = liveUser.contacts;
	// to check if user already exists
	if (liveUser.contacts.find(Added) != liveUser.contacts.end()) {
		userExists = true;
		cout << "This user is already in your contacts.\n";
	}
	if(!userExists) {// لو اليوزر مش عندي ضيفه
		liveUser.contacts.insert({ Added,msgcounter(Added,liveUser) });
		cout << "Sender added to contacts.\n";

	}


}



int User::msgcounter(User &AddedContact, User &liveUser) 
{
	int numOfmsgs = 0;
			//count number of sent messages for this contact 
	
	if (!liveUser.sent.empty()) {
		for (int i = 0; i < liveUser.sent.size(); i++) {
			if (liveUser.sent.front().getReceiverID() == AddedContact.getid()) {
				numOfmsgs++;
			}
			liveUser.sent.push_back(liveUser.sent.front());
			liveUser.sent.pop_front();
		}
	}

	if (!liveUser.inbox.empty()) {
		for (int i = 0; i < liveUser.inbox.size(); i++) {
			if (liveUser.inbox[i].getSenderID() == AddedContact.getid()) 
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

void User::addToSent(Message msg,User &liveUser,User &received)
{
	sent.push_front(msg);
	liveUser.contacts[received]++;
}

void User::addToInbox(Message msg, User &liveUser, User &sender) 
{
	inbox.push_back(msg);
	liveUser.contacts[sender]++;
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
}


void User::viewMessageOptions(int i)
{

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
	}
	
}
//Favourites have 10 only if more we remove the oldest favourite
void User::RemoveOldestFavorite(){
   FavouriteMessages.erase(FavouriteMessages.begin()+0);
}

void User::viewFavorites(){
	for(int i = 0; i < FavouriteMessages.size(); i++){
		cout << FavouriteMessages[i].getContent();
		cout << endl;
	}
}


//search contact by his id
void User::searchContactbyid(int id) {
	bool found = false;
	User it;
	for (auto i : contacts) {
		if (i.first.id == id) {
			found = true;
			it = i.first;
			break;
		}
	}
	if (found) {
		cout << "Contact Found !\n Name : " << it.getUsername() << "\t Id : " << id << '\n';
	}
	else {
		cout << "Contact not Found ! , check if the entered id is correct \n";
	}
}

void User::searchContactbyname(string username) {
	bool found = false;
	User it;
	for (auto i : contacts) {
		if (i.first.username == username) {
			found = true;
			it = i.first;
			break;
		}
	}
	if (found) {
		cout << "Contact Found !\n Name : " << username << "\t Id : " << it.getid() << '\n';
	}
	else {
		cout << "Contact not Found ! , check if the entered username is correct \n";
	}

}