#include "data.hpp"

vector<vector<int>> create_graph(string filename) {
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
    if (airport_to_int.find(airpotName) == airport_to_int.end()) return false;
}

int airportToInt(string airportName) {
    if (airport_to_int.find(airportName) == airport_to_int.end()){
        int size = 0;
        for (const auto [key, value] : airport_to_int) size++;
        airport_to_int[airportName] = size;
    }
    return airport_to_int.find(airportName)->second;
}

string intToAirport(int node) {
    if (node >= airport_to_int.size()) return "";
    for(const auto& [key, value] : airport_to_int) {
        if (value == node) return key;
    }
    return "";
};

void printAdjList(vector<vector<int>> graph) {
    for (int i = 0; i < graph.size(); i++) {
        cout << intToAirport(i) << ": ";
        for (auto code : graph[i]) {
            cout << intToAirport(code) << " ";
        }
        cout << endl;
    }
}

int test_main() {
    auto graph = create_graph();
    printAdjList(graph);
    return 0;
}