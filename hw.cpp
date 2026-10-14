#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

class Dovidnyk {
private:
    string _name;
    string _owner;
    string _phone;
    string _address;
    string _activity;

public:
    void Input() {
        cout << "Company name: ";
        getline(cin, _name);
        cout << "Owner: ";
        getline(cin, _owner);
        cout << "Phone: ";
        getline(cin, _phone);
        cout << "Address: ";
        getline(cin, _address);
        cout << "Activity: ";
        getline(cin, _activity);
    }

    void Print() {
        cout << "Company name: " << _name << endl;
        cout << "Owner: " << _owner << endl;
        cout << "Phone: " << _phone << endl;
        cout << "Address: " << _address << endl;
        cout << "Activity: " << _activity << endl;
        cout << endl;
    }

    bool SearchName(string name) {
        return _name == name;
    }

    bool SearchOwner(string owner) {
        return _owner == owner;
    }

    bool SearchPhone(string phone) {
        return _phone == phone;
    }

    bool SearchActivity(string activity) {
        return _activity == activity;
    }

    void Save(ofstream& file) {
        file << _name << endl;
        file << _owner << endl;
        file << _phone << endl;
        file << _address << endl;
        file << _activity << endl;
    }

    bool Load(ifstream& file) {
        if (!getline(file, _name)) {
            return false;
        }
        if (!getline(file, _owner)) {
            return false;
        }
        if (!getline(file, _phone)) {
            return false;
        }
        if (!getline(file, _address)) {
            return false;
        }
        if (!getline(file, _activity)) {
            return false;
        }

        return true;
    }
};

int main() {
    vector<Dovidnyk> firms;

    ifstream inFile("Dovidnyk.txt");

    if (inFile.is_open()) {
        Dovidnyk D;

        while (D.Load(inFile)) {
            firms.push_back(D);
        }

        inFile.close();
    }

    string choice;

    while (true) {
        cout << "1. Add company" << endl;
        cout << "2. Print all" << endl;
        cout << "3. Search by name" << endl;
        cout << "4. Search by owner" << endl;
        cout << "5. Search by phone" << endl;
        cout << "6. Search by activity" << endl;
        cout << "0. Exit" << endl;
        cout << "Choose: ";

        if (!getline(cin, choice)) {
            break;
        }

        if (choice == "0") {
            break;
        }
        else if (choice == "1") {
            Dovidnyk D;
            D.Input();

            if (!cin) {
                break;
            }

            ofstream outFile("Dovidnyk.txt", ios::app);

            if (outFile.is_open()) {
                D.Save(outFile);
                outFile.close();

                if (outFile) {
                    firms.push_back(D);
                    cout << "Company added" << endl;
                }
                else {
                    cout << "Error with writing the file" << endl;
                }
            }
            else {
                cout << "Error with opening the file" << endl;
            }
        }
        else if (choice == "2") {
            int count = firms.size();

            if (count == 0) {
                cout << "The directory is empty" << endl;
            }

            for (int i = 0; i < count; i++) {
                firms[i].Print();
            }
        }
        else if (choice == "3" || choice == "4" ||
                 choice == "5" || choice == "6") {
            string text;
            cout << "Enter search text: ";

            if (!getline(cin, text)) {
                break;
            }

            bool found = false;
            int count = firms.size();

            for (int i = 0; i < count; i++) {
                bool match = false;

                if (choice == "3") {
                    match = firms[i].SearchName(text);
                }
                else if (choice == "4") {
                    match = firms[i].SearchOwner(text);
                }
                else if (choice == "5") {
                    match = firms[i].SearchPhone(text);
                }
                else if (choice == "6") {
                    match = firms[i].SearchActivity(text);
                }

                if (match) {
                    firms[i].Print();
                    found = true;
                }
            }

            if (!found) {
                cout << "Nothing found" << endl;
            }
        }
        else {
            cout << "Wrong choice" << endl;
        }

        cout << endl;
    }

    return 0;
}