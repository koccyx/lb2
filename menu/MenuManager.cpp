#include "MenuManager.h"
#include <iostream>
#include <cctype>
#include "../exceptions/exceptions.h"

void MenuManager::addMenuItem(MenuItem item) {
    menuItems.push_back(item);
}

void MenuManager::showMenu() {
    int choice;
        do {
            std::cout << "Menu:\n";
            for (int i = 0; i < menuItems.size(); ++i) {
                std::cout << i + 1 << ". " << menuItems[i].getLabel() << "\n";
            }
            std::cout << "0. exit\n";
            try {
                std::cout << "Input a number: ";
                std::cin >> choice;
                if (std::cin.fail()) {
                    choice = 100000;
                    InputException("Invalid choice, try again\n");
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                } else if (std::cin.good() && choice > 0 && choice <= menuItems.size()) {
                    menuItems[choice - 1].execute();
                }

            } catch (...) {
            }
        } while (choice != 0 );
}





