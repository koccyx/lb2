#ifndef MENU_MANAGER_H
#define MENU_MANAGER_H

#include <vector>
#include "MenuItem.h"

class MenuManager {
public:
    void addMenuItem(MenuItem item);
    void showMenu();

private:
    std::vector<MenuItem> menuItems;
};

#endif
