#include <iostream>
#include <string>
#include "vertex.hpp"

using namespace std;

int main(){
    vertex<int> road;
    road.addEdge(1);
    road.addEdge(2);
    road.addEdge(3);

    cout << "orig" << endl;
    road.print();


    cout << "copy" << endl;
    vertex<int> copy(road);
    copy.print();

    
    cout << "assign" << endl;
    vertex<int> assign;
    assign = copy;
    assign.print();
    
    return 0;
}