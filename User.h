#pragma once
#ifndef USER_H
#define USER_H
#include <string>
#include <unordered_set>
#include <iostream>
using namespace std;
class User {
private:
    int id;
    string name;
    string city;
    unordered_set<string> interests;

public:
    User();
    User(int id, string name, string city);

    int getId();
    string getName();
    string getCity();
    unordered_set<string> getInterests();

    void addInterest(string interest);
    void display();

    // For interest matching
    bool hasInterest(string interest);
};

#endif
