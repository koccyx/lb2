#include "menu/MenuManager.h"
#include <iostream>
#include <fstream>
using namespace std;
#include "tree.h"
#include "exceptions/exceptions.h"

Tree* tr = nullptr;
string expression = "";

void loadExpression() {
    int fileIter = 0;
    ifstream fin;
    fin.open("../txt/input.txt");
    string *arr {new string[0]{}};
    string str;
    try {
        if(!fin.is_open()) {
            cout << "mistake file";
        } else {
            while (!fin.eof()) {
                fin >> str;
                expression += str;
            }
        }
    } catch (string error) {

    }
    fin.close();
    delete[] arr;

    tr = buildExpressionTree(expression);
    cout << "Success loading\n";
}



void PrintTree() {
    if (tr == nullptr) {
        EmptyException("Tree is empty, please load it\n");
    } else {
        PrintAllTree(tr);
    }
}

void prefics() {
    if (tr == nullptr) {
        EmptyException("Tree is empty, please load it\n");
    } else {
        std::ofstream fout;
        fout.open("../txt/output.txt", std::ios_base::app);
        if (fout.is_open()) {
            fout << "\n";
            fout << PreficsTriversial(tr);
            fout << '\n';
        }
        fout.close();
    }
}

void infics() {
    if (tr == nullptr) {
        EmptyException("Tree is empty, please load it\n");
    } else {
        std::ofstream fout;
        fout.open("../txt/output.txt", std::ios_base::app);
        if (fout.is_open()) {
            fout << "\n";
            fout << InficsTriversial(tr);
            fout << '\n';
        }
        fout.close();
    }
}

void postfics() {
    if (tr == nullptr) {
        EmptyException("Tree is empty, please load it\n");
    } else {
        std::ofstream fout;
        fout.open("../txt/output.txt", std::ios_base::app);
        if (fout.is_open()) {
            fout << "\n";
            fout << PostficsTriversial(tr);
            fout << '\n';
        }
        fout.close();
    }
}

void deleteNode() {
    string data;
    cout << "Input node: ";
    cin >> data;
    DeleteNode(tr, data);
}

int main() {
    MenuManager menuManager;
    menuManager.addMenuItem(MenuItem("Load expression from file", loadExpression));
    menuManager.addMenuItem(MenuItem("Print tree", PrintTree));
    menuManager.addMenuItem(MenuItem("Delete node", deleteNode));
    menuManager.addMenuItem(MenuItem("Infics traversal", infics));
    menuManager.addMenuItem(MenuItem("Prefics traversal", prefics));
    menuManager.addMenuItem(MenuItem("Postfics traversal", postfics));

//    menuManager.addMenuItem(MenuItem("Remove item", remove));
//    menuManager.addMenuItem(MenuItem("Print", print));ss
//    menuManager.addMenuItem(MenuItem("Sort", sort));
//    menuManager.addMenuItem(MenuItem("Input from file", fileTest));

    menuManager.showMenu();

    return 0;
}
