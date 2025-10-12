#pragma once

#include <vector>
#include <queue>
#include <cmath>

//represents nodes of a graph
struct Node{
    int x, y; //coordinates
    double f, g, h; //A* algorithm values
    /*
    g is cost to reach a node from the start node
    h is the estimated cost to reach the goal node from the current node
    f is the summation of g and h
    */
    
    Node(int r, int c);

    bool operator>(const Node& other) const;
    bool operator==(const Node& other) const;
};

//Heuristic Implementation
double HeuCost(int sx, int sy, int gx, int gy);

//A* Algorithm Call
std::vector<Node> FindPath(const std::vector<std::vector<int>>& graph, const Node& start, const Node& goal);