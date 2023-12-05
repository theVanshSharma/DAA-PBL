#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <limits>
#include <algorithm>

using namespace std;

struct Edge
{
    string destination;
    int distance;
};

struct Location
{
    string name;
    vector<Edge> neighbors;
};

map<string, Location> locations;

pair<int, vector<string>> dijkstra(string start, string end)
{
    map<string, int> distance;
    map<string, string> parent;
    set<pair<int, string>> pq;

    for (const auto &pair : locations)
    {
        string locName = pair.first;
        distance[locName] = numeric_limits<int>::max();
        pq.insert({numeric_limits<int>::max(), locName});
    }

    distance[start] = 0;
    pq.insert({0, start});

    while (!pq.empty())
    {
        string current = pq.begin()->second;
        pq.erase(pq.begin());

        for (const Edge &neighbor : locations[current].neighbors)
        {
            int alt = distance[current] + neighbor.distance;
            if (alt < distance[neighbor.destination])
            {
                pq.erase({distance[neighbor.destination], neighbor.destination});
                distance[neighbor.destination] = alt;
                parent[neighbor.destination] = current;
                pq.insert({alt, neighbor.destination});
            }
        }
    }

    int shortestDistance = distance[end];
    vector<string> path;
    string current = end;
    while (current != start)
    {
        path.push_back(current);
        current = parent[current];
    }
    path.push_back(start);
    reverse(path.begin(), path.end());

    return make_pair(shortestDistance, path);
}

int main()
{
    locations["A"] = {"A", {{"B", 1}, {"C", 4}}};
    locations["B"] = {"B", {{"A", 1}, {"D", 2}, {"E", 5}}};
    locations["C"] = {"C", {{"A", 4}, {"F", 3}}};
    locations["D"] = {"D", {{"B", 2}}};
    locations["E"] = {"E", {{"B", 5}, {"F", 1}}};
    locations["F"] = {"F", {{"C", 3}, {"E", 1}}};

    string startLocation, endLocation;
    cout << "Enter start location: ";
    cin >> startLocation;
    cout << "Enter end location: ";
    cin >> endLocation;

    pair<int, vector<string>> result = dijkstra(startLocation, endLocation);

    int shortestDistance = result.first;
    vector<string> shortestPath = result.second;

    if (shortestDistance == numeric_limits<int>::max())
    {
        cout << "No path found between " << startLocation << " and " << endLocation << endl;
    }
    else
    {
        cout << "Shortest distance from " << startLocation << " to " << endLocation << ": " << shortestDistance << endl;
        cout << "Shortest path: ";
        for (size_t i = 0; i < shortestPath.size(); ++i)
        {
            cout << shortestPath[i];
            if (i < shortestPath.size() - 1)
            {
                cout << " -> ";
            }
        }
        cout << endl;
    }

    return 0;
}