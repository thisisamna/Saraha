#include<iostream>
#include<fstream>
#include<string>
#include "log_in.h"
#include"registration.h"
using namespace std;
bool log_in::IsloggedIn(string name,string pass) {
	ifstream myfile("users.txt");
	if (myfile.is_open()) {
		string First_name, second_name2, pass;
		while (myfile >> First_name >> second_name2 >> pass) {
			if (name == (First_name + " " + second_name2) && pass == pass) {
				myfile.close();
				return 1;
			}
		}
	}
	myfile.close();
	return 0;
}

void log_in::logIn(){
	cout << "Enter your user name: \n";
	cin.ignore();
	getline(cin, username);
	cout << "Enter your password: \n";
	cin >> password;
}

void log_in::message() {
	if (IsloggedIn(username, password)) {
		cout << "Welcome " << username;
	}
	else
	{
		cout << "Your data is incorrect\nPlease try again!";
	}
}
