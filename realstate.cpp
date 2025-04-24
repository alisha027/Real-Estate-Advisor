#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

class Property {
public:
    string id, name, type;
    double price;
    bool isAvailable;

    Property(string id, string name, string type, double price, bool isAvailable = true)
        : id(id), name(name), type(type), price(price), isAvailable(isAvailable) {}

    void display() const {
        cout << "---------------------------\n";
        cout << "ID       : " << id << "\n";
        cout << "Name     : " << name << "\n";
        cout << "Type     : " << type << "\n";
        cout << "Price    : $" << price << "\n";
        cout << "Available: " << (isAvailable ? "Yes" : "No") << "\n";
    }
};

bool userExists(const string& uname) {
    ifstream file("users.txt");
    string u, p;
    while (file >> u >> p) {
        if (u == uname) return true;
    }
    return false;
}

bool registerUser(string& username) {
    string uname, pwd;
    cout << "Enter new username: ";
    cin >> uname;
    if (userExists(uname)) {
        cout << "Username already exists.\n";
        return false;
    }

    cout << "Enter new password: ";
    cin >> pwd;

    ofstream file("users.txt", ios::app);
    file << uname << " " << pwd << "\n";
    username = uname;
    cout << "Registration successful!\n";
    return true;
}

bool loginUser(string& username) {
    string uname, pwd, fileUname, filePwd;
    cout << "Enter username: ";
    cin >> uname;
    cout << "Enter password: ";
    cin >> pwd;

    ifstream file("users.txt");
    while (file >> fileUname >> filePwd) {
        if (fileUname == uname && filePwd == pwd) {
            username = uname;
            return true;
        }
    }
    return false;
}

vector<Property> loadProperties() {
    vector<Property> props;
    ifstream file("properties.txt");
    string id, name, type;
    double price;
    int avail; // read as int, then convert to bool

    while (file >> id >> name >> type >> price >> avail) {
        bool isAvailable = (avail == 1);
        props.emplace_back(id, name, type, price, isAvailable);
    }

    return props;
}

void saveProperties(const vector<Property>& props) {
    ofstream file("properties.txt");
    for (const auto& p : props) {
        file << p.id << " " << p.name << " " << p.type << " " << p.price << " " << p.isAvailable << "\n";
    }
}

void showMainMenu() {
    cout << "\n1. View Properties\n2. Buy Property\n3. Rent Property\n4. Exit\nChoose an option: ";
}

void viewPropertiesMenu(const vector<Property>& properties) {
    int viewChoice;
    cout << "\n1. View Available Properties\n2. View All Properties\nChoose option: ";
    cin >> viewChoice;

    if (viewChoice == 1) {
        cout << "\nAvailable Properties:\n";
        for (const auto& prop : properties) {
            if (prop.isAvailable) {
                prop.display();
            }
        }
    } else if (viewChoice == 2) {
        cout << "\nAll Properties:\n";
        for (const auto& prop : properties) {
            prop.display();
        }
    } else {
        cout << "Invalid choice.\n";
    }
}

void buyProperty(vector<Property>& properties) {
    string id;
    cout << "Enter Property ID to Buy: ";
    cin >> id;
    bool found = false;

    for (auto& prop : properties) {
        if (prop.id == id) {
            found = true;
            if (prop.isAvailable) {
                prop.isAvailable = false;
                cout << "Property bought successfully!\n";
            } else {
                cout << "Property is already taken!\n";
            }
            break;
        }
    }

    if (!found) {
        cout << "Property ID not found!\n";
    }

    saveProperties(properties);
}

void rentProperty(vector<Property>& properties) {
    string id;
    cout << "Enter Property ID to Rent: ";
    cin >> id;
    bool found = false;

    for (auto& prop : properties) {
        if (prop.id == id) {
            found = true;
            if (prop.isAvailable) {
                prop.isAvailable = false;
                cout << "Property rented successfully!\n";
            } else {
                cout << "Property is already rented or bought!\n";
            }
            break;
        }
    }

    if (!found) {
        cout << "Property ID not found!\n";
    }

    saveProperties(properties);
}

int main() {
    string username;
    int authChoice;

    cout << "1. Login\n2. Register\nChoose option: ";
    cin >> authChoice;

    bool authenticated = false;
    if (authChoice == 1) {
        authenticated = loginUser(username);
        if (!authenticated) {
            cout << "Login failed. Exiting.\n";
            return 0;
        }
    } else if (authChoice == 2) {
        authenticated = registerUser(username);
        if (!authenticated) return 0;
    } else {
        cout << "Invalid option.\n";
        return 0;
    }

    vector<Property> properties = loadProperties();
    int choice;
    do {
        showMainMenu();
        cin >> choice;
        switch (choice) {
            case 1:
                viewPropertiesMenu(properties);
                break;
            case 2:
                buyProperty(properties);
                break;
            case 3:
                rentProperty(properties);
                break;
            case 4:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }
    } while (choice != 4);

    return 0;
}
