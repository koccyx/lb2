#include "MenuItem.h"
#include <iostream>

MenuItem::MenuItem(std::string label, void (*action)()) : label(label), action(action) {}

void MenuItem::execute() {
    action();
}

std::string MenuItem::getLabel() const {
    return label;
}
