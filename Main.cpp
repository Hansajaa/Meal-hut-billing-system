#include <iostream>
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
	string itemsName[8] = { "Plain Egg     ", "Bacon and Egg  ", "Muffin         ", "French Toast   ", "Fruit Basket   ", "Cereal         ", "Coffee         ", "Tea            " }; //items names
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
	cout << " _________________________________________________________________________________________" << endl;
	cout << "| Item ID\t\t|\t\t";
	cout << "Menu Item\t\t|\t\t";
	cout << "Price \t  |" << endl;
	cout << " -----------------------------------------------------------------------------------------" << endl;

	//items
	for (int i = 0; i < 8; i++) {
		cout << "| " << menuList[i].itemNo << "\t\t\t |\t\t";
		cout << menuList[i].itemName << "\t\t | \t\t";
		cout << "$" << menuList[i].itemPrice << "\t  |" << endl;
	}

	cout << "|_________________________________________________________________________________________|\n" << endl;
}

void addItemsToOrder(Order orderList[], Item menuList[], int &lastIndexofOrder) {

	int itemNo;
	int quantity;


	//show currently added products and their quantity
	cout << "\n**** Items in cart ****" << endl;
	cout << " --------------------------------" << endl;
	cout << "| item\t\t | quantity\t |" << endl;
	cout << " --------------------------------" << endl;

	//check if cart empty
	if (lastIndexofOrder == 0) {
		cout << "| Cart is currently empty \t |" << endl;
	}

	//if products exists in cart show them for user to get understand of their cart status
	for (int i = 0; i < lastIndexofOrder; i++){
		cout << "| " << orderList[i].itemName << " | " << orderList[i].quantity << " \t\t |" << endl;
	}
		
	cout << " --------------------------------" << endl;

	cout << "\nEnter the item ID (eg - 111 ) : ";
	cin >> itemNo;

	if (!(itemNo >= 111 && itemNo <= 118)) {
		cout << "\t\t\t\t\tInvalid item ID. Please enter a valid item ID." << endl;
	}else {
		for (int i = 0; i < lastIndexofOrder; i++){
			if (itemNo == orderList[i].itemNo) {
				cout << "\t\t\t\t\tItem already added to the order. Please enter a different item ID." << endl;
				return;
			}
		}

		do{
			cout << "Enter quantity (1 - 50) : ";
			cin >> quantity;

			if (!(quantity >= 1 && quantity <= 50)) {
				cout << "\t\t\t\t\tInvalid quantity. Please enter a valid quantity." << endl;
			}

		} while (!(quantity >= 1 && quantity <= 50));


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

	do{
		displayMenu(menuList);
		addItemsToOrder(orderList, menuList, lastIndexofOrder);


		do{
			cout << "Do you want to add more items (y/n) : ";
			cin >> isContinue;

			if (isContinue == 'n' || isContinue == 'N') {
				cout << "\t\t\t\t\tOrder Placed Successfully !" << endl;
				return;
			}

			if (isContinue != 'y' && isContinue != 'Y') {
				cout << "\t\t\t\t\tIncorrect answer !" << endl;
			}

		} while (isContinue != 'y' && isContinue != 'Y');


	} while (isContinue == 'y' || isContinue == 'Y');


}

//print the bill
void printBill(Order orderList[], int &lastIndexOfOrder) {

	double tax;
	double tot = 0.0;

	cout << "\n\n\t\t\t******************** Bill ********************\n" << endl; //title

	//Table headers
	cout << " ___________________________________________________________________________________________________________" << endl;
	cout << "| Item ID\t|\t";
	cout << "Menu Item\t|\t";
	cout << "Price per Item\t|\t";
	cout << "Quantity\t|\t";
	cout << "Total Price |" << endl;
	cout << " -----------------------------------------------------------------------------------------------------------" << endl;

	for (int i = 0; i < lastIndexOfOrder; i++) {
		tot += orderList[i].total; // calculate total of all items

		cout << "| " << orderList[i].itemNo << "\t        |\t";
		cout << orderList[i].itemName << "\t| \t";
		cout << "$" << orderList[i].itemPrice<< "\t\t|\t";
		cout  << orderList[i].quantity<< "\t\t|\t";
		cout << "$" << orderList[i].total<< "\t    |" << endl;
	}

	tax = tot * 0.05; //calculate tax

	cout << " -----------------------------------------------------------------------------------------------------------" << endl;
	cout << "\t\t\t\t\t\t\t\t| Tax \t\t\t|\t$" << tax << "     |" << endl;
	
	cout << "\t\t\t\t\t\t\t\t| ------------------------------------------|" << endl;

	cout << "\t\t\t\t\t\t\t\t| Amount Due \t\t|\t$" << tot+tax << "     |" << endl;
	
	cout << "\t\t\t\t\t\t\t\t| __________________________________________|" << endl;

}

//get orders
void getOrders(Item menuList[]) {
	
	getData(menuList); // load data into menuList array

	char isContinue;

	do {
		
		Order orderList[8]; // array of orders
		int lastIndexofOrder = 0; // last index of orderList array

		cout << "\n\n\t\t\t******************** New Order ********************\n" << endl;

		placeOrder(orderList, menuList, lastIndexofOrder); // get order
		printBill(orderList, lastIndexofOrder); //print the bill

		do{
			cout << "\n\nDo you want to place new order (y/n) : ";
			cin >> isContinue;

			if (isContinue == 'n' || isContinue == 'N') {
				cout << "\t\t\t\t\tThank You !" << endl;
			}

			if (isContinue != 'y' && isContinue != 'Y' && isContinue != 'n' && isContinue != 'N') {
				cout << "\t\t\t\t\tIncorrect answer Please enter (y/n) !" << endl;
			}

		} while (isContinue != 'y' && isContinue != 'Y' && isContinue != 'n' && isContinue != 'N');
	} while (isContinue == 'y' || isContinue == 'Y');
}

int main() {
	cout << "\t\t\t******** Welcome to Meal Hut *********\n" << endl; //title

	Item menuList[8]; // array of items

	getOrders(menuList);
	
}