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

int User::getid() 
{
	return id;
}
string User::getUsername()
{
	return username;
}

void User::addcontact(User* liveUser, User* Added)
{
	bool userExists = false; // ترو لو اليوزر موجود بالفعل عندي
	int s = liveUser->contacts.size();
	for (int i = 0; i < s; i++){
		if (liveUser->contacts[i].first->getid()== Added->getid()) {
			cout << "\nUser already exists in contacts\n";
			userExists = true;
			break;
		}
    }
	// to check if user already exists

	if(!userExists) {// لو اليوزر مش عندي ضيفه
		liveUser->contacts.push_back(make_pair(Added, msgcounter(liveUser, Added)));
	}


}



int User::msgcounter(User *AddedContact, User* liveUser) 
{
	int numOfmsgs = 0;
			//count number of sent messages for this contact 
	
	if (!liveUser->sent.empty()) {
		for (int i = 0; i < liveUser->sent.size(); i++) {
			if (liveUser->sent.front().getReceiverID() == AddedContact->getid()) {
				numOfmsgs++;
			}
			liveUser->sent.push_back(liveUser->sent.front());
			liveUser->sent.pop_front();
		}
	}

	if (!liveUser->inbox.empty()) {
		for (int i = 0; i < liveUser->inbox.size(); i++) {
			if (liveUser->inbox[i].getSenderID() == AddedContact->getid()) 
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

void User::addToSent(Message msg)
{
	sent.push_front(msg);
	contacts[msg.getReceiverID()].second++;

}

void User::addToInbox(Message msg)
{
	inbox.push_back(msg);
	contacts[msg.getSenderID()].second++;
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
	cout << "Contacts: " << endl;

	for (int i = 0; i < contacts.size(); i++) {
		cout << i+1 << "." << contacts[i].first->getUsername() << endl;
		

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