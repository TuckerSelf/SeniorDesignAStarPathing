#include "AStar.h"

#include <iostream>
#include <algorithm>
#include <cmath>

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

//implementation of Euclidean Heuristic
double HeuCost(int sx, int sy, int gx, int gy){
    double cost = sqrt(pow(((gx-sx)), 2) + pow((gy-sy), 2));
    return cost;
}

std::vector<Node> FindPath(int** graph, const Node& start, const Node& goal){

    //possible movements
    const int directionX[] = {-1, 0, 1, 0, -1, -1, 1, 1};
    const int directionY[] = {0, 1, 0, -1, 1, -1, 1, -1};

    //Initialization of Open and Closed lists
    std::vector<Node> openList;
    std::vector<Node> closedList;

    //starting position
    openList.push_back(start);
    
    std::vector<Node> path;

    //Processing Loop
    while(!openList.empty()){

        //Lowest f value
        Node current = openList[0];
        auto it = std::find(closedList.begin(), closedList.end(), current);
        for(Node& node : openList){
            it = std::find(closedList.begin(), closedList.end(), node);
            if(node.f < current.f && it != closedList.end())
                current = node;
        }
        openList.erase(it);

        current.h = HeuCost(current.x, current.y, goal.x, goal.y);

        path.push_back(current);
        if (current == goal){
            return path;
        }

        
        //Mark current point as closed
        closedList.push_back(current);
        //check neighboring points
        for (int i = 0; i < 8; ++i){
            int newX = current.x + directionX[i];
            int newY = current.y + directionY[i];

            //check if in boundary
            if (newX >= 0 && newX < sizeof(graph) && newY >= 0 && newY < sizeof(graph)){
                //Check if walkable and not closed
                if (graph[newX][newY] == 0){
                    Node neighbor(newX, newY);
                    auto it = std::find(closedList.begin(), closedList.end(), neighbor);
                    double newG;
                    if((directionX[i] == 1 && directionY[i] == 0) || (directionX[i] == 0 && directionY[i] == 1) || (directionX[i] == 0 && directionY[i] == -1) || (directionX[i] == -1 && directionY[i] == 0))
                        newG = current.g + 1;
                    else
                        newG = current.g + 1.414;

                    //Check if not open or has lower g
                    if (it != closedList.end() || newG < neighbor.g){
                        neighbor.g = newG;
                        neighbor.h = HeuCost(newX, newY, goal.x, goal.y);
                        neighbor.f = neighbor.g + neighbor.h; 
                        openList.push_back(neighbor); //Add neighbor to open list
                    }
                }
            }
        }
    }

    //No Path Available
    return std::vector<Node>();
}