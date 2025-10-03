#include "AStar.h"

#include <iostream>
#include <algorithm>

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

    //Initialization of Open and Closed lists
    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> openList;
    std::vector<std::vector<bool>> closedList(graph.size(), std::vector<bool>(grid[0].size(), false));

    //starting position
    openList.push(start);

    //Processing Loop
    while(!openList.empty()){

        //Lowest f value
        Node current = openList.top();
        openList.pop();

        if (current == goal) 
        {
            //Rebuild path
            std::vector<Node> path;
            while (!(current == start)) 
            {
                path.push_back(current);
                current = graph[current.x][current.y];
            }
            path.push_back(start);
            reverse(path.begin(), path.end());
            return path;
        }

        //Mark current point as closed
        closedList[current.x][current.y] = true;

        //check neighboring points
        for (int i = 0; i < 8; ++i) 
        {
            int newX = current.x + directionX[i];
            int newY = current.y + directionY[i];

            //check if in boundary
            if (newX >= 0 && newX < graph.size() && newY >= 0 && newY < grid[0].size()) 
            {
                //Check if walable and not closed
                if (graph[newX][newY] == 0 && !closedList[newX][newY]) 
                {
                    Node neighbor(newX, newY);
                    int newG = current.g + 1;

                    //Check if not open or has lower g
                    if (newG < neighbor.g || !closedList[newX][newY]) 
                    {
                        neighbor.g = newG;
                        neighbor.h = abs(newX - goal.x) + abs(newY - goal.y);
                        neighbor.f = neighbor.g + neighbor.h;
                        graph[newX][newY] = current; //Update parent point
                        openList.push(neighbor); //Add neighbor to open list
                    }
                }
            }
        }
    }

    //No Path Available
    return std::vector<Node>();
}