#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class Tree {
public:
    string data;
    Tree *left;
    Tree *right;

    Tree(string data) {
        this->data = data;
    }
    Tree(char data) {
        this->data = data;
    }
};

class TreeArr {
public:
    TreeArr(int capacity) : capacity(capacity), size(0) {
        array = new Tree*[capacity];
        for (int i = 0; i < capacity; i++) {
            array[i] = nullptr;
        }
    }

    ~TreeArr() {
        for (int i = 0; i < size; i++) {
            delete array[i];
        }
        delete[] array;
    }

    void push(Tree* node) {
        if (size < capacity) {
            array[size++] = node;
        } else {
            std::cerr << "Stack is full" << std::endl;
        }
    }

    Tree* pop() {
        if (size > 0) {
            Tree* top = array[size - 1];
            array[size - 1] = nullptr;
            size--;
            return top;
        } else {
            std::cerr << "Stack is empty" << std::endl;
            return nullptr;
        }
    }

    Tree* top() {
        if (size > 0) {
            return array[size - 1];
        } else {
            std::cerr << "Stack is empty" << std::endl;
            return nullptr;
        }
    }

private:
    Tree** array;
    int capacity;
    int size;
};

Tree * createNode(string data) {
    return new Tree(data);
}
#include <stack>

Tree * Insert(Tree * t, string data) {
    if (t == nullptr)
    {
        return createNode(data);
    }
    if (data < t->data) {
        t->left = Insert(t->left, data);
    } else if (data > t->data) {
        t->right = Insert(t->right, data);
    }
    return t;
}

Tree * GetMinimum(Tree *node) {
    if (node->right == nullptr && node->left == nullptr) {
        return nullptr;
    }
    if (node->right == nullptr || node->right->data > node->left->data) {
        return node->left;
    } else if (node->left == nullptr || node->left->data > node->right->data) {
        return node->right;
    }
}

Tree * DeleteNode(Tree *_root, string data)
{
    if (_root == nullptr)
        return nullptr;
    if (data == _root->data)
    {
        if (_root->left == nullptr &&
            _root->right == nullptr)
        {
            delete _root;
            return nullptr;
        }
        if (_root->left == nullptr &&
            _root->right != nullptr)
        {
            Tree * temp = _root->right;
            delete _root;
            return temp;
        }
        if (_root->right == nullptr &&
            _root->left != nullptr)
        {
            Tree * temp = _root->left;
            delete _root;
            return temp;
        }
        _root->data = GetMinimum(_root->right)->data;
        _root->right = DeleteNode(_root->right,
                                  _root->data);
        return _root;
    } else {
        if (_root->left != nullptr) {
            _root->left = DeleteNode(_root->left, data);
            return _root;
        }
        if (_root->right != nullptr) {
            _root->right = DeleteNode(_root->right, data);
            return _root;
        }
    }

//    if (data < _root->data)
//    {
//        _root->left = DeleteNode(_root->left,data);
//        return _root;
//    }
//    if (data > _root->data)
//    {
//        _root->right = DeleteNode(_root->right, data);
//        return _root;
//    }
    return _root;
}


void PrintTree(Tree *t, int n, ofstream* fout) {
    int i;
    if (t != NULL) {
        PrintTree(t->right, n + 1, fout);
        for (i = 0; i < n; i++)
            *fout << "    ";
        *fout << t->data;
        PrintTree(t->left, n + 1, fout);
    } else
        *fout << '\n';
}

void PrintAllTree(Tree* t) {
    std::ofstream fout;
    fout.open("../txt/output.txt", std::ios_base::app);
    if (fout.is_open()) {
        fout << "\n";
        PrintTree(t, 5, &fout);
    }
    fout.close();
}
string inficsStr = "";
string preficsStr = "";
string postficsStr = "";

string PreficsTriversial(Tree * t) {
    preficsStr += t->data + " ";
    if (t->left != nullptr) {
        PreficsTriversial(t->left);
    }
    if (t->right != nullptr) {
        PreficsTriversial(t->right);
    }
    return preficsStr;
}

string InficsTriversial(Tree * t) {
    if (t->left != nullptr) {
        InficsTriversial(t->left);
    }
    inficsStr += t->data + " ";
    if (t->right != nullptr) {
        InficsTriversial(t->right);
    }
    return inficsStr;
}

string PostficsTriversial(Tree * t) {
    if (t->left != nullptr) {
        PostficsTriversial(t->left);
    }
    if (t->right != nullptr) {
        PostficsTriversial(t->right);
    }
    postficsStr += t->data + " ";

    return postficsStr;
}

bool isOperator(char c) {
    return c == '+' ||  c == '-' ||  c == '*' || c == '/';
}
bool isOperator(string c) {
    return c == "+" ||  c == "-" ||  c == "*" || c == "/";
}

int getPriority(char op) {
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}



Tree* buildExpressionTree(const string& expression) {
    stack<Tree*> nodes;
    stack<char> operators;

    for (char c : expression) {
        if (c == ' ') continue; // Пропускаем пробелы

        if (isdigit(c)) {
            nodes.push(new Tree(c));
        } else if (c == '(') {
            operators.push(c);
        } else if (c == ')') {
            while (!operators.empty() && operators.top() != '(') {
                Tree* right = nodes.top(); nodes.pop();
                Tree* left = nodes.top(); nodes.pop();
                Tree* opNode = new Tree(operators.top());
                opNode->left = left;
                opNode->right = right;
                operators.pop();
                nodes.push(opNode);
            }
            operators.pop(); // Удаляем открывающую скобку
        } else if (isOperator(c)) {
            while (!operators.empty() && getPriority(operators.top()) >= getPriority(c)) {
                Tree* right = nodes.top(); nodes.pop();
                Tree* left = nodes.top(); nodes.pop();
                Tree* opNode = new Tree(operators.top());
                opNode->left = left;
                opNode->right = right;
                operators.pop();
                nodes.push(opNode);
            }
            operators.push(c);
        }
    }

    return nodes.top();
}

void printExpressionTree(Tree* root) {

    if (isOperator(root->data)) cout << "(";
    printExpressionTree(root->left);
    cout << root->data;
    printExpressionTree(root->right);
    if (isOperator(root->data)) cout << ")";
}