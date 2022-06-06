#include "Menu.h"

Menu::Menu() {
    cout << "--------MENU----------" << endl;

    loadData = LoadData(network);
    menu0();
}

void Menu::menu0() {
    cout << "Insira o numero do ficheiro com a rede de transporte a considerar: (0 - Sair)" << endl;

    int fileInt;
    bool validOption;
    do {
        validOption = true;

        cin >> fileInt;
        if (cin.fail()) {
            validOption = false;
            cout << "Opçao invalida! Tente novamente" << endl;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
        }
    } while(!validOption);

    if (fileInt == 0)
        return;
    else {
        if (!loadData.loadNetwork(fileInt))
            return;
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
    cout << "Grupos que nao se separam" << endl;
    cout << "Pretende saber:" << endl;
    cout << "3 - A dimensao maxima do grupo com que pode viajar" << endl; // 1.1
    cout << "4 - O caminho com menor numero de transbordos" << endl; // 1.2
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
    cout << "5 - A dimensao maxima do grupo com que pode viajar" << endl; // 2.3
    cout << "6 - Um possivel encaminhamento para o seu grupo" << endl; // 2.1
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
    int src, dest;
    cout << "Indique a origem: " << endl; cin >> src;
    cout << "Indique o destino: " << endl; cin >> dest;
    cout << endl;
    network.maxCapacity(src, dest);

    cout << endl;
    string aux;
    cout << "Pressione qualquer tecla para voltar" << endl;
    cin.ignore(INT_MAX, '\n');
    getline(cin, aux);
    option = lastMenu.top();
    lastMenu.pop();
    processOption();
}

void Menu::menu4() {
    int src, dest;
    cout << "Indique a origem: " << endl; cin >> src;
    cout << "Indique o destino: " << endl; cin >> dest;
    cout << endl;
    network.minTranshipments(src, dest);

    cout << endl;
    string aux;
    cout << "Pressione qualquer tecla para voltar" << endl;
    cin.ignore(INT_MAX, '\n');
    getline(cin, aux);
    option = lastMenu.top();
    lastMenu.pop();
    processOption();
}

void Menu::menu5() {
    int src, dest;
    cout << "Indique a origem: " << endl; cin >> src;
    cout << "Indique o destino: " << endl; cin >> dest;
    cout << endl;
    network.getMaxFlow(src, dest);

    cout << endl;
    string aux;
    cout << "Pressione qualquer tecla para voltar" << endl;
    cin.ignore(INT_MAX, '\n');
    getline(cin, aux);
    option = lastMenu.top();
    lastMenu.pop();
    processOption();
}

void Menu::menu6() {
    cout << "Indique a origem: " << endl; cin >> src;
    cout << "Indique o destino: " << endl; cin >> dest;
    cout << "Indique a dimensao do grupo: " << endl; cin >> dim;
    cout << endl;
    Graph residualNetwork = network;
    paths = residualNetwork.separateGroup(src, dest, dim, network);

    cout << endl;
    cout << "7 - Pretende adicionar pessoas extra ao seu grupo?" << endl;
    cout << "8 - Pretende saber em que paragem todos os elementos do grupo se poderao encontrar\n para depois viajarem juntos ate ao final?" << endl;
    cout << "0 - Voltar ao menu anterior" << endl;
    readOption(7, 8);

    if (!option) {
        option = lastMenu.top();
        lastMenu.pop();
    }
    processOption();
}

void Menu::menu7() {
    int extra;
    cout << "Indique o numero de pessoas extra: " << endl; cin >> extra;
    cout << endl;
    Graph residualNetwork = network;
    paths = residualNetwork.separateGroup(src, dest, dim, network, extra);

    cout << endl;
    string aux;
    cout << "Pressione qualquer tecla para voltar" << endl;
    cin.ignore(INT_MAX, '\n');
    getline(cin, aux);
    option = lastMenu.top();
    lastMenu.pop();
    processOption();
}

void Menu::menu8() {
    network.reuniteGroup(src, dest, paths);

    cout << endl;
    cout << "9 - Pretende saber quanto tempo os restantes grupos terao de esperar pelo ultimo grupo a chegar?" << endl;
    cout << "0 - Voltar ao menu anterior" << endl;
    readOption(9, 9);
    if (!option) {
        option = lastMenu.top();
        lastMenu.pop();
    }
    processOption();
}

void Menu::menu9() {
    network.waitTime(src, reunite, paths);

    cout << endl;
    string aux;
    cout << "Pressione qualquer tecla para voltar" << endl;
    cin.ignore(INT_MAX, '\n');
    getline(cin, aux);
    option = lastMenu.top();
    lastMenu.pop();
    processOption();
}

void Menu::readOption(int minOption, int maxOption) {
    bool validOption;
    do {
        validOption = true;

        cin >> option;
        if (cin.fail() || ((option < minOption || option > maxOption) && option != 0)) {
            validOption = false;
            cout << "Opçao invalida! Tente novamente" << endl;
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
        case 7: menu7(); break;
        case 8: menu8(); break;
        case 9: menu9(); break;
    }
}