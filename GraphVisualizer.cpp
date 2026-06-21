#include "GraphVisualizer.h"
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;
GraphVisualizer::GraphVisualizer(Graph& network)
    : myNetwork(network), myWindow(VideoMode(Vector2u(800, 600)), "ConnectFlow - My Social Network") {
    srand(time(NULL));
    try {
        Font tempFont("C:\\Windows\\Fonts\\Arial.ttf");
        myFont = tempFont;
        fontLoaded = true;
        cout << "Font loaded successfully!" << endl;
    }
    catch (...) {
        fontLoaded = false;
        cout << "Font not loaded - showing circles only" << endl;
    }

    loadUsersAndFriends();
    arrangeInCircle();
}

string GraphVisualizer::getShortName(string fullName) {
    // If the name is short, display it entirely
    if (fullName.length() <= 5) {
        return fullName;
    }
    // If the name is longer, trim it to 4 characters and add an ellipsis
    return fullName.substr(0, 4) ;
}

void GraphVisualizer::loadUsersAndFriends() {
    allNodes.clear();
    allEdges.clear();

    unordered_map<int, User>& users = myNetwork.getAllUsers();
    unordered_map<int, vector<int>>& friends = myNetwork.getFriendList();

    // Create nodes
    for (auto& pair : users) {
        int id = pair.first;
        User* user = myNetwork.findUser(id);

        UserNode node;
        node.userId = id;

        // Circle
        node.circle.setRadius(25);
        node.circle.setFillColor(getRandomColor());
        node.circle.setOutlineThickness(2);
        node.circle.setOutlineColor(Color::White);

        // Create text using pointer 
        if (fontLoaded && user != NULL) {
            string shortName = getShortName(user->getName());
            node.nameText = make_unique<Text>(myFont, shortName, 18);
            node.nameText->setFillColor(Color::Black);
            node.nameText->setStyle(Text::Bold);
        }

        allNodes.push_back(std::move(node));
    }

    // Create edges
    for (auto& pair : friends) {
        int fromId = pair.first;
        for (int toId : pair.second) {
            if (fromId < toId) {
                allEdges.push_back(make_pair(fromId, toId));
            }
        }
    }
}

void GraphVisualizer::arrangeInCircle() {
    if (allNodes.empty()) return;

    float centerX = 400;
    float centerY = 300;
    float radius = 200;

    for (int i = 0; i < allNodes.size(); i++) {
        float angle = (2 * 3.14159f * i) / allNodes.size();
        allNodes[i].x = centerX + radius * cos(angle);
        allNodes[i].y = centerY + radius * sin(angle);
        allNodes[i].circle.setPosition(Vector2f(allNodes[i].x, allNodes[i].y));

        // Position of text in center of circle
        if (fontLoaded && allNodes[i].nameText != nullptr) {
            FloatRect bounds = allNodes[i].nameText->getLocalBounds();
            float textX = allNodes[i].x + 25 - (bounds.size.x / 2);
            float textY = allNodes[i].y + 25 - (bounds.size.y / 2);
            allNodes[i].nameText->setPosition(Vector2f(textX, textY));
        }
    }
}

void GraphVisualizer::drawLines() {
    for (auto& edge : allEdges) {
        float x1 = 0, y1 = 0, x2 = 0, y2 = 0;
        bool found1 = false, found2 = false;

        for (auto& node : allNodes) {
            if (node.userId == edge.first) {
                x1 = node.x + 25;
                y1 = node.y + 25;
                found1 = true;
            }
            if (node.userId == edge.second) {
                x2 = node.x + 25;
                y2 = node.y + 25;
                found2 = true;
            }
        }

        if (found1 && found2) {
            Vertex line[2];
            line[0] = Vertex(Vector2f(x1, y1), Color(150, 150, 150));
            line[1] = Vertex(Vector2f(x2, y2), Color(150, 150, 150));
            myWindow.draw(line, 2, PrimitiveType::Lines);
        }
    }
}

void GraphVisualizer::drawNames() {
    if (!fontLoaded) return;

    for (auto& node : allNodes) {
        if (node.nameText != nullptr) {
            myWindow.draw(*node.nameText);
        }
    }
}

Color GraphVisualizer::getRandomColor() {
    return Color(rand() % 200 + 55, rand() % 200 + 55, rand() % 200 + 55);
}

void GraphVisualizer::start() {
    myWindow.clear(Color::Black);
    drawLines();

    // Draw circles
    for (auto& node : allNodes) {
        myWindow.draw(node.circle);
    }

    // Draw names on top
    drawNames();
    myWindow.display();

    while (myWindow.isOpen()) {
        while (const optional<Event> event = myWindow.pollEvent()) {
            if (event->is<Event::Closed>()) {
                myWindow.close();  
            }
        }
    }
}
