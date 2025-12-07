# Flight Route Search - Course Project By Josiah Snyder

A C++ program that finds optimal flight routes between cities using graph algorithms and breadth-first search (BFS).

## Overview

This program processes airline route data and provides three main functionalities:
1. Find routes between two cities with connection constraints
2. Find optimal routes through multiple waypoint cities
3. Find optimal meetup locations for three people traveling from different cities

## Files

- **`main.cpp`** - Main program logic with BFS implementation and route finding algorithms
- **`create_graph.cpp`** - Graph construction from flight data file
- **`data.hpp`** - Header file with function declarations and includes
- **`flight.txt`** - Input data file containing flight routes (format: `city_from, city_to, distance`)

## Compilation

```bash
g++ -o main main.cpp create_graph.cpp
```

## Usage

Run the compiled program:
```bash
./main
```

The program presents an interactive menu with three options:

### Option 1: Direct Route with Connection Limit
Find the shortest route from city A to city B with at most X connections.

**Example:**
```
1) From city A to city B with at most X connections.
Choose option: 1
Name of city A: New York
Name of city B: Tokyo
Number of Connections: 3

Output:
New York -> Los Angeles -> Seoul -> Tokyo
Number of connections: 2
```

### Option 2: Route Through Multiple Cities
Find the shortest route from city A to city D that passes through both city B and city C (order optimized automatically).

**Example:**
```
2) Smallest connections from A to D through B and C.
Choose option: 2
Enter city A: Paris
Enter city B: London
Enter city C: Berlin
Enter city D: Moscow

Output:
The fastest path is from: Paris -> London -> Berlin -> Warsaw -> Moscow
```

### Option 3: Optimal Meetup Location
Find the best city for three people to meet, minimizing total connections for all travelers.

**Example:**
```
3) City A, City B, and City C meet with smallest connections for all three.
Choose option: 3
Enter city A: Seattle
Enter city B: Miami
Enter city C: Denver

Output:
You should meet at: Chicago
Route for first person: Seattle->Minneapolis->Chicago
Route for second person: Miami->Atlanta->Chicago
Route for last person: Denver->Chicago
```

## Algorithm Details

### Data Structures

- **Adjacency List**: The flight network is represented as a vector of vectors (`vector<vector<int>>`), where each index represents an airport and contains a list of direct destinations
- **Hash Map**: An `unordered_map<string, int>` maps airport names to integer indices for efficient lookup
- **Queue**: Used for BFS traversal to explore the graph level by level

## Input Data Format

The `flight.txt` file should contain flight routes in the following format:
```
City_From, City_To, Distance
```

**Example:**
```
New York, London, 3459
London, Paris, 214
Paris, Berlin, 546
```

**Note**: Distance values are parsed but not used in calculations (only connection count matters).

## Design Decisions
### Why Hash Map for Name Mapping?
- O(1) average lookup time for city name to index conversion
- Efficient for frequent conversions during I/O operations

## License

Educational use only - Fall 2025 Course Project
