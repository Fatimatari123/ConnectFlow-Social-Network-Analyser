#include "User.h"

User::User() {
    id = -1;
    name = "";
    city = "";
}

User::User(int i, string n, string c) {
    id = i;
    name = n;
    city = c;
}

int User::getId() {
    return id;
}

string User::getName() {
    return name;
}

string User::getCity() {
    return city;
}

unordered_set<string> User::getInterests() {
    return interests;
}

void User::addInterest(string interest) {
    interests.insert(interest);
    cout << "Added interest: " << interest << endl;
}

void User::display() {
    cout << "ID: " << id << " | Name: " << name << " | City: " << city << " | Interests: ";
    for (string i : interests) {
        cout << i << " ";
    }
    cout << endl;
}

bool User::hasInterest(string interest) {
    return interests.find(interest) != interests.end();
}