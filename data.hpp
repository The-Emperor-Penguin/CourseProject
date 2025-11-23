#ifndef DATA
#define DATA

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <string>
#include <unordered_map>
#include <tuple>
using namespace std;

vector<vector<int>> create_graph(string filename = "flight.txt");
tuple<int, int> readLine(string line);
unordered_map<string, int> airport_to_int;
int airportToInt(string airportName);
void printAdjList(vector<vector<int>> graph);
string intToAirport(int node);
bool airportInMap(string airpotName);

#endif