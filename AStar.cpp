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

std::vector<Node> FindPath(const std::vector<std::vector<int>>& graph, const Node& start, const Node& goal){

    //possible movements
    const int directionX[] = {-1, 0, 1, 0, -1, -1, 1, 1};
    const int directionY[] = {0, 1, 0, -1, 1, -1, 1, -1};

    //Initialization of Open and Closed lists
    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> openList;
    std::vector<std::vector<bool>> closedList(graph.size(), std::vector<bool>(graph.size(), false));

    //starting position
    openList.push(start);
    
    std::vector<Node> path;

    //Processing Loop
    while(!openList.empty()){

        //Lowest f value
        while(closedList[openList.top().x][openList.top().y])
            openList.pop();

        Node current = openList.top();
        openList.pop();

        path.push_back(current);
        if (current == goal){
            //Rebuild path
            /*while (!(current == start)) 
            {
                path.push_back(current);
                openList.pop();
                current = openList.top();
            }
            //path.push_back(start);
            reverse(path.begin(), path.end());*/
            return path;
        }

        
        //Mark current point as closed
        closedList[current.x][current.y] = true;
        //check neighboring points
        for (int i = 0; i < 8; ++i){
            int newX = current.x + directionX[i];
            int newY = current.y + directionY[i];

            //check if in boundary
            if (newX >= 0 && newX < graph.size() && newY >= 0 && newY < graph.size()){
                //Check if walkable and not closed
                if (graph[newX][newY] == 0 && !closedList[newX][newY]){
                    Node neighbor(newX, newY);
                    double newG;
                    if((directionX[i] == 1 && directionY[i] == 0) || (directionX[i] == 0 && directionY[i] == 1) || (directionX[i] == 0 && directionY[i] == -1) || (directionX[i] == -1 && directionY[i] == 0))
                        newG = current.g + 1;
                    else
                        newG = current.g + 1.414;

                    //Check if not open or has lower g
                    if (!closedList[newX][newY] || newG < neighbor.g){
                        neighbor.g = newG;
                        neighbor.h = HeuCost(newX, goal.x, newY, goal.y);
                        neighbor.f = neighbor.g + neighbor.h; 
                        //newX = current.x; //Update to parent point x
                        //newY = current.y; //Update to parent point y
                        openList.push(neighbor); //Add neighbor to open list
                    }
                }
            }
        }
    }

    //No Path Available
    return std::vector<Node>();
}