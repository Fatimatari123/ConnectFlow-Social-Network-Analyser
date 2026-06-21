# ConnectFlow — Social Network Simulator
A graph-based Social Network Simulator built in **C++** using **Visual Studio**, that models users and friendships as a graph. Features BFS-powered friend suggestions, DFS community detection, degrees of separation, and a queue-based friend request system. All visualised in real-time using **SFML**.

## Features

- **Add Users & Interests** — Create user profiles with name, city, and hobbies
- **Friend Management** — Add friends and view friend lists
- **Friend Request System** — Send, accept, and reject requests using a custom FIFO Queue
- **People You May Know** — BFS traversal at depth-2 with Jaccard interest-based scoring
- **Community Detection** — DFS-based connected component detection
- **Degrees of Separation** — Shortest social path between any two users via BFS
- **Network Visualizer** — Real-time graphical rendering of the network using SFML

## Tech Stack
| Tool | Purpose |
|------|---------|
| C++ | Core language |
| Visual Studio | IDE |
| SFML | Real-time graphics & visualization |
| STL (unordered_map, queue, set) | Data structure support |

## Data Structures & Algorithms Used

- **Adjacency List** — Graph representation of friendships
- **BFS (Breadth-First Search)** — Friend suggestions & degrees of separation
- **DFS (Depth-First Search)** — Community detection
- **Custom Queue** — FIFO friend request processing
- **Hash Maps & Unordered Sets** — O(1) user and interest lookups
- **Jaccard Similarity** — Interest-based friend scoring

## Project Structure

-**main.cpp**  - Entry point & menu

-**Graph.h / Graph.cpp**  - Core graph logic (BFS, DFS, requests)

-**User.h / User.cpp**       - User profile model

-**GraphVisualizer.h / GraphVisualizer.cpp**     - SFML visualisation

-**Queue.h**               - Custom queue implementation

-**Header.h**              - Shared headers


### Prerequisites
- Visual Studio 2022
- SFML library linked to the project

## Sample Network 

| ID | Name | City |
|----|------|------|
| 0 | Alice | New York |
| 1 | Bob | LA |
| 2 | Charlie | Chicago |
| 3 | Diana | NY |
| 4 | Eve | SF |
| 5 | Frank | Boston |

## Network Visualisation:
<img width="798" height="651" alt="Screenshot 2026-04-28 204423" src="https://github.com/user-attachments/assets/7de403e4-2d7d-4047-b843-cd745a750edc" />



