/******************************************
 * take in a map of adjacent rooms
 * place the keys that unlock certain doors in their designated rooms
 * DFS the map to search for a key
 * if a key is found, unlock the door and DFS for the next key/exit
 * if no keys are found, return a "", meaning there is no possible exit
 * if the exit is reached, Leon has escaped
******************************************/
#include <iostream>
#include <fstream>
#include <vector>
#include "hashMap.hpp"
#include "vertex.hpp"
using namespace std;

string running(string, hashMap<string, vertex<string>>&, hashMap<string, vector<string>>&, hashMap<string, bool> &);

int main()
{
    string file;
    fstream inFile;
    //take in vector of all location names
    vector<string> uniqueLocations;
    //keeps track of rooms that are adjacent
    hashMap<string, vertex<string>> map;

    cin >> file;

    inFile.open(file);

    string location1;
    string location2;

    //while there are still locations
    while (!inFile.eof())
    {
        //take in adjacent locations
        inFile >> location1 >> location2;
        if (inFile.eof())
        {
            break;
        }

        //establish the doors between rooms
        map[location1].addEdge(location2);
        map[location2].addEdge(location1);

        //insert unique rooms in to vector
        if (uniqueLocations.size() == 0)
        {
            uniqueLocations.push_back(location1);
            uniqueLocations.push_back(location2);
        }

        bool exist = false;

        //check if the room is already in the vector
        for (int i = 0; i < uniqueLocations.size(); i++)
        {
            if (uniqueLocations[i] == location1)
            {
                exist = true;
                break;
            }
        }

        //if its new add to vector
        if (!exist)
        {
            uniqueLocations.push_back(location1);
        }

        exist = false;
        //check if the room is already in the vector

        for (int i = 0; i < uniqueLocations.size(); i++)
        {
            if (uniqueLocations[i] == location2)
            {
                exist = true;
                break;
            }
        }

        //if its new add to vector
        if (!exist)
        {
            uniqueLocations.push_back(location2);
        }

    }

    inFile.close();
    //map of where the keys are located and which doors they unlock
    hashMap<string, vector<string>> keys;

    cin >> file;

    inFile.open(file);

    string location3;

    //while there are still keys to be placed
    while (!inFile.eof())
    {
        inFile >> location1 >> location2 >> location3;
        if (inFile.eof())
        {
            break;
        }

        //establish location of keys, pushback rooms it unlocks
        keys[location1].push_back(location2);
        keys[location1].push_back(location3);
    }

    string curr = "MainHall";

    //it is the player going through the rooms
    vertex<string>::edgeIterator it;
    //mark places that have been visited
    hashMap<string, bool> visited;
    //"" represents deadend, while there are still rooms to search
    while(curr != "")
    {
        //call dfs starting at curr location
        curr = running (curr, map, keys, visited);
        //if there is a key, remove it
        keys[curr].clear();
        //if a deadend occurs with no key found, break out of dfs loop, player has not escaped
        if (curr == "")
        {
            break;
        }

        //if exit is reached, player has escaped
        if (curr == "Exit")
        {
            cout << "Ok Leon, you escaped the police station, now to find Ada" << endl;
            return 0;
        }

        //reset all of the locations, setting everything to false
        for (int i = 0; i < uniqueLocations.size(); i++)
        {
            visited[uniqueLocations[i]] = false;
        }
    }

    cout << "Ok Leon, your first day will be your last day on the force" << endl;
}

/**********************************************
 *  running(string, hashMap<string, vertex<string>>&, hashMap<string, vector<string>>&, hashMap<string, bool>&)
 *      DFS function
 *      parameter: 
 *          string: current location, dfs starts there
 *          hasMap<string, vertex<string>>&: hashMap map of adjacent rooms
 *          hashMap<string, vector<string>>&: hashMap location of keys
 *          hashMap<string, bool>&: keeps track of locations visited
 *      begin searching through all the rooms avaliable
 *      if a key is found, return the location of the room and unlock the door associated with the key
 *      for loop through potential rooms to check, if it is already visited do not check
 *      if a room is returned, then return back
 *      if every rooms has been checked, return ""
**********************************************/
string running(string curr, hashMap<string, vertex<string>>& map, hashMap<string, vector<string>>& keys, hashMap<string, bool>& visited)
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
        //if there is a key, unlock the path
        map[keys[curr][0]].addEdge(keys[curr][1]);
        map[keys[curr][1]].addEdge(keys[curr][0]);
        //return the room where the key was found
        return curr;
    }

    //if no key was found, determine which room to search next
    vertex<string>::edgeIterator it;
    for (it = map[curr].begin(); it != map[curr].end(); it++)
    {
        //if you have not visited this room,
        if (visited[*it] == false)
        {
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
