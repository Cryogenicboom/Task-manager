#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <fstream> // file handling
using namespace std;

// forward declaration :) finally got to use them
void menu(vector<string>& list); 
void add(vector<string> &list);
void view(const vector<string> &list);
int edit(vector<string> &list);


string login() {
    int user_input;
    string username, passkey;

    cout << "Signup (1)\nLogin (2): ";
    cin >> user_input;
    cin.ignore();  // <-- Please Aryan remeber this 

    if (user_input == 1) {
        cout << "Choose a Username: ";
        getline(cin, username);
        cout << "Choose a Password (no spaces): ";
        getline(cin, passkey);

        ofstream file("users.txt", ios::app);
        if (file.is_open()) {
            file << username << " " << passkey << endl;
            file.close();
            cout << "Signup successful!\n";
        } else {
            cout << "Error\n";
        }
    } 
    else if (user_input == 2) {
        
        // using reading type to match the user info with user input.

        bool found = false;
        cout << "Username: ";
        getline(cin, username);
        cout << "Password: ";
        getline(cin, passkey);


        // ifstream = fstream(".txt", in)
        // same as ofstream = fstream(".txt", on)

        ifstream file("users.txt");
        if (file.is_open()) {
            string file_user, file_pass;
            while (file >> file_user >> file_pass) {
                if (file_user == username && file_pass == passkey) {
                    found = true;
                    break;
                }
            }
            file.close();

            if (!found) {
                cout << "Login failed. Username or password incorrect.\n";
                return login();  // later fix, causing trouble.
            } else {
                cout << "Login successful!\n";
            }
        } else {
            cout << "Eror.\n";
        }
    }

    
    time_t now = time(0);
    tm* ltm = localtime(&now);
    int hour = ltm->tm_hour;

    if (hour >= 0 && hour < 12) {
        cout << "Good morning, " << username << "!\n";
    } else if (hour >= 12 && hour < 18) {
        cout << "Good afternoon, " << username << "!\n";
    } else {
        cout << "Good evening, " << username << "!\n";
    }

    return username;
}

void add(vector<string> &list){
    cout<<"\nenter a task and hit 'enter' key to register it. (q to menu)\n";
    string user_input;

    cin.ignore(); // clear leftover newline from previous input

    while (true) {
        getline(cin, user_input);
        if (user_input == "q") 
            return; 
        list.push_back(user_input);
    }
    
    // i was doing mistake here; while loop will be always true since user_input is empty,and when i write q to quit, q is also added to tasks list.

    // while(user_input != "q"){
    //     int i= 0;
    //     getline(cin, user_input);
    //     i++;
    //     list.push_back(user_input);
    // }
}

int edit(vector<string> &list){
    for(int i = 0; i < list.size(); i++){
        cout<<i+1<<" "<<list[i]<<"\n";
    }
    cout<<"\nEnter tasks number with (e) to edit & (r) to remove\n[ex: 2 e, 5 r]: ";
    int task_num;
    char action;
    string newtask;
    cin>>task_num>>action;

    // always use to make buffer empty
    cin.ignore();

    if(action == 'e'){
        cout<<"Edit the task; "<<list.at(task_num-1);
        
        getline(cin,newtask);
        list.at(task_num-1) = newtask;
    }
    else if(action == 'r'){
        list.erase(list.begin()+(task_num-1));
    }
    return 0;
}

// using const here since i want to just view and not waste memory, and it avoid dynamic features making it not changeable in view mode.

void view(const vector<string> &list){
    // vector.empty() : c++ stl things
    if(list.empty()){
        cout<<"Hooray! No work today or Add to work on!"<<endl;
    }
    else{
        cout<<"\nPending tasks; \n";
        for(int i = 0; i < list.size(); i++){
            cout<<i+1<<". "<<list[i]<<endl;
        }
    }
    
}

void menu(vector<string> &list){
    int user_input;
    

    view(list);

    while(true){     
        cout<<"\n1 to Add Tasks\n2 to Edit and remove task\n3 to quit\n";
        cin>>user_input;
        if(user_input == 1){
            add(list);
        }
        else if(user_input == 2){
            edit(list);
        }
        else{
            cout<<"Exiting...";
            
            // pehle yeh break statement nahi chal raha that, why? kyoki break statement is only used in loops and switch cases.
            break;
        }
    }
}

int main(){
    vector<string> list;
    string username= login();

    // take username from login function to here and spread it whole others functions; (Good concept imo), saving files for each user.

    // if new login 
    ifstream taskfile(username + "_tasks.txt");
    string task;
    while (getline(taskfile, task)) {
        list.push_back(task);
    }
    taskfile.close();

    menu(list);

    // save after exit
    ofstream save(username + "_tasks.txt");
    for (string task : list) {
        save << task << "\n";
    }
    save.close();

    return 0;
}
