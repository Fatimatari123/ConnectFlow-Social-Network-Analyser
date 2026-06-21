#pragma once
#ifndef GRAPH_H
#define GRAPH_H
#include "User.h"
#include "Queue.h"
#include <vector>
#include <list>
#include <queue>
#include <stack>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <functional>
#include <set>
#include <fstream>
#include <cmath>
using namespace std;

class Graph {
private:
    // User storage
    unordered_map<int, User> allUsers;

    // Friendship graph using (adjacency list)
    unordered_map<int, vector<int>> friendList;

    // Friend requests queue
    Queue<int> requestQueue;

    // Pending requests: for each user, list of people who requested them
    unordered_map<int, vector<int>> pendingRequests;

    int nextId;

    // Helper functions
    int countMutualFriends(int userA, int userB);
    double calculateInterestMatch(int userA, int userB);
    void dfsVisit(int startId, unordered_set<int>& visited, vector<int>& community);

public:
    Graph();

    // User functions
    int addUser(string name, string city);
    void addInterest(int userId, string interest);
    void showAllUsers();
    User* findUser(int userId);

    // Friend functions
    void addFriend(int userA, int userB);
    bool areTheyFriends(int userA, int userB);
    void showFriends(int userId);
    vector<int> getFriendList(int userId);

    // Friend request functions 
    void sendRequest(int fromId, int toId);
    void showPendingRequests(int userId);
    void acceptRequest(int fromId, int toId);
    void rejectRequest(int fromId, int toId);
    void showRequestQueue();

    // FEATURE 1: People You May Know 
    void suggestFriends(int userId);

    // FEATURE 2: Community Detection 
    void findCommunities();

    // Extra: Degrees of separation between two users
    int findDegreesOfSeparation(int userA, int userB);

    // Get all users 
    unordered_map<int, User>& getAllUsers();
    unordered_map<int, vector<int>>& getFriendList();
};

#endif
