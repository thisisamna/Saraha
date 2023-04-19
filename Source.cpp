#include<iostream>
#include<fstream>
#include<string>
using namespace std;
void registration() {
	string username, password;
	ofstream myfile("users.txt", ios::app);
	cout << "Please! Enter your name...\n";
	cin.ignore();
	getline(cin,username);
	cout << "Please! Enter your password...\n";
	cin>>password;
	myfile << username<<"\t"<<password << "\n";
	myfile.close();
	cout << "Congratulation!!\nYou now have an account";
}
bool IsloggedIn(string username,string password) {
	ifstream myfile("users.txt");
	if (myfile.is_open()) {
		string First_name,second_name2,pass;
		while (myfile>> First_name >> second_name2 >> pass) {
			if (username==(First_name +" "+ second_name2) && password == pass) {
				myfile.close();
				return 1;
			}
		}
	}
	myfile.close();
	return 0;
}
void main() {
	string username, password;
	int choice;
	cout << "\nClick 1 for registration\nClick 2 for log in\nClick -1 for end\n";
	cin >> choice;
	switch (choice)
	{
	case 1:
		system("cls");
		registration();
		main();
		break;
	case 2:
		system("cls");
		cout << "Enter your user name: \n";
		cin.ignore();
		getline(cin, username);
		cout << "Enter your password: \n";
		cin >> password;
		if (IsloggedIn(username, password)) {
			cout << "Welcome " << username;
			main();
		}
		else
		{
			cout << "Your data is incorrect\nPlease try again!";
			main();
		}
	case -1:
		return;
	default:
		break;
	}

}