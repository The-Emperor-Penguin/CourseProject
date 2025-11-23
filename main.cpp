#include "data.hpp"

bool isInVector(vector<int> list, int node) {
    for (int number : list) {
        if (number == node) return true;
    }
    return false;
}

vector<int> smallestPath(int citA, int citB, const vector<vector<int>> graph) {
    queue<int> tovisit;
    vector<tuple<int, int>> paths;
    vector<int> shortPath;
    vector<int> visited;
    tovisit.push(citA);
    // This currently will go through everything and add the shortest path to everynode to paths
    // TODO: Stop and find the required path from paths
    while(!tovisit.empty()) {
        int currentNode = tovisit.front();
        tovisit.pop();
        for (int i = 0; i < graph[currentNode].size(); i++) {
            int newNode = graph[currentNode][i];
            if(isInVector(visited, newNode)) continue;
            tovisit.push(newNode);
            paths.emplace_back(make_tuple(currentNode, newNode));
        }
    }
}

void smallestConnection(string cityA, string cityB, int maxCon) {
    
    if ((!airportInMap(cityA)) && (!airportInMap(cityB))) {
        cout << "Airports Do not exist in given data!";
        return;
    }
    int Aind = airportToInt(cityA);
    int Bind = airportToInt(cityB);
    

}


int main() {
    vector<vector<int>> graph = create_graph();
    int option;
    cout << "1) from city A to city B with at most X connections." << endl;
    cout << "2) smallest connections from A to D through B and C." << endl;
    cout << "3) City A, City B, and City C meet with smallest connections for all three.";
    cin >> option;
    switch (option) {
        case 1:
        case 2:
        case 3:
        default:
        cout << "Name of city A: ";
        string cityA;
        cin >> cityA;
        cout << "Name of city B: ";
        string cityB;
        cin >> cityB;
        int numCon;
        cout << "Number of Connections: ";
        cin >> numCon;
        smallestConnection(cityA, cityB, numCon);
    }

}