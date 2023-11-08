#ifndef MENU_ITEM_H
#define MENU_ITEM_H

#include <string>

class MenuItem {
public:
    MenuItem(std::string label, void (*action)());

    void execute();
    std::string getLabel() const;

private:
    std::string label;
    void (*action)();
};

#endif
