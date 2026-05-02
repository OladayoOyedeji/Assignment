#ifndef OPERATOR_H
#define OPERATOR_H

#include <iostream>
#include <stack>
#include <vector>
#include <limits>

class Error
{};

class Op
{
public:
    Op(char c)
        : oper(c), precedence(0)
    {
        switch (c)
        {
            case '+':
            case '-':
                precedence = 1;
                break;
            case '*':
            case '/':
            case '%':
                precedence = 2;
                break;
            case '(':
            case ')':
                precedence = 0;
                break;
        }
    }
    Op(const Op & op)
        : precedence(op.pred()), oper(op.c())
    {}
    // Op(const string & s)
    // {
        
    // }
    int pred() const
    {
        return precedence;
    }
    char c() const
    {
        return oper;
    }
private:
    int precedence;
    char oper;
};

std::ostream & operator<<(std::ostream & cout, const Op & op)
{
    cout << "<" << op.c() << ',' << op.pred() << '>';
    return cout;
}
int eval(int a, int b, const Op & op_)
{
    switch(op_.c())
    {
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '/':
            return a / b;
        case '*':
            return a * b;
        case '%':
            return a % b;
    }
    return -9999;
}
#endif
