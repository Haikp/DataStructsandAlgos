#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
//#include "hashMap.hpp"
#include "vertex.hpp"
using namespace std;

string running(string, unordered_map<string, vertex<string>>&, unordered_map<string, vector<string>>&, unordered_map<string, bool> &);

int main()
{
    string file;
    fstream inFile;
    vector<string> uniqueLocations;
    unordered_map<string, vertex<string>> map;

    cout << "police station map" << endl;
    cin >> file;

    inFile.open(file);

    string location1;
    string location2;

    while (!inFile.eof())
    {
        inFile >> location1 >> location2;
        if (inFile.eof())
        {
            break;
        }

        map[location1].addEdge(location2);
        map[location2].addEdge(location1);
/*
        cout << location1 << " " << location2 << endl;

        if (uniqueLocations.size() == 0)
        {
            uniqueLocations.push_back(location1);
            uniqueLocations.push_back(location2);
            continue;
        }

        for (int i = 0; i < uniqueLocations.size(); i++)
        {
            if (uniqueLocations[i] == location1)
            {
                break;
            }

            uniqueLocations.push_back(location1);
        }

        for (int i = 0; i < uniqueLocations.size(); i++)
        {
            if (uniqueLocations[i] == location2)
            {
                break;
            }

            uniqueLocations.push_back(location2);
        }
        */
    }

    inFile.close();
    unordered_map<string, vector<string>> keys;

    cout << "keys file" << endl;
    cin >> file;

    inFile.open(file);

    string location3;

    while (!inFile.eof())
    {
        inFile >> location1 >> location2 >> location3;
        if (inFile.eof())
        {
            break;
        }

        keys[location1].push_back(location2);
        keys[location1].push_back(location3);
    }
    string curr = "MainHall";

    while(curr != "")
    {
        unordered_map<string, bool> visited;
        curr = running (curr, map, keys, visited);
        keys[curr].clear();
        //cout << "curr = " << curr << endl;
        if (curr == "")
        {
            break;
        }

        if (curr == "Exit")
        {
            cout << "Ok Leon, you escaped the police station, now to find Ada" << endl;
            return 0;
        }

        visited.clear();

/*
        for (int i = 0; i < uniqueLocations.size(); i++)
        {
            visited[uniqueLocations[i]] = false;
        }
        */
    }

    cout << "Ok Leon, your first day will be your last day on the force" << endl;
}

string running(string curr, unordered_map<string, vertex<string>>& map, unordered_map<string, vector<string>>& keys, unordered_map<string, bool>& visited)
{
    string room;
    //mark the location as visited
    visited[curr] = true;

    //if we are at the Exit, you escaped
    if (curr == "Exit")
    {
        return curr;
    }

    //check if there is a key within the room
    if (keys[curr].size() != 0)
    {
        cout << "key found at " << curr << endl;
        //if there is a key, unlock the path
        map[keys[curr][0]].addEdge(keys[curr][1]);
        map[keys[curr][1]].addEdge(keys[curr][0]);
        //return the room where the key was found
        return curr;
    }

    //if no key was found, determine which room to search next
    vertex<string>::edgeIterator it;
    it = map[curr].begin();
    cout << *it << endl;
    for (it = map[curr].begin(); it != map[curr].end(); it++)
    {
        //if you have not visited this room,
        if (visited[*it] == false)
        {
            cout << "enter room " << *it << endl;
            //enter the room and repeat the function
            room = running (*it, map, keys, visited);
            if (room != "")
            {
                return room;
            }
        }
    }

    //if nothing was found in the end, return "", you did not escape
    return "";
}
