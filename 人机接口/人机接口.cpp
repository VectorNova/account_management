#include<cstdio>
#include<cstdlib>
#include<iostream>
using namespace std;

void print_menu();

int main()
{
	cout << "Welcome to the Billing Management System" << endl;
	int choice;
	while (true) {
		print_menu();
		cin >> choice;
		switch (choice) {
			case 1:cout << "Add card" << endl<<endl; break;
			case 2:cout << "Query card" << endl<<endl; break;
			case 3:cout << "Login" << endl<<endl; break;
			case 4:cout << "Logout" << endl<<endl; break;
			case 5:cout << "Recharge" << endl<<endl; break;
			case 6:cout << "Refund" << endl<<endl; break;
			case 7:cout << "Statistics" << endl<<endl; break;
			case 8:cout << "Cancel card" << endl<<endl; break;
			case 0:cout << "Exit" << endl<<endl; break;
			default:cout << "Error, please write again" << endl<<endl;
		}
		if (choice == 0) break;
	}
	return 0;
}

// print menu function
void print_menu()
{
	cout << "---------- Menu ----------" << endl;
	cout << "1. Add card" << endl << "2. Query card" << endl << "3. Login" << endl;
	cout << "4. Logout" << endl << "5. Recharge" << endl << "6. Refund" << endl;
	cout << "7. Statistics" << endl << "8. Cancel card" << endl << "0. Exit" << endl;
	cout << "Please choose an option (0-8):";
}