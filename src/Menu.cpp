#include "Menu.h"

Menu::Menu() {
    cout << "--------MENU----------" << endl;

    loadData = LoadData(network);
    menu0();
}

void Menu::menu0() {
    cout << "Insira o número do ficheiro com a rede de transporte a considerar: (0 - Sair)" << endl;

    int fileInt;
    bool validOption;
    do {
        validOption = true;

        cin >> fileInt;
        if (cin.fail()) {
            validOption = false;
            cout << "Opção inválida! Tente novamente" << endl;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
        }
    } while(!validOption);

    if (fileInt == 0)
        return;
    else {
        loadData.loadNetwork(fileInt);
        network = loadData.getNetwork();
    }

    cout << "Pretende:" << endl;
    cout << "1 - Viajar sempre com o mesmo grupo sem se separarem" << endl; //grupos que não se separam
    cout << "2 - Viajar com a possibilidade de o seu grupo se separar" << endl; //grupos que se separam
    cout << "0 - Sair" << endl;
    readOption(1, 2);

    if (!option) {
        cout << "Volte Sempre!" << endl;
        return;
    }
    lastMenu.push(0);
    processOption();
}

void Menu::menu1() {
    cout << "Grupos que não se separam" << endl;
    cout << "Pretende saber:" << endl;
    cout << "3 - A dimensão máxima do grupo com que pode viajar" << endl; // 1.1
    cout << "4 - Comparação entre maximização do tamanho do grupo e minimização do número de transbordos" << endl; // 1.2
    cout << "0 - Voltar ao menu anterior" << endl;
    readOption(3, 4);

    if (!option) {
        option = lastMenu.top();
        lastMenu.pop();
    }
    lastMenu.push(1);
    processOption();
}

void Menu::menu2() {
    cout << "Grupos que se podem separar" << endl;
    cout << "Pretende saber:" << endl;
    cout << "5 - A dimensão máxima do grupo com que pode viajar" << endl; // 2.3
    cout << "6 - Um possível encaminhamento para o seu grupo" << endl; // 2.1
    cout << "0 - Voltar ao menu anterior" << endl;
    readOption(5, 6);

    if (!option) {
        option = lastMenu.top();
        lastMenu.pop();
    }
    lastMenu.push(2);
    processOption();
}

void Menu::menu3() {
    //TODO: call 1.1
}

void Menu::menu4() {
    //TODO: call 1.2
}

void Menu::menu5() {
    //TODO: call 2.3
}

void Menu::menu6() {
    //TODO: call 2.1
}

void Menu::readOption(int minOption, int maxOption) {
    bool validOption;
    do {
        validOption = true;

        cin >> option;
        if (cin.fail() || ((option < minOption || option > maxOption) && option != 0)) {
            validOption = false;
            cout << "Opção inválida! Tente novamente" << endl;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
        }
    } while (!validOption);
}

void Menu::processOption() {
    switch (option) {
        case 0: menu0(); break;
        case 1: menu1(); break;
        case 2: menu2(); break;
        case 3: menu3(); break;
        case 4: menu4(); break;
        case 5: menu5(); break;
        case 6: menu6(); break;
    }
}