#include "User.h"
#include <iostream>
#include "Message.h"
#include <algorithm>
#include <map>
#include <vector>
#include <stack>
#include <deque>


using namespace std;
User::User() //Wessal
{
}
User::User(string username, string password) //Wessal
{
	
}
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



	if(!userExists) // لو اليوزر مش عندي ضيفه
{
		contacts.push_back(u);
		msgcounter(u);
	}
}

void User::msgcounter(User) {
	//loop through each contact and count the number of messages exchanged 
	for (auto contact : contacts) {
		int numOfmsgs = 0;
		//count number of sent messages for this contact 

		if (!sent.empty()) {
			for (int i = 0; i < sent.size(); i++) {
				if (sent.front().getSender() == contact.id) {
					numOfmsgs++;
				}
				sent.push_back(sent.front());
				sent.pop_front();
			}
		}
		//count number of received messages from this contact 
		for (auto msg : inbox) {
			if (msg.getReceiver() == contact.id) {
				numOfmsgs++;
			}
		}
		sortedContacts.push_back(make_pair(contact, numOfmsgs));
	}
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
			cout << i << ". " << inbox[i].getContent() << endl;
		}
	}
}


void User::viewMessageOptions(int i)
{

}


void User::viewcontacts() {
	sort(sortedContacts.begin(), sortedContacts.end(), [](pair<User,int>& a, pair<User,int>& b) {
		return a.second > b.second;
		}
	);
	for (auto i : sortedContacts) {
		cout << i.first.id << "		" << i.second << '\n';
	}
}

void User::sendmessage() {
	// Data
	string username_receiver, msg; char check;
	//User receiver = null;
	// Create Message
	cout << endl << "Enter your message:" << " ";
	cin >> msg;

	cout << "Enter receiver username:" << " ";
	cin >> username_receiver;
	User receiver = usernameToUser(username_receiver);
	if (receiver == null){
		cout <<endl<< "receiver username invalid, PLZ Try Again.<< " ";
	break;
	}
	Message msgg_object(this.id, username_receiver, msg);
	/*for (User it : contacts)
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
	}*/

	// Check
	cout << endl << "Send message? (y/n)" << " ";
	cin >> check;

	// Send Message
	if (check == 'y')
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
	string recevier_username;
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
			cout << "Enter receiver username:" << " ";
			User receiver = usernameToUser(recevier_username);
			if (receiver == null) {
				cout << endl << "receiver username invalid, PLZ Try Again.<< " ";
					break;
			}
			receiver.inbox.pop();
			this sent.pop();
			break;
		default:
			cout << "Invalid, PLZ try again!";
		}
	}
	else
		break;
}




void favourite(Message msg) {
	vector <Message> FavouriteMessages;
	bool MessageIsFavourite = false;
	char answer;
	for (int i = 0; i < FavouriteMessages.size(); i++) {
		
		if (msg.getContent() == FavouriteMessages.at(i).getContent()) {
			MessageIsFavourite = true;

			cout << "Message is already favourite press 'Y' if you want to remove it \n";
			cout << "Or 'N' to remain it\n";
			cin >> answer;


			if (answer == ('y' || 'y')) {
				FavouriteMessages.erase(FavouriteMessages.begin() + i);
				break;
			}
			else if (answer == ('N' || 'n'))
				break;
		}

		
	}
	if(!MessageIsFavourite)
	FavouriteMessages.push_back(msg);
}
