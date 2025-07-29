#include <iostream>
#include <string>
#include <vector>
#include <ctime>
using namespace std;

// forward declaration :) finally got to use them
void menu(vector<string>& list); 
void add(vector<string> &list);
void view(const vector<string> &list);
int edit(vector<string> &list);

void login(const vector<string> &list){
    string username, passkey;
    cout<<"Username: ";
    getline(cin, username);
    cout<<"Password (no spaces or special chars!): ";
    getline(cin, passkey);

    time_t now = time(0);                  // Get current time in seconds
    tm *ltm = localtime(&now);             // Convert to local time
    int time = ltm->tm_hour;               // Extract the hour (0–23)

    if (time >= 0 && time < 12){
        cout<<"Good morning! "<<username<<"\n";
    }
    else if (time >= 12 && time < 18){
        cout<<"Good afternoon! "<<username<<"\n";
    }
    if (time >= 18 && time <=23 ){
        cout<<"Good evening! "<<username<<"\n";
    }
    cout<<endl;
    view(list);
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
        cout<<"Pending tasks; \n";
        for(int i = 0; i < list.size(); i++){
            cout<<i+1<<". "<<list[i]<<endl;
        }
    }
    
}

void menu(vector<string> &list){
    int user_input;
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
    login(list);
    menu(list);
    return 0;
}