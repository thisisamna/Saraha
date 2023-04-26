#include "User.h"
#include <iostream>
#include <algorithm>
#include <map>
#include<vector>


using namespace std;
void User::addcontact(User u)
{
	bool userExists = false; // ترو لو اليوزر موجود بالفعل عندي

	for (User it : contacts) 
	{
		if (it.id == u.id)
		{
			cout << "\nUser already exists\n";
			userExists = true;
			break;
		}
	}// to check if user already exists


	if (!userExists) { // لو اليوزر مش عندي ضيفه
		contacts.push_back(u);
		msgcounter(u);
	}
}
void User::msgcounter(User) {
	//loop through each contact and count the number of messages exchanged 
	for (auto contact : contacts) {
		int numOfmsgs = 0;
		//count number of sent messages for this contact 
		for (auto msg : sent) {
			if (msg.get_sender() == contact.id) {
				numOfmsgs++;
			}
		}
		//count number of received messages from this contact 
		for (auto msg : inbox) {
			if (msg.get_receiver() == contact.id) {
				numOfmsgs++;
			}
		}
		numberOfmsg.insert(make_pair(contact, numOfmsgs));
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
		cout << "You haven't sent any messages yet.";
	}
	else
	{
		for(auto msg:sent)
		{
			msg.viewAsSent();
		}
	}
}

void User::viewReceived()
{
	if (inbox.empty())
	{
		cout << "Your inbox is empty.";
	}
	else
	{
		for (auto msg : sent)
		{
			msg.viewAsReceived();
		}
	}
} 

bool User::cmp(const pair<int, int>& a, const pair<int, int>& b)
{
	return a.second < b.second;
}
void User::viewcontacts() {
	vector < pair<User, int>>sortedContacts(numberOfmsg.begin(), numberOfmsg.end());
	sort(sortedContacts.begin(), sortedContacts.end(), cmp);
		
	

}

void User::sendmessage() {
	// Data
	string username_receiver, msg; char check;
	User receiver = null;
	// Create Message
	cout << endl << "Enter your message:" << " ";
	cin >> msg;

	cout << "Enter receiver username:" << " ";
	cin >> username_receiver;

	for (User it : contacts)
	{
		if (it.username == username_receiver)
		{
			Message msgg_object(this.id, username_receiver, msg);
			receiver = it;
			break;
		}
		else
		{
			cout << "receiver username doesnot found in your contacts" << endl;
		}
	}

	// Check
	cout << endl << "Send message? (y/n)" << " ";
	cin >> check;

	// Send Message
	if (c == 'y')
	{
		// Push in Sender messages
		this.sent.push_back(msgg_object);

		// push in reciver inbox
		receiver.inbox.push_back(msgg_object);
		cout << endl << "Message sent Successfully." << " " << endl;
	}
	else
	{
		cout << endl << "Message Doesnot Sent." << " " << endl;
	}


}

void User::undolastmessage() {
	cout << endl << "Do You Want To Delete Last Message ? (y/n)" << " " << endl;
	char c,cc;
	cin >> c;
	if (c == 'y') {
		cout << endl << "Do You Want To Delete It For You(1) OR For Everyone(0) ? " << " " << endl;
		cin >> cc;
		switch (cc)
		{
		case 1:
			this.sent.pop();
			break;
		case 0:
			receiver.inbox.pop();
			this.sent.pop();
			break;
		default:
			cout << "Invalid, PLZ try again!";
		}
	}
	else
		return;
}
