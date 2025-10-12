#include <iostream>
#include <vector>
#include "AStar.h"

using namespace std;

void PrintPath(vector<Node>& path);




int main(){
    //Define Graph
    //Start and Goal should be valid Node values in graph
    //simple fully filled graph definition
    vector<vector<int>> graph(11, vector<int>(11,0));
    


    //start at top left, end at bottom right
    Node start(1, 1);
    Node goal(10, 10);

    cout << "Graph Size: " << graph.size() << endl;

    cout << "Start: " << start.x << ", " << start.y << " Goal: " << goal.x << ", " << goal.y << endl;
    cout << "Path: ";
    vector<Node> Path = FindPath(graph, start, goal);
    PrintPath(Path);

}

void PrintPath(vector<Node>& path){
    for (Node& node : path){
        cout << "(" << node.x << ", " << node.y << ") = " << node.f << ", ";
    }
    cout << endl;
}