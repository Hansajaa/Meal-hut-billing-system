#include <iostream>
#include <fstream>
#include <string>
#include <typeinfo>
#include <limits>
#include <iomanip>
#include <stdlib.h>
#include <cstdlib>
#include <ctime>
using namespace std;

//item structure
struct Item{
	int itemNo = 0;
	string itemName;
	double itemPrice = 0.0;
};

//order structure
struct Order {
	int itemNo = 0;
	string itemName;
	int quantity = 0;
	double itemPrice = 0.0;
	double total = 0.0;
};

//load data into menuList array
void getData(Item menuList[]) {
	int itemsID[8] = { 111, 112, 113, 114, 115, 116, 117, 118 }; //items IDs
	string itemsName[8] = { "Plain Egg", "Bacon and Egg", "Muffin", "French Toast", "Fruit Basket", "Cereal", "Coffee", "Tea" }; //items names
	double itemsPrice[8] = { 1.45 , 2.45 , 0.99 , 1.99 , 2.49 , 0.69 , 0.50 , 0.75  }; //items prices

	for (int i = 0; i < 8; i++) { // loop through add items to the menuList array
		menuList[i].itemNo = itemsID[i];
		menuList[i].itemName = itemsName[i];
		menuList[i].itemPrice = itemsPrice[i];
	}
}

//show menu
void displayMenu(Item menuList[]) {

	//Table headers
	cout << " _________________________________________________" << endl;
	cout << "|" << setw(11) << "Item ID|";
	cout << setw(21) << "Menu Item |";
	cout << setw(18) << "Price |" << endl;
	cout << " -------------------------------------------------" << endl;

	//items
	for (int i = 0; i < 8; i++) {

		cout << "|" << setw(10) << menuList[i].itemNo << "|";
		cout << setw(20) << menuList[i].itemName << "|";
		cout << setw(13) << "$" << fixed << setprecision(2) << menuList[i].itemPrice <<"|" << endl;
	}

	cout << "|_________________________________________________|\n" << endl;
}

void addItemsToOrder(Order orderList[], Item menuList[], int &lastIndexofOrder) {

	int itemNo = 0;
	int quantity;


	//show currently added products and their quantity
	cout << "\n**** Items in cart ****" << endl;
	cout << " -----------------------------------" << endl;
	cout << "|" << setw(20) << "item" << "|" << setw(15) << "   quantity|" << endl;
	cout << " -----------------------------------" << endl;

	//check if cart empty
	if (lastIndexofOrder == 0) {
		cout << "|     Cart is currently empty \t    |" << endl;
	}

	//if products exists in cart show them for user to get understand of their cart status
	for (int i = 0; i < lastIndexofOrder; i++){
		cout << "|" << setw(20) << orderList[i].itemName << "|" << setw(14) << orderList[i].quantity << "|" << endl;
	}
		
	cout << " -----------------------------------" << endl;

	cout << "\nEnter the item ID (eg - 111 ) : ";
	cin >> itemNo;

	if (!cin || cin.fail()) { //check is input not an expected type

		cout << "\t\t\t\t\tPlease Enter between 111 and 118" << endl;
		cin.clear(); //reset the error flag
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); //clear input buffer
		return;

	}else if(!(itemNo >= 111 && itemNo <= 118)) {

		cout << "\t\t\t\t\tInvalid item ID. Please enter a valid item ID." << endl;
		return;

	}else {
		

		for (int i = 0; i < lastIndexofOrder; i++){
			if (itemNo == orderList[i].itemNo) {

				if (orderList[i].quantity == 50) {
					cout << "\n\t\t\t\t\tAlready maximum quantities are added to " << orderList[i].itemName << " !" << endl;
					return;
				}else {
					do{
						try {
							char isContinue;
							string input;

							cout << "\nItem already added to the order. Do you want add more quantity for " << orderList[i].itemName << ". ( y/n ) : ";
							cin >> input;

							isContinue = input[0];

							if (input.length() != 1) {
								cout << "\n\t\t\t\t\tPlease enter exactly one character (y/n)!" << endl;
								continue;
							}else if (isContinue == 'y' || isContinue == 'Y') {
								//get quantity for already added item and update if user want

								do {
									cout << "Enter quantity (1 - 50) : ";
									cin >> quantity;

									if (!cin || cin.fail()) {
										cout << "\t\t\t\t\tInvalid input. Please enter a between 1 and 50." << endl;
										cin.clear(); //reset the error flag
										cin.ignore(numeric_limits<streamsize>::max(), '\n'); //clear input buffer
									}else if (!(quantity >= 1 && quantity <= 50)) {
										cout << "\t\t\t\t\tInvalid quantity. Please enter a valid quantity." << endl;
									}

								} while (!(quantity >= 1 && quantity <= 50) || (!cin || cin.fail()));

								if ((orderList[i].quantity + quantity) > 50) {

							
									do{
									
										cout << "\n" << orderList[i].itemName << " quantity limit is exceed after adding " << quantity << " quantities. Do you want add 50 quantity of " << orderList[i].itemName << " into this order. ( y/n ) :  ";
										cin >> input;

										isContinue = input[0];

										if (input.length() != 1) {
											cout << "\n\t\t\t\t\tPlease enter exactly one character (y/n)!" << endl;
											continue;
										}else if (isContinue == 'y' || isContinue == 'Y') {
											orderList[i].quantity = 50;
											cout << "\t\t\t\t\tQuantity is updated for " << orderList[i].itemName << "." << endl;
											return;
										}else if (isContinue == 'n' || isContinue == 'N'){
											return;
										}else {
											cout << "\t\t\t\t\tIncorrect answer Please enter ( y/n ) !" << endl;
											continue;
										}
									
									} while (true);
							
								}else {
									orderList[i].quantity += quantity;
									cout << "\t\t\t\t\tQuantity is updated for " << orderList[i].itemName << "." << endl;
									return;
								}

							}else if (isContinue == 'n' || isContinue == 'N') {
								return;
							}else {
								cout << "\t\t\t\t\tIncorrect answer Please enter ( y/n ) !" << endl;
								continue;
							}

						}catch (const std::exception& e) {
							cout << "\t\t\t\t\tUnexpected error occured : " << e.what() << endl;
							cin.clear();
							cin.ignore(numeric_limits<streamsize>::max(), '\n');
						}

					} while (true);
				}
				
				
			}
		}

		do{
			cout << "Enter quantity (1 - 50) : ";
			cin >> quantity;

			if (!cin || cin.fail()) {
				cout << "\t\t\t\t\tInvalid input. Please enter a between 1 and 50." << endl;
				cin.clear(); //reset the error flag
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); //clear input buffer
			}else if (!(quantity >= 1 && quantity <= 50)) {
				cout << "\t\t\t\t\tInvalid quantity. Please enter a valid quantity." << endl;
			}

		} while (!(quantity >= 1 && quantity <= 50) || (!cin || cin.fail()));


		for (int i = 0; i < 8; i++) {
			if (menuList[i].itemNo == itemNo) {
				orderList[lastIndexofOrder].itemNo = menuList[i].itemNo;
				orderList[lastIndexofOrder].itemName = menuList[i].itemName;
				orderList[lastIndexofOrder].itemPrice = menuList[i].itemPrice;
				orderList[lastIndexofOrder].quantity = quantity;
				orderList[lastIndexofOrder].total = menuList[i].itemPrice * quantity;
				lastIndexofOrder++;
				cout << "\t\t\t\t\tItem Added successfully !\n" << endl;
			}
		}

	}

}

//place a new order
void placeOrder(Order orderList[], Item menuList[], int& lastIndexofOrder) {

	char isContinue;
	string input;

	do{
		displayMenu(menuList);
		addItemsToOrder(orderList, menuList, lastIndexofOrder);

		do {
			cout << "\n\nDo you want to add more items (y/n) : ";
			cin >> input;

			isContinue = input[0]; // string varible 0 index assign to the char variable

			if (input.length() != 1) { //check length
				cout << "\n\t\t\t\t\tPlease enter exactly one character (y/n)!" << endl;
				continue;
			}else if (isContinue == 'n' || isContinue == 'N') {
				system("cls"); //clear the console
				if (lastIndexofOrder != 0) {
					cout << "\t\t\t\t\tOrder Placed Successfully !" << endl;
				}
				break;
			}else if (isContinue == 'y' || isContinue == 'Y') {
				system("cls"); //clear the console
				break;
			}else {
				cout << "\t\t\t\t\tIncorrect answer Please enter ( y/n ) !" << endl;
				continue;
			}

		} while (true);

	} while (isContinue == 'y' || isContinue == 'Y');


}

//bill save into txt file
void billSaveIntoFile(Order orderList[], int &lastIndexOfOrder, double &tax, double &tot, string &orderID) {
	
	fstream myFile;

	time_t now = time(0);
	char str[26];
	ctime_s(str, sizeof str, &now);

	//you need to copy local location path into orders.txt file
	myFile.open("C:\\ICBT\\Fip\\1st Sem\\Assignment\\Meal-hut-billing-system\\orders.txt", ios::app);
	if (myFile.is_open()) {

		myFile << "Date - " << str << endl;

		myFile << "\nOrder ID - " << orderID << endl;
		
		//append and save bill into the file
		myFile << " ___________________________________________________________________________________________________________" << endl;
		myFile << "|" << setw(18) << "Item ID|";
		myFile << setw(30) << "Menu Item|";
		myFile << setw(20) << "Price per Item|";
		myFile << setw(20) << "Quantity|";
		myFile << setw(20) << "Total Price |" << endl;
		myFile << " -----------------------------------------------------------------------------------------------------------" << endl;

		for (int i = 0; i < lastIndexOfOrder; i++) {

			myFile << "|" << setw(17) << orderList[i].itemNo << "|";
			myFile << setw(29) << orderList[i].itemName << "|";
			myFile << setw(15) << "$" << fixed << setprecision(2) << orderList[i].itemPrice << "|";
			myFile << setw(19) << orderList[i].quantity << "|";
			myFile << setw(15) << "$" << fixed << setprecision(2) << orderList[i].total << "|" << endl;
		}

		myFile << " -----------------------------------------------------------------------------------------------------------" << endl;
		myFile << "\t\t\t\t\t\t\t\t    | Tax \t\t|" << setw(15) << "$" << fixed << setprecision(2) << tax << "|" << endl;

		myFile << "\t\t\t\t\t\t\t\t    | --------------------------------------|" << endl;

		myFile << "\t\t\t\t\t\t\t\t    | Amount Due\t|" << setw(15) << "$" << fixed << setprecision(2) << tot + tax << "|" << endl;

		myFile << "\t\t\t\t\t\t\t\t    | ______________________________________|" << endl;

		myFile << "\n\n****************************************************************************************************************************\n" << endl;
		
		myFile.close();
	}else {
		cout << "\t\t\t\t\tFile Not Found !\n\n" << endl;
	}

	
}

//print the bill
void printBill(Order orderList[], int &lastIndexOfOrder) {


	int randomNum1 = rand() % 1000000000000001;
	int randomNum2 = rand() % 101;
	int randomNum3 = rand() % 11;

	int ordNo = randomNum1 + randomNum2 + randomNum3;
	string orderID = "ORD-" + to_string(ordNo);

	if (lastIndexOfOrder != 0) {
		double tax;
		double tot = 0.0;

		cout << "\n\n\t\t\t******************** Bill ********************\n" << endl; //title

		cout << "Order ID - " << orderID << "\n" << endl;

		//Table headers
		cout << " ___________________________________________________________________________________________________________" << endl;
		cout << "|" << setw(18) << "Item ID|";
		cout << setw(30) << "Menu Item|";
		cout << setw(20) << "Price per Item|";
		cout << setw(20) << "Quantity|";
		cout << setw(20) << "Total Price |" << endl;
		cout << " -----------------------------------------------------------------------------------------------------------" << endl;

		for (int i = 0; i < lastIndexOfOrder; i++) {
			tot += orderList[i].total; // calculate total of all items

			cout << "|" << setw(17) << orderList[i].itemNo << "|";
			cout << setw(29) << orderList[i].itemName << "|";
			cout << setw(15) << "$" << fixed << setprecision(2) << orderList[i].itemPrice << "|";
			cout << setw(19) << orderList[i].quantity << "|";
			cout << setw(15) << "$" << fixed << setprecision(2) << orderList[i].total << "|" << endl;
		}

		tax = tot * 0.05; //calculate tax

		cout << " -----------------------------------------------------------------------------------------------------------" << endl;
		cout << "\t\t\t\t\t\t\t\t    | Tax \t\t|" << setw(15) << "$" << fixed << setprecision(2) << tax << "|" << endl;

		cout << "\t\t\t\t\t\t\t\t    | --------------------------------------|" << endl;

		cout << "\t\t\t\t\t\t\t\t    | Amount Due\t|" << setw(15) << "$" << fixed << setprecision(2) << tot + tax << "|" << endl;

		cout << "\t\t\t\t\t\t\t\t    | ______________________________________|" << endl;


		billSaveIntoFile(orderList, lastIndexOfOrder, tax, tot, orderID);
	}
	
}

//get orders
void getOrders(string username) {
	
	Item menuList[8]; // array of items

	getData(menuList); // load data into menuList array

	string input;
	char isContinue;

	cout << "Welcome " << username << endl;

	do {
		Order orderList[8]; // array of orders
		int lastIndexofOrder = 0; // last index of orderList array

		cout << "\n\n\t\t\t******************** New Order ********************\n" << endl;

		placeOrder(orderList, menuList, lastIndexofOrder); // get order
		printBill(orderList, lastIndexofOrder); //print the bill

		do{
			cout << "\n\nDo you want to place a new order (y/n) : ";
			cin >> input;
			
			isContinue = input[0]; // string varible 0 index assign to the char variable

			if (input.length() != 1) { //check length
				cout << "\n\t\t\t\t\tPlease enter exactly one character (y/n)!" << endl;
				continue;
			}else if (isContinue == 'n' || isContinue == 'N') {
				system("cls"); //clear the console after place an every order
				break;
			}else if(isContinue == 'y' || isContinue == 'Y'){
				system("cls"); //clear the console after place an every order
				break;
			}else {
				cout << "\t\t\t\t\tIncorrect answer Please enter ( y/n ) !" << endl;
				continue;
			}

		} while (true);

	} while (isContinue == 'y' || isContinue == 'Y');

	system("cls");
}

//authenticate user
string authentication() {
	string USERNAME = "admin";
	string PASSWORD = "1234";

	string iUsername;
	string iPassword;

	do {
		cout << "Enter Username : ";
		getline(cin, iUsername);

		if (!cin || cin.fail()) {
			cout << "\t\t\t\t\tSomething wrong, Try Again" << endl;
			continue;
		}else {
			//check username
			if (iUsername == USERNAME) {
				break;
			}else {
				cout << "\t\t\t\t\tIncorrect username" << endl;
				continue;
			}
		}
	} while (true);

	do {
		cout << "Enter Password : ";
		getline(cin, iPassword);

		if (!cin || cin.fail()) {
			cout << "\t\t\t\t\tSomething wrong, Try Again" << endl;
			continue;
		}else {
			//check username
			if (iPassword == PASSWORD) {
				break;
			}else {
				cout << "\t\t\t\t\tIncorrect password" << endl;
				continue;
			}
		}
	} while (true);

	system("cls"); //clear after login

	return iUsername;

}

void viewAllOrders() {
	cout << "\t\t\t\t*********** All Orders **************\n\n" << endl;

	fstream myFile;
	myFile.open("C:\\ICBT\\Fip\\1st Sem\\Assignment\\Meal-hut-billing-system\\orders.txt", ios::in);
	if (myFile.is_open()) {
		string line;
		while (getline(myFile, line)) {
			cout << line << endl;
		}

		myFile.close();
	}else {
		cout << "\t\t\t\t\tFile Not Found !" << endl;
	}

	string input;
	
	do{
		cout << "\n\n\nDo you want go to home page press enter.";
		getline(cin, input);

		if (cin.get() == '\n') {
			break;
		}
	} while (true);
}

void showOptions(string username) {


	int opt;
	string input;

	do{
		cout << "\t\t\t\t******** Welcome to Meal Hut *********\n" << endl; //title	
		
		//show options
		cout << "\n1. Add an order" << endl;
		cout << "2. View all orders" << endl;
		cout << "3. Exit" << endl;

		//get input from user
		cout << "\nSelect one option : ";
		getline(cin, input);

		//check user enter empty value
		if (input.empty()) {
			cout << "\t\t\t\t\tInput cannot be empty. Try again!\n" << endl;
		}else if(input.length() != 1){
			cout << "\t\t\t\t\tInvalid input. Try again!\n" << endl;
		}else{
			
			system("cls");
			try {
				opt = stoi(input); // Try to convert input to integer

				if (opt >= 1 && opt <= 3) { //check range
					if (opt == 1) {
						system("cls"); //clear the console
						getOrders(username);
						continue;
					}else if (opt == 2) {
						system("cls"); //clear the console
						viewAllOrders();
						system("cls"); //clear the console
						continue;
					}else {
						exit(0);
					}
				}else { // if user enter out of range number display error message
					cout << "\t\t\t\t\tNumber out of range!\n" << endl;
					continue;
				}

			}catch (const std::invalid_argument&) {
				cout << "\t\t\t\t\tInvalid input. Please enter a number!\n" << endl;
				continue;
			}catch (const std::out_of_range&) {
				cout << "\t\t\t\t\tNumber out of range!\n" << endl;
				continue;
			}
		}

	} while (true);


}


//main method
int main() {

	string username = authentication();
	showOptions(username);
}