#include <iostream>
#include <vector>
#include "AStar.h"

using namespace std;

void PrintPath(const vector<Node>& path);




int main(){
    //Define Graph
    //Start and Goal should be valid Node values in graph
    vector<vector<int>> graph;
    //simple fully filled graph definition
    for(int i = 0; i < 11; i++){
        for(int j = 0; j < 11; j++){
            graph.push_back({i,j});
        }
    }

    //start at top left, end at bottom right
    Node start(0, 0);
    Node goal(10, 10);

    vector<Node> Path = FindPath(graph, start, goal);

    cout << "Path: ";
    PrintPath(Path);

}

void PrintPath(const vector<Node>& path){
    for (const Node& node : path) 
    {
        std::cout << "(" << node.x << ", " << node.y << ") ";
    }
    std::cout << std::endl;
}