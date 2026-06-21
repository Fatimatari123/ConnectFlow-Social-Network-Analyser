#include "Graph.h"
#include "GraphVisualizer.h"
#include <iostream>
#include <limits>
using namespace std;
// Function to show menu
void showMenu() {
    cout << "========================================" << endl;
    cout << "\n\n";
    cout << "1. Add User" << endl;
    cout << "2. Add User interests" << endl;
    cout << "3. Show All Users" << endl;
    cout << "4. Show all Friends of a User" << endl;
    cout << "5. Send Friend Request " << endl;
    cout << "6. View Pending Requests" << endl;
    cout << "7. Accept Friend Request" << endl;
    cout << "8. Reject Friend Request" << endl;
    cout << "9. Suggestions" << endl;
	cout << "10. FIND COMMUNITIES " << endl;//based on mutual friendships
	cout << "11. Degrees of Separation " << endl;//between two users
	cout << "12. Established Network " << endl;//visualize the network using SFML
    cout << "13. Exit" << endl;
    cout << "========================================" << endl;
    cout << "Choice: ";
}
int main() {
    Graph network;
    int choice;
    cout << "\n========================================" << endl;
    cout << "     CONNECTFLOW - Social Network" << endl;
    cout << "========================================" << endl;
    while (true) {
        showMenu();
        cin >> choice;
        cin.ignore();
        switch (choice) {
        case 1: {
            string name, city;
            

            cout << "Name: ";
            getline(cin, name);

            cout << "City: ";
            cin >> city;
            cin.ignore();
            network.addUser(name, city);
            cout << "User added! \n" << endl;
            break;
        }
        case 2: {
            string interest;
            int id;
			cout << "User ID: ";
            cin >> id;
			cout << "Interest: ";
            cin >> interest;;
            network.addInterest(id, interest);
            
            break;
        }
        case 3:{
            network.showAllUsers();
            break;
        }
        case 4: {
            int id;
            cout << "User ID: ";
            cin >> id;
            network.showFriends(id);
            break;
        }

        case 5: {
            int from, to;
            cout << "Your ID: ";
            cin >> from;
            cout << "Friend's ID: ";
            cin >> to;
            network.sendRequest(from, to);
            break;
        }

        case 6: {
            int id;
            cout << "User ID: ";
            cin >> id;
            network.showPendingRequests(id);
            break;
        }

        case 7: {
            int from, to;
            cout << "Requester ID: ";
            cin >> from;
            cout << "Your ID (to accept): ";
            cin >> to;
            network.acceptRequest(from, to);
            break;
        }

        case 8: {
            int from, to;
            cout << "Requester ID: ";
            cin >> from;
            cout << "Your ID (to reject): ";
            cin >> to;
            network.rejectRequest(from, to);
            break;
        }

       

        case 9: {
            int id;
            cout << "Enter User ID: ";
            cin >> id;
            network.suggestFriends(id);//suggestions based on mutaul friends
            break;
        }

        case 10: {
            network.findCommunities();//communities based on mutual friendships
            break;
        }
        case 11: {
            int id1, id2;
            cout << "First User ID: ";
            cin >> id1;
            cout << "Second User ID: ";
            cin >> id2;
			int degrees = network.findDegreesOfSeparation(id1, id2);//degree of separation between two users
            if (degrees == -1) {
                cout << "No connection found!" << endl;
            }
            else {
                cout << "Degrees of separation: " << degrees << endl;
            }
            break;
        }

        case 12: {
            GraphVisualizer visualizer(network);
            visualizer.start();
            break;
        }

        case 13: {
            cout << "Goodbye!" << endl;
            return 0;
        }
        default:
            cout << "Invalid choice!" << endl;
        }
    }

    return 0;
}