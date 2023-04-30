#include "User.h"
#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
#include <stack>
#include <deque>
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

int User::getid() 
{
	return id;
}
string User::getUsername()
{
	return username;
}

void User::addcontact(User u)
{
	bool userExists = false; // ترو لو اليوزر موجود بالفعل عندي

	for (User it : contacts) 
	{
		if (it.id == u.id)
		{
			cout << "\nUser already exists in contacts\n";
			userExists = true;
			break;
		}
	}// to check if user already exists

	if(!userExists) {// لو اليوزر مش عندي ضيفه
		contacts.push_back(u);
		msgcounter(u);
		cout << "User added\n";
	}
}

//void User::msgcounter(User u) {
//	//loop through each contact and count the number of messages exchanged 
//	for (auto contact : contacts) {
//		int numOfmsgs = 0;
//		//count number of sent messages for this contact 
//
//		if (!sent.empty()) {
//			for (int i = 0; i < sent.size(); i++) {
//				if (sent.front().getSender() == contact.id) {
//					numOfmsgs++;
//				}
//				sent.push_back(sent.front());
//				sent.pop_front();
//			}
//		}
//		//count number of received messages from this contact 
//		for (auto msg : inbox) {
//			if (msg.getReceiver() == contact.id) {
//				numOfmsgs++;
//			}
//		}
//		sortedContacts.push_back(make_pair(contact, numOfmsgs));
//	}
//}

void User::msgcounter(User u) // still cant figure how to get the id of the user calling the function
{

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

void User::addToSent(Message msg)
{
	sent.push_front(msg);
}

void User::addToInbox(Message msg)
{
	inbox.push_back(msg);
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
			cout << "Message removed";
			break;
		}
	}
}

void User::removecontact(User u)
{
	int i = -1;

	for (User it : contacts)
	{
		i++;
		if (it.id == u.id)
			break;
	}
	contacts.erase(contacts.begin() + i);
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
	sort(sortedContacts.begin(), sortedContacts.end(), [](pair<User,int>& a, pair<User,int>& b)
		{
		return a.second > b.second;
		}
	);
	for (auto i : sortedContacts) {
		cout << i.first.id << "		" << i.second << '\n';
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


			if(answer==('y' ||'Y'))
			FavouriteMessages.erase(FavouriteMessages.begin()+i);

			else if (answer == ('N' || 'n'))
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