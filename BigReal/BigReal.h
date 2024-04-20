//
// Created by Osos on 24/10/2023.
//
#include <iostream>
#include <cstring>
#include <utility>
using namespace std;
#ifndef LAB_BIGREAL_H
#define LAB_BIGREAL_H

class BigReal {
private:
    string number;
    string furction;
    char sign;
    BigReal(string,int);
    string performArithmeticOperation(string ,string,string ,string,char);
    pair<string,string> find_max_number(string,string ,string,string);
    pair<string,string > divide_number(string );

public:
    BigReal();
    BigReal(string);
    BigReal operator+ (const BigReal& );
    BigReal operator- (const BigReal& );
    BigReal operator= (const BigReal& );
    bool operator< (BigReal );
    bool operator> (BigReal );
    bool operator== (BigReal );
    string get();
    void set(string);
    friend ostream& operator << (ostream& out, BigReal& num);
};


#endif //LAB_BIGREAL_H
