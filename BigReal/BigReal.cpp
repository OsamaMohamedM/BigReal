// FCAI –OOP Programming– 2023 - Assignment 2
// Program: main.cpp
// Purpose:Bigreal number
// Author1: Osama Mohamed Mahmoud  , Id: 20220056 ,section_number=S5
// Author2:Deyaa El-Din Ahmed      ,ID: 20221091 ,section_number=NO Section
// Author3:Marawan Shrief Abdelatef,ID:20220325  ,section_number=s5
// last UpDate:9/10/2023
//Version: 1.0
#include "BigReal.h"
#include <iostream>
#include <cstring>
#include <utility>
#include <algorithm>
using namespace std;
BigReal::BigReal(string num , int n) {
    pair<string,string > tmp =divide_number(num);
    sign=tmp.first[0];
    integer=tmp.first.substr(1);
    fraction=tmp.second;
    int idx=num.size();
    for(int i=0; i < integer.size(); i++)
    {
        if(integer[i] != '0') {
            idx = i;
            break;
        }
    }
    long long sz=fraction.size();
    while(fraction.back()=='0' && sz>1)
    {
        sz--;
        fraction.pop_back();
    }
    integer.erase(0, idx);
    if(integer.empty())
        integer="0";
    if(fraction.empty())fraction="0";

}
bool BigReal::isvalid(string num) {
    if(num.back()=='+' ||num.back()=='-' || num.back()=='.' || (num[0]!='+' &&  num[0]!='-'&& !isdigit(num[0])) )
        return false;
    bool flag=true;
    for(int i=0;i<num.size();i++)
    {
        if(i) {
            if (num[i] == '.') {
                flag = !flag;
                if (flag)
                    return false;
            }
          else if (!(num[i] >= '0' && num[i] <= '9'))
              return false;
      }
    }
    return true;
}
string BigReal::performArithmeticOperation(string operandA, string fractionalPartA, string operandB, string fractionalPartB, char operation) {
    // Normalize fractional parts by adding leading zeros
    while (fractionalPartA.size() != fractionalPartB.size()) {
        if (fractionalPartA.size() < fractionalPartB.size()) {
            fractionalPartA += '0';
        } else {
            fractionalPartB += '0';
        }
    }

    // Normalize integer parts by adding leading zeros
    while (operandA.size() != operandB.size()) {
        if (operandA.size() < operandB.size()) {
            operandA = '0' + operandA;
        } else {
            operandB = '0' + operandB;
        }
    }
    // Ensure that operandA is greater when subtracting
    if (operandA < operandB) {
        swap(operandA, operandB);
        swap(fractionalPartA, fractionalPartB);
    }
    int i = fractionalPartA.size() - 1;
    int carry = 0;
    int digitA, digitB, sum;
    string fractionalResult = "";
    while (i >= 0 ) {
        digitA =  (fractionalPartA[i] - '0');
        digitB =  (fractionalPartB[i--] - '0');// 5.30 3.56

        if (operation == '+') {
            sum = digitA + digitB + carry;
        } else if (operation == '-') {
            sum = digitA - digitB - carry;
        }

        if (sum < 0) {
            carry = 1;
            sum += 10;
        } else {
            carry = sum / 10;
        }

        fractionalResult = char((sum % 10) + '0') + fractionalResult;
    }

    i = operandA.size() - 1;

    string integerResult = "";

    while (i >= 0  || carry > 0) {
        digitA =  (operandA[i] - '0');
        digitB =  (operandB[i--] - '0');

        if (operation == '+') {
            sum = digitA + digitB + carry;
        } else if (operation == '-') {
            sum = digitA - digitB - carry;
        }

        if (sum < 0) {
            carry = 1;
            sum += 10;
        } else {
            carry = sum / 10;
        }

        integerResult = char((sum % 10) + '0') + integerResult;
    }

    if (integerResult.empty()) {
        integerResult = "0";
    }
    if(fractionalResult.empty())
        fractionalResult="0";

    return integerResult + '.' + fractionalResult;
}
pair<string,string> BigReal::find_max_number(string num1, string frc1, string num2, string frc2) {

    if(num1.size()>num2.size())return {num1,frc1};
    if(num1.size()<num2.size())return {num2,frc2};
    if(num1!=num2)return max(make_pair(num1,frc1), make_pair(num2,frc2));
    string tmp1=frc1,tmp2=frc2;
    while(frc1.size()!=frc2.size())
    {
        if(frc1.size()<frc2.size())frc1+='0';
        else frc2+='0';
    }
    if(frc1>frc2)return {num1,tmp1};
    else return {num2,tmp2};
}
pair<string, string> BigReal::divide_number(string num) {
    char sign;
    string number,furction;
    if(num[0]=='-') {
        sign = '-';
    }
    else {

        sign = '+';
    }
    if(!isdigit(num[0]))
        num.erase(0,1);
    bool flag=true;
    number="";
    furction="";
    long long sizeofnumber=num.size();
    for(int i=0;i<sizeofnumber;i++)
    {
        if(num[i]=='.')
            flag=false;
        else if(flag)number+=num[i];
        else furction+=num[i];
    }
    return (make_pair(sign+number,furction));
}
BigReal::BigReal(): integer("0"), sign(' '), fraction("0") {}
BigReal::BigReal(double s) {
    string num= to_string(s);
    if(!isvalid(num))
    {
        cout<<"Invaild integer\n";
        return;
    }
    pair<string,string > tmp =divide_number(num);
    sign=tmp.first[0];
    integer=tmp.first.substr(1);
    fraction=tmp.second;
}
BigReal::BigReal(string num) {
    if(!isvalid(num))
    {
        cerr<<"[!] Invalid integer\n";
        return;
    }
    pair<string,string > tmp =divide_number(num);
    sign=tmp.first[0];
    integer=tmp.first.substr(1);
    fraction=tmp.second;
}
BigReal BigReal::operator+(const BigReal &otherNumber) {

    // Find the integer with greater absolute value
    pair<string, string> maxNumber = find_max_number(integer, fraction, otherNumber.integer, otherNumber.fraction);

    string result;
    if (sign == otherNumber.sign) {
        // Perform addition if signs are the same
        result = performArithmeticOperation(integer, fraction, otherNumber.integer, otherNumber.fraction, '+');

        // If both numbers are negative, result should be negative
        if (sign == '-') {
            result = '-' + result;
        }
    } else {
        // Perform subtraction if signs are different
        result = performArithmeticOperation(integer, fraction, otherNumber.integer, otherNumber.fraction, '-');

        // Check if this integer has the greater absolute value and is negative
        if (integer == maxNumber.first && sign == '-') {
            result = '-' + result;
        } else if (maxNumber.first == otherNumber.integer && otherNumber.sign == '-') {
            result = '-' + result;
        }
    }
    return BigReal(result,1);
}
BigReal BigReal::operator-(const BigReal & othornumber) {
    pair<string,string >s=find_max_number(integer, fraction, othornumber.integer, othornumber.fraction);
    string tmp= s.first;
    string result;
    if(sign==othornumber.sign)
    {
        result= performArithmeticOperation(integer, fraction, othornumber.integer, othornumber.fraction, '-');
    }
    else
    {
            result = performArithmeticOperation(integer, fraction, othornumber.integer, othornumber.fraction, '+');
            //return BigReal(result);

    }
    if(tmp == integer && sign == '-')
    {
        result='-'+result;
    }
    else if(tmp==othornumber.integer && othornumber.sign == '+')
    {
        result='-'+result;
    }
    return BigReal(result,1);
}
BigReal BigReal::operator=(const BigReal & other) {
    integer=other.integer;
    fraction=other.fraction;
    sign=other.sign;
    return BigReal(sign + integer + '.' + fraction);
}
bool BigReal::operator>(BigReal othornumber) {
    if(sign=='-' && othornumber.sign=='+' )
        return false;
    if(sign=='+' && othornumber.sign=='-' )
        return true;//   5 5
    pair<string,string>tmp=find_max_number(integer, fraction, othornumber.integer, othornumber.fraction);
    if(sign=='+')
    return (tmp==make_pair(integer, fraction) && tmp != make_pair(othornumber.integer, othornumber.fraction));
    if(sign=='-')
        return (tmp!=make_pair(integer, fraction) && tmp != make_pair(othornumber.integer, othornumber.fraction) );
}
bool BigReal::operator<(BigReal othornumber) {

   if(sign=='-' && othornumber.sign=='+' )
       return true;
    if(sign=='+' && othornumber.sign=='-' )
        return false;
   pair<string,string>tmp=find_max_number(integer, fraction, othornumber.integer, othornumber.fraction);
   if(sign=='+')
   return (tmp!=make_pair(integer, fraction) && tmp != make_pair(othornumber.integer, othornumber.fraction));
   else
       return (tmp==make_pair(integer, fraction) && tmp != make_pair(othornumber.integer, othornumber.fraction));
}
bool BigReal::operator==(BigReal othornumber) {
    while (fraction.size() != othornumber.fraction.size()) {
        if (fraction.size() < othornumber.fraction.size()) {
            fraction += '0';
        } else {
            othornumber.fraction+= '0';
        }
    }
    while (integer.size() != othornumber.integer.size()) {
        if (integer.size() < othornumber.integer.size()) {
            integer = '0' + integer;
        } else {
            othornumber.integer = '0' + othornumber.integer;
        }
    }
    return (integer==othornumber.integer&& fraction == othornumber.fraction
            && sign==othornumber.sign);
}
string BigReal::get()const {
    if(sign=='-')
        return('-' + integer+'.'+fraction);
    else return integer+'.'+fraction;
}
void BigReal::set(string num) {
    if(!isvalid(num))
    {
        cout<<"Invaild integer\n";
        return;
    }
    pair<string,string > tmp =divide_number(num);
    sign=tmp.first[0];
    integer=tmp.first.substr(1);
    fraction=tmp.second;
}
int BigReal::Sign() {
    if(integer == "0" && fraction == "0")
        return 0;
    return (sign=='+' ? 1:-1);
}
ostream& operator<<(ostream& out, const BigReal& num) {
    if(num.integer == "0" && num.fraction == "0")
    {
        out<<"0.0";
        return out;
    }
    if(num.sign=='-')out<<'-';
    out<<num.integer;
    if(!num.fraction.empty())
        out<<'.'<<num.fraction;

    return out;
}

// This coded by me.
