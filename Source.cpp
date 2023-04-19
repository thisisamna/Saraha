#include<iostream>
#include<fstream>
#include<string>
#include"registration.h"
#include"log_in.h"
using namespace std;
void main() {
	registration r;
	log_in l;
	int choice;
	cout << "\nClick 1 for registration\nClick 2 for log in\nClick -1 for end\n";
	cin >> choice;
	switch (choice)
	{
	case 1:
		system("cls");
		r.sign_up();
		main();
		break;
	case 2:
		system("cls");
		l.logIn();
		l.message();
		main();
		break;
	case -1:
		return;
	default:
		break;
	}

}