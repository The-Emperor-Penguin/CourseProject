#include "data.hpp"

//TODO: Move some functions from this file into another to help clean up the finished code!

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
    return -1;
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
    if (parent == -1) return vector<int>();

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
        cout << "There is no path found between those cities. If you think this is an error then please check given data!" << endl;
        return;
    }
    if (path.size() - 2 >= maxCon) {
        cout << "There are no flights that could get you there in that many connections." << endl;
        cout << "The minimum connections required is " << path.size()-1 << "." << endl;
        return;
    }
    for (int i = 0; i < path.size(); i++) {
        if (i != path.size()-1) cout << intToAirport(path[i]) << " -> ";
        else cout << intToAirport(path[i]);
    }
    cout << endl;
    cout << "Number of connections: " << path.size()-2 << endl;
}

void passThroughFourCities(vector<int> intcities, const vector<vector<int>> graph) {
    // intcities must have A at 0 B at 1, C at 2, and D at 3
            vector<int> pathAB = smallestPath(intcities.at(0), intcities.at(1), graph);
            vector<int> pathAC = smallestPath(intcities.at(0), intcities.at(2), graph);
            vector<int> pathBC = smallestPath(intcities.at(1), intcities.at(2), graph);
            vector<int> pathCB = smallestPath(intcities.at(2), intcities.at(1), graph);
            vector<int> pathCD = smallestPath(intcities.at(2), intcities.at(3), graph);
            vector<int> pathBD = smallestPath(intcities.at(1), intcities.at(3), graph);

            int pathsizeABCD = pathAB.size() + pathBC.size() + pathCD.size() - 2;
            if (pathAB.empty() || pathBC.empty() || pathCD.empty()) {
                pathsizeABCD = -1;
            }

            int pathsizeACBD = pathAC.size() + pathCB.size() + pathBD.size() - 2;
            if (pathAC.empty() || pathCB.empty() || pathBD.empty()) {
                pathsizeACBD = -1;
            }

            cout << pathsizeABCD << " " << pathsizeACBD << endl;

            if ((pathsizeABCD == -1 && pathsizeACBD == -1)) {
                cout << "There are no paths that go through A,B,C, and D!" << endl;
            }
            else if ((pathsizeABCD <= pathsizeACBD && pathsizeABCD > -1) || (pathsizeACBD == -1 && pathsizeABCD > -1)) {
                cout << "The fastest path is from: ";
                for (int i = 0; i < pathAB.size()-1; i++) {
                    cout << intToAirport(pathAB[i]) << " -> ";
                }
                for (int i = 0; i < pathBC.size()-1; i++) {
                    cout << intToAirport(pathBC[i]) << " -> ";
                }
                for (int i = 0; i < pathCD.size(); i++) {
                    if (i == pathCD.size()-1) cout << intToAirport(pathCD[i]);
                    else cout << intToAirport(pathCD[i]) << " -> ";
                }
                cout << endl;
            }
            else if ((pathsizeACBD <= pathsizeABCD && pathsizeACBD > -1) || (pathsizeABCD == -1 && pathsizeACBD > -1)) {
                cout << "The fastest path is from: ";
                for (int i = 0; i < pathAC.size()-1; i++) {
                    cout << intToAirport(pathAC[i]) << " -> ";
                }
                for (int i = 0; i < pathCB.size()-1; i++) {
                    cout << intToAirport(pathCB[i]) << " -> ";
                }
                for (int i = 0; i < pathBD.size(); i++) {
                    if (i == pathBD.size()-1) cout << intToAirport(pathBD[i]);
                    else cout << intToAirport(pathBD[i]) << " -> ";
                }
                cout << endl;
            }

}

vector<tuple<int,int>> findPaths(int startNode, const vector<vector<int>> graph) {
    //POSSIBLY DELETE BUT KEEP FOR NOW IN CASE I NEED IT
    queue<int> toVisit;
    toVisit.push(startNode);
    vector<tuple<int,int>> Paths;
    vector<int> visited;
    while (!toVisit.empty()) {
        int node = toVisit.front();
        toVisit.pop();
        for (int i = 0; i < graph[node].size(); i++) {
            int newNode = graph[node][i];
            if (isInVector(visited, newNode)) continue;
            toVisit.push(newNode);
            Paths.emplace_back(make_tuple(node, newNode));
        }
    }
    return Paths;
}

bool isInQueue(queue<int> list, int node) {
    queue<int> tempQueue(list);
    while (!tempQueue.empty()) {
        int tempNode = tempQueue.front();
        tempQueue.pop();
        if (tempNode == node) return true;
    }
    return false;
}


int findClosestInteresect(int A, int B, int C, const vector<vector<int>> graph) {
    int startingNodes[] = {A, B, C};
    queue<int> Avisited;
    queue<int> Bvisited;
    queue<int> Cvisited;
    for (int i = 0; i < 3; i++) {
        int startNode = startingNodes[i];
        queue<int> toVisit;
        toVisit.push(startNode);
        queue<int> visited;
        while (!toVisit.empty()) {
            int node = toVisit.front();
            toVisit.pop();
            visited.push(node);
            for (int n = 0; n < graph[node].size(); n++) {
                int newNode = graph[node][n];
                if (isInQueue(visited, newNode)) continue;
                toVisit.push(newNode);
            }
        }
        if (i == 0) Avisited = visited;
        else if (i == 1) Bvisited = visited;
        else Cvisited = visited;
    }
    unordered_map<int, int> nodeCount;
    while((!Cvisited.empty()) && (!Bvisited.empty()) && (!Avisited.empty())) {
        int Anode = Avisited.front();
        Avisited.pop();
        if (nodeCount.find(Anode) == nodeCount.end()) nodeCount[Anode] = 1;
        else nodeCount[Anode]++;

        int Bnode = Bvisited.front();
        Bvisited.pop();
        if (nodeCount.find(Bnode) == nodeCount.end()) nodeCount[Bnode] = 1;
        else nodeCount[Bnode]++;

        int Cnode = Cvisited.front();
        Cvisited.pop();
        if (nodeCount.find(Cnode) == nodeCount.end()) nodeCount[Cnode] = 1;
        else nodeCount[Cnode]++;

        for (const auto& [node, count] : nodeCount) {
            if (count >= 3) return node;
        }

    }
    return -1;
}


void findMeetUpCity(string cityA, string cityB, string cityC, const vector<vector<int>> graph) {
    /*TODO: Use BFS going from each city until there is a point in common from all of the cities. That 
    point in common is the point in which is closest to all of the cities that minimizes distance for all.\
    After finding the common point it will find the smallest path for each city and return it to display.
    */

    int icityA = airportToInt(cityA);
    int icityB = airportToInt(cityB);
    int icityC = airportToInt(cityC);

    int meetupcity = findClosestInteresect(icityA, icityB, icityC, graph);

    vector<int> Ashortest = smallestPath(icityA, meetupcity, graph);
    vector<int> BShortest = smallestPath(icityB, meetupcity, graph);
    vector<int> CShortest = smallestPath(icityC, meetupcity, graph);

    string meetupname =  intToAirport(meetupcity);
    cout << "You should meet at: " << meetupname << endl;
    cout << "Route for first person: ";
    string airport;
    for (int i = 0; i < Ashortest.size(); i++) {
        airport = intToAirport(Ashortest.at(i));
        if (i != Ashortest.size()-1) cout << airport << "->";
        else cout << airport << endl;
    }
    cout << "Route for second person: ";
    for (int i = 0; i < BShortest.size(); i++) {
        airport = intToAirport(BShortest.at(i));
        if (i != BShortest.size()-1) cout << airport << "->";
        else cout << airport << endl;
    }
    cout << "Route for last person: ";
    for (int i = 0; i < CShortest.size(); i++) {
        airport = intToAirport(CShortest.at(i));
        if (i != CShortest.size()-1) cout << airport << "->";
        else cout << airport << endl;
    }
}

int main() {
    vector<vector<int>> graph = create_graph();
    int option;
    cout << "1) From city A to city B with at most X connections." << endl;
    cout << "2) Smallest connections from A to D through B and C." << endl;
    cout << "3) City A, City B, and City C meet with smallest connections for all three." << endl;
    cin >> option;
    switch (option) {
        case 1: {
            // TODO: Add git line to deal with spaces
            cout << "Name of city A: ";
            string cityA;
            cin.ignore();
            cin.clear();
            getline(cin, cityA);
            cout << "Name of city B: ";
            string cityB;
            getline(cin, cityB);
            int numCon;
            cout << "Number of Connections: ";
            cin >> numCon;
            smallestConnection(cityA, cityB, numCon, graph);
            break;
        }
        case 2: {
            cin.ignore();
            cin.clear();
            vector<string> cities;
            char CityAlph = 'A';
            //Gather input from the user and put it into a vector
            
            for (int i = 0; i < 4; i++) {
                string input;
                cout << "Enter city " << CityAlph << ": ";
                CityAlph++;
                getline(cin,input);
                cities.emplace_back(input);
            }
            //convert the names into ints and put them in a new vector in same order
            vector<int> intcities;
            for (string name : cities) {
                intcities.emplace_back(airportToInt(name));
            }
            //Find and print the shortest path going through all the cities and starting and ending at the specified cities
            passThroughFourCities(intcities, graph);

            break;
        }
        case 3: {
            string cityA;
            string cityB;
            string cityC;
            cin.ignore();
            cin.clear();
            cout << "Enter city A: ";
            getline(cin, cityA);
            cout << "Enter city B: ";
            getline(cin, cityB);
            cout << "Enter city C: ";
            getline(cin, cityC);
            findMeetUpCity(cityA, cityB, cityC, graph);
            break;
        }
        default:
            cout << "Warning input not recongnized." << endl;

    }

}