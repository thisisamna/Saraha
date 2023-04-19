#include<iostream>
#include<fstream>
#include<string>
#include "registration.h"
registration::registration() {
	username = "";
	password = "";
}

void registration::sign_up() {
	string username, password;
	ofstream myfile("users.txt", ios::app);
	cout << "Please! Enter your name...\n";
	cin.ignore();
	getline(cin, username);
	cout << "Please! Enter your password...\n";
	cin >> password;
	myfile << username << "\t" << password << "\n";
	myfile.close();
	cout << "Congratulation!!\nYou now have an account";
}

registration::~registration() {
}

