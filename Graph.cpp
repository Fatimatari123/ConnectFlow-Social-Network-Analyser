#include "Graph.h"
#include <iostream>
using namespace std;
Graph::Graph() {
    nextId = 1;
}
// ========== USER FUNCTIONS ==========
int Graph::addUser(string name, string city) {
    int id = nextId;
    nextId++;
    User newUser(id, name, city);
    allUsers[id] = newUser;
    friendList[id] = vector<int>();
    return id;
}
void Graph::addInterest(int userId, string interest) {
    if (allUsers.find(userId) != allUsers.end()) {
        allUsers[userId].addInterest(interest);
    }
    else {
        cout << "User not found!" << endl;
    }
}

void Graph::showAllUsers() {
    cout << "\n===== ALL USERS =====" << endl;
    for (auto& pair : allUsers) {
        pair.second.display();
    }
}
User* Graph::findUser(int userId) {
    if (allUsers.find(userId) != allUsers.end()) {
        return &allUsers[userId];
    }
    return NULL;
}
// ========== FRIEND FUNCTIONS ==========
void Graph::addFriend(int userA, int userB) {
    if (userA == userB) {
        cout << "Cannot befriend yourself!" << endl;
        return;
    }
    if (areTheyFriends(userA, userB)) {
        cout << "Already friends!" << endl;
        return;
    }
    friendList[userA].push_back(userB);
    friendList[userB].push_back(userA);
    cout << "Friendship added between " << allUsers[userA].getName()
        << " and " << allUsers[userB].getName() << endl;
}
bool Graph::areTheyFriends(int userA, int userB) {
    for (int f : friendList[userA]) {
        if (f == userB) 
            return true;
    }
    return false;
}

void Graph::showFriends(int userId) {
    if (allUsers.find(userId) == allUsers.end()) {
        cout << "User not found!" << endl;
        return;
    }
    cout << "\nFriends of " << allUsers[userId].getName() << ":" << endl;
    if (friendList[userId].empty()) {
        cout << "  No friends yet." << endl;
        return;
    }
    for (int fId : friendList[userId]) {
        cout << "  - " << allUsers[fId].getName() << " (ID: " << fId << ")" << endl;
    }
}
vector<int> Graph::getFriendList(int userId) {
    return friendList[userId];
}
// ========== FRIEND REQUEST FUNCTIONS  ==========
void Graph::sendRequest(int fromId, int toId) {
    if (fromId == toId) {
        cout << "Cannot send request to yourself!" << endl;
        return;
    }
    if (areTheyFriends(fromId, toId)) {
        cout << "You are already friends!" << endl;
        return;
    }
    // Check if request already pending
    for (int r : pendingRequests[toId]) {
        if (r == fromId) {
            cout << "Request already sent!" << endl;
            return;
        }
    }
    // Add to queue and pending list
    requestQueue.enqueue(fromId);
    pendingRequests[toId].push_back(fromId);

    cout << "Friend request sent from " << allUsers[fromId].getName()
        << " to " << allUsers[toId].getName() << endl;
}

void Graph::showPendingRequests(int userId) {
    cout << "\nPending requests for " << allUsers[userId].getName() << ":" << endl;
    if (pendingRequests[userId].empty()) {
        cout << "  No pending requests." << endl;
        return;
    }
    for (int rId : pendingRequests[userId]) {
        cout << "  - From: " << allUsers[rId].getName() << " (ID: " << rId << ")" << endl;
    }
}
void Graph::acceptRequest(int fromId, int toId) {
    vector<int>& requests = pendingRequests[toId];
    auto it = find(requests.begin(), requests.end(), fromId);
    if (it == requests.end()) {
        cout << "No pending request from this user!" << endl;
        return;
    }
    requests.erase(it);
    addFriend(fromId, toId);
    cout << "Request ACCEPTED!" << endl;
}
void Graph::rejectRequest(int fromId, int toId) {
    vector<int>& requests = pendingRequests[toId];
    auto it = find(requests.begin(), requests.end(), fromId);
    if (it == requests.end()) {
        cout << "No pending request from this user!" << endl;
        return;
    }
    requests.erase(it);
    cout << "Request REJECTED!" << endl;
}

// ========== FEATURE 1: PEOPLE YOU MAY KNOW using BFS and interests ==========
int Graph::countMutualFriends(int userA, int userB) {
    int count = 0;
    for (int fA : friendList[userA]) {
        for (int fB : friendList[userB]) {
            if (fA == fB && fA != userA && fA != userB) {
                count++;
            }
        }
    }
    return count;
}
double Graph::calculateInterestMatch(int userA, int userB) {
    User* uA = findUser(userA);
    User* uB = findUser(userB);
    if (uA == NULL || uB == NULL) return 0;
    unordered_set<string> interestsA = uA->getInterests();
    unordered_set<string> interestsB = uB->getInterests();
    if (interestsA.empty() && interestsB.empty()) return 0.5;
    int common = 0;
    for (string interest : interestsA) {
        if (interestsB.find(interest) != interestsB.end()) {
            common++;
        }
    }
    int total = interestsA.size() + interestsB.size() - common;
    if (total == 0) return 0;
    return (double)common / total;
}
void Graph::suggestFriends(int userId) {
    // BFS to find friends-of-friends
    vector<pair<int, int>> suggestions; // pair<userId, score>
    unordered_set<int> visited;
    unordered_set<int> directFriends;
    // Record direct friends but do not mark them visited here;
    // they must be visited by BFS so we can explore their neighbors.
    for (int f : friendList[userId]) {
        directFriends.insert(f);
    }
    visited.insert(userId);
    // BFS queue
    queue<pair<int, int>> bfsQueue; // pair<userId, distance>
    bfsQueue.push({ userId, 0 });
    while (!bfsQueue.empty()) {
        int current = bfsQueue.front().first;
        int dist = bfsQueue.front().second;
        bfsQueue.pop();
        if (dist >= 2) 
            continue;
        for (int neighbor : friendList[current]) {
            if (visited.find(neighbor) == visited.end()) {
                visited.insert(neighbor);
                bfsQueue.push({ neighbor, dist + 1 });
                if (dist + 1 == 2 && directFriends.find(neighbor) == directFriends.end()) {
                    int mutual = countMutualFriends(userId, neighbor);
                    double interestMatch = calculateInterestMatch(userId, neighbor);
                    int score = mutual + (int)(interestMatch * 10);
                    suggestions.push_back({ neighbor, score });
                }
            }
        }
    }
    // Sort by score (higher is better)
    sort(suggestions.begin(), suggestions.end(),
        [](pair<int, int> a, pair<int, int> b) {
            return a.second > b.second;
        });
    // Display suggestions
    cout << "\n===== PEOPLE YOU MAY KNOW =====" << endl;
    cout << "For user: " << allUsers[userId].getName() << endl;

    if (suggestions.empty()) {
        cout << "No suggestions available." << endl;
        return;
    }

    for (int i = 0; i < suggestions.size() && i < 5; i++) {
        User* u = findUser(suggestions[i].first);
        if (u != NULL) {
            cout << i + 1 << ". " << u->getName() << " (Score: " << suggestions[i].second;
            cout << " | Mutual friends: " << countMutualFriends(userId, suggestions[i].first);
            cout << ")" << endl;
        }
    }
    cout << endl;
}
// ========== FEATURE 2: COMMUNITY DETECTION using (DFS) ==========
void Graph::dfsVisit(int startId, unordered_set<int>& visited, vector<int>& community) {
    visited.insert(startId);
    community.push_back(startId);
    for (int neighbor : friendList[startId]) {
        if (visited.find(neighbor) == visited.end()) {
            dfsVisit(neighbor, visited, community);
        }
    }
}
void Graph::findCommunities() {
    vector<vector<int>> allCommunities;
    unordered_set<int> visited;
    // Find connected components using DFS
    for (auto& pair : allUsers) {
        int userId = pair.first;
        if (visited.find(userId) == visited.end()) {
            vector<int> community;
            dfsVisit(userId, visited, community);
            if (community.size() > 1) { // Only show communities with 2+ people
                allCommunities.push_back(community);
            }
        }
    }
    // Display communities
    cout << "\n===== COMMUNITIES DETECTED =====" << endl;
    cout << "Found " << allCommunities.size() << " communities:" << endl;

    for (int i = 0; i < allCommunities.size(); i++) {
        cout << "\nCommunity " << i + 1 << " (Size: " << allCommunities[i].size() << "):" << endl;
        for (int userId : allCommunities[i]) {
            User* u = findUser(userId);
            if (u != NULL) {
                cout << "  - " << u->getName() << " (ID: " << userId << ")" << endl;
            }
        }
    }

    if (allCommunities.empty()) {
        cout << "No communities found. Add more friendships!" << endl;
    }
}
// ==========  Feature 3: DEGREES OF SEPARATION using (BFS) ==========
int Graph::findDegreesOfSeparation(int userA, int userB) {
    if (userA == userB) 
        return 0;

    unordered_map<int, int> distance;
    unordered_map<int, bool> visited;
    queue<int> bfsQueue;

    bfsQueue.push(userA);
    visited[userA] = true;
    distance[userA] = 0;

    while (!bfsQueue.empty()) {
        int current = bfsQueue.front();
        bfsQueue.pop();

        for (int neighbor : friendList[current]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                distance[neighbor] = distance[current] + 1;
                bfsQueue.push(neighbor);

                if (neighbor == userB) {
                    return distance[neighbor];
                }
            }
        }
    }

    return -1; // No path found
}
// ========== GETTERS FOR GRAPHICS ==========
unordered_map<int, User>& Graph::getAllUsers() {
    return allUsers;
}
unordered_map<int, vector<int>>& Graph::getFriendList() {
    return friendList;
}