#include "data.hpp"



void smallestConnection(string cityA, string cityB, int maxCon) {
    //Posibly need to check if it exist first before since it would create a new index in the table!!
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