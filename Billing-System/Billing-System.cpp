#include <iostream>
using namespace std;

void main(){

    int selectedItemNo;
    int selectedQty;

    cout << "\t\t\t******** Welcome to Meal Hut *********\n" << endl;

    //Table headers
    cout << " _____________________________________________________________________________________" << endl;
    cout << "| Item No\t\t|\t\t";
    cout << "Menu Item\t\t|\t\t";
    cout << "Price |" << endl;
    cout << " -------------------------------------------------------------------------------------" << endl;

    //items
    cout << "| 111\t\t\t|\t\t";
    cout << "Plain Egg\t\t|\t\t";
    cout << "$1.45 |" << endl;

    cout << "| 112\t\t\t|\t\t";
    cout << "Bacon and Egg\t\t|\t\t";
    cout << "$2.45 |" << endl;

    cout << "| 113\t\t\t|\t\t";
    cout << "Muffin\t\t\t|\t\t";
    cout << "$0.99 |" << endl;

    cout << "|_____________________________________________________________________________________|" << endl;

    cout << "Enter Item No You want : ";
    cin >> selectedItemNo;

    cout << "Enter quantity you want : ";
    cin >> selectedQty;


}
