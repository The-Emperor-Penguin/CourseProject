#include "data.hpp"

unordered_map<string, int> airport_to_int;

vector<vector<int>> create_graph(string filename) {
    //Return adjacency list from the given file
    vector<vector<int>> graph;
    string line;
    ifstream file(filename);
    if (file.is_open()) {
        while (getline(file, line)) {
            
            int parent, child;
            tie(parent, child) = readLine(line);
            while (graph.size() <= parent) {
                graph.emplace_back(vector<int>());
            }
            graph.at(parent).emplace_back(child);
        }
    }
    file.close();
    return graph;
}

tuple<int, int> readLine(string line) {
    //read the first two parts of each line and ignore distance
    string data;
    int firstNode;
    int secondNode;
    int pos = line.find(',');
    data = line.substr(0, pos);
    line = line.substr(pos+2);
    firstNode = airportToInt(data);
    pos = line.find(',');
    data = line.substr(0, pos);
    secondNode = airportToInt(data);
    return make_tuple(firstNode, secondNode);

}   

bool airportInMap(string airpotName) {
    // returns true if there is an airpot in the map
    if (airport_to_int.find(airpotName) == airport_to_int.end()) return false;
    return true;
}

int airportToInt(string airportName) {
    // converts the airport name to a unique number for the adjacency list
    if (airport_to_int.find(airportName) == airport_to_int.end()){
        int size = 0;
        for (const auto [key, value] : airport_to_int) size++;
        airport_to_int[airportName] = size;
    }
    return airport_to_int.find(airportName)->second;
}

string intToAirport(int node) {
    // Converts a number back into the airport name (mainly for displaying it to user)
    // Will return an empty string if it doesn't exist in the map
    if (node >= airport_to_int.size()) return "";
    for(const auto& [key, value] : airport_to_int) {
        if (value == node) return key;
    }
    return "";
};

void printAdjList(vector<vector<int>> graph) {
    // Easily prints out the adjacancy list (used mainly for debugging)
    for (int i = 0; i < graph.size(); i++) {
        cout << intToAirport(i) << ": ";
        for (auto code : graph[i]) {
            cout << intToAirport(code) << " ";
        }
        cout << endl;
    }
}

int test_main() {
    // Used to debug file
    auto graph = create_graph();
    printAdjList(graph);
    return 0;
}