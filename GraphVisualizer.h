#ifndef GRAPH_VISUALIZER_H
#define GRAPH_VISUALIZER_H
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "Graph.h"
#include <vector>
#include <string>
#include <memory>
using namespace sf;

class GraphVisualizer {
private:
    Graph& myNetwork;
    RenderWindow myWindow;

    struct UserNode {
        CircleShape circle;
        std::unique_ptr<Text> nameText;  // Using pointer instead of direct object
        int userId;
        float x;
        float y;

        UserNode() : nameText(nullptr) ,userId(0), x(0.0f), y(0.0f) {}  // Default constructor
    };

    std::vector<UserNode> allNodes;
    std::vector<std::pair<int, int>> allEdges;
    Font myFont;
    bool fontLoaded;
    void loadUsersAndFriends();
    void arrangeInCircle();
    void drawLines();
    void drawNames();
    Color getRandomColor();
    std::string getShortName(std::string fullName);

public:
    GraphVisualizer(Graph& network);
    void start();
};

#endif