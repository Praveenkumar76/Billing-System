#include <iostream>
#include <fstream>
#include <sstream>
#include <windows.h>
using namespace std;

class Bill {
private:
    string Item;
    int Rate, Quantity;

public:
    Bill() : Item(""), Rate(0), Quantity(0) {}

    void setItem(string item) {
        Item = item;
    }

    void setRate(int rate) {
        Rate = rate;
    }

    void setQuant(int quant) {
        Quantity = quant;
    }

    string getItem() {
        return Item;
    }

    int getRate() {
        return Rate;
    }

    int getQuant() {
        return Quantity;
    }
};

void addItem(Bill& b) {  
    bool close = false;
    while (!close) {
        int choice;
        cout << "\t1. Add." << endl;
        cout << "\t2. Close." << endl;
        cout << "\tEnter Choice: ";
        cin >> choice;

        if (choice == 1) {
            system("cls");
            string item;
            int rate, quant;

            cout << "\tEnter Item Name: ";
            cin >> item;
            b.setItem(item);

            cout << "\tEnter Rate Of Item: ";
            cin >> rate;
            b.setRate(rate);

            cout << "\tEnter Quantity Of Item: ";
            cin >> quant;
            b.setQuant(quant);

            ofstream out("Bill.txt", ios::app);
            if (!out) {
                cout << "\tError: File Can't Open!" << endl;
            } else {
                out << b.getItem() << " : " << b.getRate() << " : " << b.getQuant() << endl;
            }
            out.close();
            cout << "\tItem Added Successfully" << endl;
            Sleep(2000);
        } else if (choice == 2) {
            system("cls");
            close = true;
            cout << "\tBack To Main Menu!" << endl;
            Sleep(2000);
        }
    }
}

void printBill() {
    system("cls");
    int totalBill = 0;  
    bool close = false;

    while (!close) {
        int choice;
        cout << "\t1. Add Bill." << endl;
        cout << "\t2. Close Session." << endl;
        cout << "\tEnter Choice: ";
        cin >> choice;

        if (choice == 1) {
            string item;
            int quant;
            cout << "\tEnter Item: ";
            cin >> item;
            cout << "\tEnter Quantity: ";
            cin >> quant;

            ifstream in("Bill.txt");
            ofstream out("Bill_Temp.txt");
            if (!in || !out) {
                cout << "\tError: File Can't Open!" << endl;
                continue;
            }

            string line;
            bool found = false;

            while (getline(in, line)) {
                stringstream ss(line);
                string itemName;
                int itemRate, itemQuant;
                char delimiter;

                ss >> itemName >> delimiter >> itemRate >> delimiter >> itemQuant;

                if (item == itemName) {
                    found = true;
                    if (quant <= itemQuant) {
                        int amount = itemRate * quant;
                        cout << "\tItem | Rate | Quantity | Amount" << endl;
                        cout << "\t" << itemName << " | " << itemRate << " | " << quant << " | " << amount << endl;

                        int newQuant = itemQuant - quant;
                        totalBill += amount;

                        out << itemName << " : " << itemRate << " : " << newQuant << endl;
                    } else {
                        cout << "\tInsufficient Stock for " << item << "!" << endl;
                    }
                } else {
                    out << line << endl;
                }
            }

            if (!found) {
                cout << "\tItem Not Found!" << endl;
            }

            in.close();
            out.close();
            remove("Bill.txt");
            rename("Bill_Temp.txt", "Bill.txt");
        } else if (choice == 2) {
            close = true;
            cout << "\tCalculating Total Bill..." << endl;
            Sleep(2000);
        }
    }

    system("cls");
    cout << "\n\tTotal Bill ----------------- : " << totalBill << endl;
    cout << "\tThanks for Shopping!" << endl;
    Sleep(3000);
}

int main() {
    Bill b;

    bool exit = false;
    while (!exit) {
        system("cls");
        int val;

        cout << "\tWelcome To Super Market Billing System" << endl;
        cout << "\t**************************************" << endl;
        cout << "\t\t1. Add Item." << endl;
        cout << "\t\t2. Print Bill." << endl;
        cout << "\t\t3. Exit." << endl;
        cout << "\t\tEnter Choice: ";
        cin >> val;

        if (val == 1) {
            system("cls");
            addItem(b);
        } else if (val == 2) {
            printBill();
        } else if (val == 3) {
            system("cls");
            exit = true;
            cout << "\tGood Luck!" << endl;
            Sleep(2000);
        }
    }

    return 0;
}