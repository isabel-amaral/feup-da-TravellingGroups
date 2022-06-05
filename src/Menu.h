#ifndef FEUP_DA_TRAVELLINGGROUPS_MENU_H
#define FEUP_DA_TRAVELLINGGROUPS_MENU_H

#include "Graph.h"
#include "LoadData.h"
#include <iostream>
#include <stack>

using namespace std;

class Menu {
    Graph network;
    LoadData loadData;
    vector<vector<int>> paths;
    int src, dest, dim, reunite;

    stack<int> lastMenu;
    int option;

public:
    Menu();
    void readOption(int minOption, int maxOption);
    void processOption();

    void menu0();
    void menu1();
    void menu2();
    void menu3();
    void menu4();
    void menu5();
    void menu6();
    void menu7();
    void menu8();
    void menu9();
};

#endif //FEUP_DA_TRAVELLINGGROUPS_MENU_H
