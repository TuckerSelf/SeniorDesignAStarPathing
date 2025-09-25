#include <iostream>
#include <vector>
#include <cmath>
#include <queue>
#include <algorithm>

//represents nodes of a graph
struct Node{
    int x, y; //coordinates
    int f, g, h; //A* algorithm values
    /*
    g is cost to reach a node from the start node
    h is the estimated cost to reach the goal node from the current node
    f is the summation of g and h
    */
    
    Node(int r, int c);

    bool operator>(const Node& other) const;
    bool operator==(const Node& other) const;
};

Node::Node(int _x, int _y): 
x(_x),
y(_y),
f(0),
g(0),
h(0){}

bool Node::operator>(const Node& other) const{
    return f > other.f;
}

bool Node::operator==(const Node& other) const{
    return x == other.x && y == other.y;
}

std::vector<Node> FindPath(const std::vector<std::vector<int>>& graph, const Node& start, const Node& goal){

    //possible movements
    const int directionX[] = {-1, 0, 1, 0, -1, -1, 1, 1};
    const int directionY[] = {0, 1, 0, -1, 1, -1, 1, -1};

    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> openList;
    std::vector<std::vector<bool>> closedList(graph.size(), std::vector<bool>(grid[0].size(), false));

    //starting position
    openList.push(start);

    while(!openList.empty()){

    }
}