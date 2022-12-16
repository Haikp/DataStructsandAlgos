#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <fstream>
#include "binTree.hpp"
using namespace std;

struct visibilityType
{
    int id;
    bool camera;
    bool seen;

    bool operator==(int x)
    {
        return id == x;
    }
};

vector<visibilityType> parseLine(string);
void cameraPlacement(binTree<visibilityType>::binTreeIterator);

int main(int argc, char *argv[])
{
    ifstream inFile;
    inFile.open(argv[1]);

    string cases;
    int totalCases;
    getline(inFile, cases);
    totalCases = stoi(cases);


    vector<visibilityType> caseValues;
    binTree<visibilityType> constructTree;

    for (int i = 0; i < totalCases; i++)
    {
        getline(inFile, cases);
        caseValues = parseLine(cases);
        constructTree.buildTree(caseValues);
    }

    binTree<visibilityType>::binTreeIterator iter(constructTree.rootIterator());
    int cameraQuantity = 0;
    cameraPlacement(iter);

    return 0;
}

vector<visibilityType> parseLine(string line)
{
    stringstream s(line);
    vector<visibilityType> parsedLine;
    visibilityType n;

    while (s >> n.id)
    {
        n.seen = n.camera = false;
        parsedLine.push_back(n);
    }

    return parsedLine;
}

void cameraPlacement(binTree<visibilityType>::binTreeIterator iter)
{
    binTree<visibilityType>::binTreeIterator nil(nullptr);
    string useless;

    if (iter.leftChild() != nil)
    {
        cout << "left " << endl;
        //cin >> useless;
        (*iter).camera = true;
        (*iter).seen = true;
        cameraPlacement(iter.leftChild());
    }

    if (iter.rightChild() != nil)
    {
        cout << "right " << endl;
        //cin >> useless;
        (*iter).camera = true;
        (*iter).seen = true;
        cameraPlacement(iter.rightChild());
    }

    if ((iter.leftChild() == nil) && (iter.rightChild() == nil))
    {
        return;
    }

    if ((*iter.leftChild()).camera == true || (*iter.rightChild()).camera == true)
    {
        if((*iter.leftChild()).seen == false || (*iter.rightChild()).seen == false)
        {
            (*iter.leftChild()).seen = true;
            (*iter.rightChild()).seen = true;
            return;
        }
        (*iter).camera = false;
    }

    cout << "finished node" << endl;
}
