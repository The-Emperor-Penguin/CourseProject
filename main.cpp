#include "data.hpp"

bool isInVector(vector<int> list, int node) {
    for (int number : list) {
        if (number == node) return true;
    }
    return false;
}

int findParentofPath(int node, vector<tuple<int,int>> paths) {
    for (auto [posparent, posnode]: paths) {
        if (posnode == node) {
            return posparent;
        }
    }
}

vector<int> smallestPath(int citA, int citB, const vector<vector<int>> graph) {
    queue<int> tovisit;
    vector<tuple<int, int>> paths;
    vector<int> shortPath;
    vector<int> visited;
    tovisit.push(citA);
    // This currently will go through everything and add the shortest path to everynode to paths
    bool foundPath = false;
    while(!tovisit.empty()) {
        int currentNode = tovisit.front();
        tovisit.pop();
        for (int i = 0; i < graph[currentNode].size(); i++) {
            int newNode = graph[currentNode][i];
            if(isInVector(visited, newNode)) continue;
            tovisit.push(newNode);
            paths.emplace_back(make_tuple(currentNode, newNode));
            if (newNode == citB) {
                foundPath = true;
                break;
            }
        }
        if (foundPath) break;
    }
    // If there is no path found then it will return an empty vector
    if (!foundPath) return vector<int>();
    //Start going through the path the algorithim took and find the path from B to A.
    shortPath.emplace(shortPath.begin(), citB);
    int parent = findParentofPath(citB, paths);

    while (parent != citA) {
        shortPath.emplace(shortPath.begin(), parent);
        parent = findParentofPath(parent, paths);
    }

    shortPath.emplace(shortPath.begin(), parent);
    return shortPath;
}

void smallestConnection(string cityA, string cityB, int maxCon, const vector<vector<int>> graph) {
    
    if ((!airportInMap(cityA)) && (!airportInMap(cityB))) {
        cout << "Airports Do not exist in given data!" << endl;
        cout << "Please type the name as given in data!" << endl;
        return;
    }
    int Aind = airportToInt(cityA);
    int Bind = airportToInt(cityB);
    vector<int> path = smallestPath(Aind, Bind, graph);
    if (path.empty()) {
        cout << "There is no path found between those cities. Please check given data!" << endl;
        return;
    }
    if (path.size() - 1 >= maxCon) {
        cout << "There are no flights that could get you there in that many connections." << endl;
        cout << "The minimum connections required is " << path.size()-1 << "." << endl;
        return;
    }
    for (int i = 0; i < path.size(); i++) {
        if (i != path.size()-1) cout << intToAirport(path[i]) << " -> ";
        else cout << intToAirport(path[i]);
    }
    cout << endl;
    cout << "Number of connections: " << path.size()-1 << endl;
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
        smallestConnection(cityA, cityB, numCon, graph);
    }

}