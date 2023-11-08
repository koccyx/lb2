#ifndef TIZD_EXCEPTIONS_H
#define TIZD_EXCEPTIONS_H
#include <exception>
#include <iostream>
#include <fstream>
#include <typeinfo>
#include <chrono>
#include <ctime>
#include <string>
#pragma warning(disable : 4996)

class MyException : std::exception {
protected:
    std::string message = "";
public:
    MyException(){}
    
    MyException(std::string msg) {
        try {
            std::ofstream fout;
            fout.open("../txt/exceptions.txt", std::ios_base::app);
            if (fout.is_open()) {
                fout << "\n";
                std::time_t end_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
                fout << msg <<" Current Time and Date: " << ctime(&end_time);
            }
            fout.close();
        }
        catch (...) {

        }
        message = msg;
    }
    virtual std::string getMessage() {
        return message;
    }
};


class InputException : MyException{
public:
    InputException(){}
    InputException(std::string msg) : MyException(msg){}
    virtual std::string getMessage()  override {
        return MyException(message).getMessage();
    };
};


class EmptyException : MyException{
public:
    EmptyException(){}
    EmptyException(std::string msg) : MyException(msg){}
    virtual std::string getMessage()  override {
        return MyException(message).getMessage();
    };
};



#endif //TIZD_EXCEPTIONS_H
