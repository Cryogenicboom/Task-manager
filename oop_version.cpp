#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>
#include <string>
using namespace std;

// stores user ID and password it doesnt perfom any action, just stores things.
class User {
private:
    string user_id;
    string password;

public:
    User() {}
    User(string id, string pass) : user_id(id), password(pass) {}

    string getUserId() const { return user_id; }
    string getPassword() const { return password; }
};

// singup and login
class Authorization {
private:
    // file storing login details of user, we use this to verify when user logins
    const string filename = "User.txt"; 

public:
    
    bool login(User &loggedInUser) {
        string user_input_id, user_input_pass;
        cout << "User Id: ";
        getline(cin, user_input_id);
        cout << "Password: ";
        getline(cin, user_input_pass);

        ifstream file(filename);
        if (!file) {
            cerr << "Error: Could not open user database.\n";
            return false;
        }

        string file_id, file_pass;
        bool found = false;
        while (file >> file_id >> file_pass) {
            if (user_input_id == file_id && user_input_pass == file_pass) {
                found = true;
                loggedInUser = User(file_id, file_pass); // Store logged-in user
                break;
            }
        }
        file.close();

        if (found) {
            greetUser(user_input_id);
            return true;
        } else {
            cout << "Wrong UserID or Password. Try again.\n";
            return false;
        }
    }

    // Signup 
    void signup() {
        string new_id, new_pass;
        cout << "Choose a User Id: ";
        getline(cin, new_id);
        cout << "Choose a Password: ";
        getline(cin, new_pass);

        ofstream file(filename, ios::app);
        if (!file) {
            cerr << "Error: Could not open user database.\n";
            return;
        }
        file << new_id << " " << new_pass << "\n";
        file.close();
        cout << "Signup successful. You can now log in.\n";
    }

    // greet user based on current time
    void greetUser(const string &name) {
        time_t now = time(0);
        tm *ltm = localtime(&now);
        int hour = ltm->tm_hour;

        if (hour < 12)
            cout << "Good Morning, " << name << "!\n";
        else if (hour < 18)
            cout << "Good Afternoon, " << name << "!\n";
        else
            cout << "Good Evening, " << name << "!\n";
    }
};

// performs all the action of our taskmanager, add, view, edit
class TaskManager {
private:
    vector<string> tasks;
    string filename;      

public:

    // we create specific file for each user to store their task history
    TaskManager(const string &user_id) {
        filename = "tasks_" + user_id + ".txt";
        loadTasks(); 
    }

    // when viewing, we need to convert the txt file into array to print it.
    void loadTasks() {
        tasks.clear();
        ifstream file(filename);
        string task;
        while (getline(file, task)) {
            tasks.push_back(task);
        }
        file.close();
    }

    // and opposite to above function, we convert array to txt in file
    void saveTasks() {
        ofstream file(filename);
        for (const auto &task : tasks) {
            file << task << "\n";
        }
        file.close();
    }

    
    void addTask() {
        string task;
        cout << "Enter new task: ";
        getline(cin, task);
        tasks.push_back(task);
        saveTasks();
        cout << "Task added successfully.\n";
    }

    void viewTasks() {
        if (tasks.empty()) {
            cout << "No tasks available.\n";
            return;
        }
        cout << "\nYour Tasks:\n";
        for (size_t i = 0; i < tasks.size(); ++i) {
            cout << i + 1 << ". " << tasks[i] << "\n";
        }
    }


    void removeTask() {
        viewTasks();
        if (tasks.empty()) return;

        int index;
        cout << "Enter task number to remove: ";
        cin >> index;
        cin.ignore(); // must to clear buffer zone

        if (index < 1 || index > (int)tasks.size()) {
            cout << "Invalid task number.\n";
            return;
        }

        tasks.erase(tasks.begin() + (index - 1));
        saveTasks();
        cout << "Task removed successfully.\n";
    }
};

int main() {
    Authorization auth;
    User currentUser;

    int choice;
    cout << "1. Signup\n2. Login\nChoose: ";
    cin >> choice;
    cin.ignore(); 

    if (choice == 1) {
        auth.signup();
    } 
    else if (choice == 2) {
        if (auth.login(currentUser)) {
            TaskManager tm(currentUser.getUserId());

            while (true) {
                cout << "\n1. Add Task\n2. View Tasks\n3. Remove Task\n4. Logout\nChoose: ";
                int option;
                cin >> option;
                cin.ignore(); 

                if (option == 1) {
                    tm.addTask();
                } 
                else if (option == 2) {
                    tm.viewTasks();
                } 
                else if (option == 3) {
                    tm.removeTask();
                } 
                else if (option == 4) {
                    cout << "Logging out...\n";
                    break;
                } 
                else {
                    cout << "Invalid choice.\n";
                }
            }
        }
    } 
    else {
        cout << "Invalid choice.\n";
    }

    return 0;
}
