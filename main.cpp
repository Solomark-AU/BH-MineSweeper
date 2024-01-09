#include "include/generatoch.hpp"
#include <iostream>
#include <string>
using namespace std;

string order;

int main() {
    tileMap map(15, 15, 24);
    while (true) {
        cin >> order;
        if (order == "exit")
            break;
        else if (order == "sweep") {
            int x, y;
            cin >> x >> y;
            if (!map.sweep(x, y)) {
                cout << "Die\n";
                break;
            }
        }
        else if (order == "display")
            map.display_map();
        else
            cout << "Error\n";
    }
    return 0;
}