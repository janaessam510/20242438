
#include <iostream>
#include <string>
#include <vector>
#include <limits>
using namespace std;


class Employee {
private:
    int    id;
    string name;
    string email;

public:
    
    Employee(int id, string name, string email)
        : id(id), name(name), email(email) {}

    
    void setName (const string& n) { name  = n; }
    void setEmail(const string& e) { email = e; }
    void setId   (int i)           { id    = i; }


    string getName () const { return name;  }
    string getEmail() const { return email; }
    int    getId   () const { return id;    }
};


class EmployeeView {
public:
    void printEmployeeDetails(const Employee& e) const {
        cout << "\n┌─────────────────────────────┐\n";
        cout << "│      Employee Details       │\n";
        cout << "├─────────────────────────────┤\n";
        cout << "│  ID    : " << e.getId()    << "\n";
        cout << "│  Name  : " << e.getName()  << "\n";
        cout << "│  Email : " << e.getEmail() << "\n";
        cout << "└─────────────────────────────┘\n";
    }

    void printAllEmployees(const vector<Employee>& employees) const {
        if (employees.empty()) {
            cout << "\n  (No employees on record)\n";
            return;
        }
        cout << "\n╔══════╦══════════════════════╦════════════════════════════╗\n";
        cout << "║  ID  ║  Name                ║  Email                     ║\n";
        cout << "╠══════╬══════════════════════╬════════════════════════════╣\n";
        for (const auto& e : employees) {
            printf("║ %4d ║ %-20s ║ %-26s ║\n",
                   e.getId(),
                   e.getName().c_str(),
                   e.getEmail().c_str());
        }
        cout << "╚══════╩══════════════════════╩════════════════════════════╝\n";
    }

    void showMessage(const string& msg) const {
        cout << "\n  >> " << msg << "\n";
    }
};


class EmployeeController {
private:
    vector<Employee> employees;
    EmployeeView&    view;
    int              nextId;

public:
    EmployeeController(EmployeeView& v) : view(v), nextId(1) {}

    
    void addEmployee(const string& name, const string& email) {
        employees.emplace_back(nextId++, name, email);
        view.showMessage("Employee added successfully.");
    }

    
    bool editEmployee(int id, const string& newName, const string& newEmail) {
        for (auto& e : employees) {
            if (e.getId() == id) {
                if (!newName.empty())  e.setName(newName);
                if (!newEmail.empty()) e.setEmail(newEmail);
                view.showMessage("Employee updated successfully.");
                return true;
            }
        }
        view.showMessage("Employee with ID " + to_string(id) + " not found.");
        return false;
    }

    bool displayEmployee(int id) const {
        for (const auto& e : employees) {
            if (e.getId() == id) {
                view.printEmployeeDetails(e);
                return true;
            }
        }
        view.showMessage("Employee with ID " + to_string(id) + " not found.");
        return false;
    }

    void displayAllEmployees() const {
        view.printAllEmployees(employees);
    }

    bool deleteEmployee(int id) {
        for (auto it = employees.begin(); it != employees.end(); ++it) {
            if (it->getId() == id) {
                employees.erase(it);
                view.showMessage("Employee deleted.");
                return true;
            }
        }
        view.showMessage("Employee with ID " + to_string(id) + " not found.");
        return false;
    }

    int getCount() const { return (int)employees.size(); }
};


void clearInput() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

string readLine(const string& prompt) {
    string s;
    cout << prompt;
    getline(cin, s);
    return s;
}

int readInt(const string& prompt) {
    int n;
    cout << prompt;
    while (!(cin >> n)) {
        cin.clear();
        clearInput();
        cout << "  Invalid. Enter a number: ";
    }
    clearInput();
    return n;
}

int main() {
    EmployeeView       view;
    EmployeeController controller(view);

    int choice = 0;
    while (true) {
        cout << "\n╔══════════════════════════════╗\n";
        cout << "║   Employee MVC System        ║\n";
        cout << "╠══════════════════════════════╣\n";
        cout << "║  1. Add Employee             ║\n";
        cout << "║  2. Edit Employee            ║\n";
        cout << "║  3. Display Employee by ID   ║\n";
        cout << "║  4. Display All Employees    ║\n";
        cout << "║  5. Delete Employee          ║\n";
        cout << "║  0. Exit                     ║\n";
        cout << "╚══════════════════════════════╝\n";
        choice = readInt("  Choose an option: ");

        if (choice == 0) {
            cout << "\nGoodbye!\n";
            break;

        } else if (choice == 1) {
            string name  = readLine("  Name  : ");
            string email = readLine("  Email : ");
            controller.addEmployee(name, email);

        } else if (choice == 2) {
            int id = readInt("  Employee ID to edit: ");
            cout << "  Leave blank to keep current value.\n";
            string name  = readLine("  New Name  : ");
            string email = readLine("  New Email : ");
            controller.editEmployee(id, name, email);

        } else if (choice == 3) {
            int id = readInt("  Employee ID: ");
            controller.displayEmployee(id);

        } else if (choice == 4) {
            controller.displayAllEmployees();

        } else if (choice == 5) {
            int id = readInt("  Employee ID to delete: ");
            controller.deleteEmployee(id);

        } else {
            cout << "  Invalid option. Try again.\n";
        }
    }

    return 0;
}
