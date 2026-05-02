#include <stack>
#include <vector>
#include <string>
#include <limits>
#include <cerrno>
#include <iostream>
#include <unordered_map>
#include "Operator.h"

using namespace std;
const int MAX_BUF = 1024;
typedef vector<string> Token;
typedef unordered_map<string, int> SymTable;

template <typename T>
std::ostream & operator<<(std::ostream & cout, const vector<T> & v)
{
    string delim = "";
    cout << "[";
    for (int i = 0; i < v.size(); i++)
    {
        cout << '[' << delim << v[i] << ']';
    }
    cout << "]";
    return cout;
}

template <typename T>
std::ostream & operator<<(std::ostream & cout, const stack<T> & s)
{
    string delim = "";
    cout << '{';
    stack<T> s_ = s;
    while (!s_.empty())
    {
        T p = s_.top();
        s_.pop();
        cout << delim << p;
        delim = ", ";
    }
    cout << '}';
    return cout;
}

int pow_of_10(int n)
{
    int prod = 1;
    for (int i = 0; i < n; ++i)
    {
        prod *= 10;
    }
    return prod;
}

void lex(const string & s, Token & token)
{
    int i = 0;
    int j = 0;

    // state: 0->numbers and variables, 1->symbols, 2->space
    int state = 0;
    while (j < s.size())
    {
        if (state == 0)
        {
            if (s[j] == ' ' || s[j] == '+' || s[j] == '-' ||
                s[j] == '=' || s[j] == '*' || s[j] == '/')
            {
                if (s[j] == ' ')
                {
                    state = 2;
                }
                else
                {
                    state = 1;
                }
                if (j-i > 0)
                    token.push_back(s.substr(i, j-i));
                i = j;
            }
            
        }
        else if (state == 1)
        {
            if (s[j] != '+' && s[j] != '-')
            {
                if (s[j] == ' ')
                {
                    state = 2;
                }
                else
                {
                    state = 0;
                }
                if (j-i > 0)
                    token.push_back(s.substr(i, j-i));
                i = j;
            }
            else if (s[j] == '=' || s[j] == '*' || s[j] == '/')
            {
                token.push_back(s.substr(i, j-i));
                token.push_back(s.substr(j, 1));
                i = j+1;
            }
        }
        else if (state == 2)
        {
            i++;
            if (s[j] != ' ')
            {
                if (s[j] == '+' || s[j] == '-' ||
                    s[j] == '=' || s[j] == '*' ||
                    s[j] == '/')
                {
                    state = 1;
                }
                else
                {
                    state = 0;
                }
            }
        }
        ++j;
    }
    if (j-i > 0 && s.substr(i, j-i) != " ")
        token.push_back(s.substr(i, j-i));
}

int get_variable(const string & tok, const SymTable & symtable)
{
    // if (symtable.find(tok) == symtable.end())
    // {
    //     throw std::runtime_error("not a variable");
    // }
    // else
    // {
    //     return symtable[tok];
    // }
    return -1;
}

int get_numerics(const string & str)
{
    int j = 0;
    int n = 0;
    for (int i = str.size() - 1; i >= 0; --i)
    {
        if (str[j] < '0' || str[j] > '9') throw std::runtime_error("not a number");
        n += pow_of_10(i) * (str[j++] - '0');
    }
    return n;
}

bool is_valid_var(const string & str)
{
    return ((str[0] < '0' || str[0] > '9') &&
            str[0] != '+' && str[0] != '-' &&
            str[0] != '=' && str[0] != '*' && str[0] != '/'); 
}

int is_equation(const Token & tok)
{
    for (int i = 0; i < tok.size(); ++i)
    {
        if (tok[i] == "=")
            return i;
    }
    return -1;
}

char get_sign(const string & s)
{
    int sign = 1;
    for(int i = 0; i < s.size(); ++i)
    {
        if (s[i] == '-')
        {
            sign *= -1;
        }
        
    }
    return (sign == 1 ? '+' : '-');
}

int sign_(char c)
{
    return (c == '-' ? -1: 1);
}

int evaluate(const Token & tok, SymTable & symtable)
{
    Token token;
    int sign = 1;
    int state = 1;
    //state: 1 sign infront of number, 0 sign behind a number
    stack<int> int_stack;
    stack<Op> op_stack;
    
    for (int i = 0; i < tok.size(); ++i)
    {
        if (state == 1)
        {
            int n;
            if (is_valid_var(tok[i]))
            {
                if (symtable.find(tok[i]) == symtable.end())
                {
                    throw std::runtime_error("not a variable name");
                }
                n = sign * symtable[tok[i]];
            }
            else
            {
                try
                {
                    n = sign * get_numerics(tok[i]);
                    
                    if (n < 0)
                    {
                        token.push_back("-" + tok[i]);
                    }
                    else
                        token.push_back(tok[i]);
                    int_stack.push(n);
                    state = 0;
                }
                catch (std::runtime_error & e)
                {
                    if (tok[i] == "*" || tok[i] == "/")
                        throw std::runtime_error("what nih?");
                    sign *= sign_(get_sign(tok[i]));
                }
            }
        }
        else if (state == 0)
        {
            string s;
            if (tok[i] == "*" || tok[i] == "/")
                s = tok[i];
            else
            {
                s = string(1, get_sign(tok[i]));
            }
            token.push_back(s);
            Op op(s[0]);
            if (!(op_stack.empty()) && op.pred() <= op_stack.top().pred())
            {
                int a = int_stack.top();
                int_stack.pop();
                while (!op_stack.empty() && op.pred() <= op_stack.top().pred())
                {
                    if (int_stack.empty())
                        throw std::runtime_error("ERROR NIH!!!!");
                    
                    int b = int_stack.top(); int_stack.pop();
                    Op p = op_stack.top();
                    op_stack.pop();
                    a = eval(b, a, p);
                }
                int_stack.push(a);
            }
            op_stack.push(op);
            sign = 1;
            state = 1;
        }
    }
    if (int_stack.empty())
    {
        throw Error();
    }
    int a;
    if (op_stack.empty())
    {
        a = int_stack.top();
    }
    else
    {
        a = int_stack.top();
        int_stack.pop();
        while (!op_stack.empty())
        {
            int b = int_stack.top();
            int_stack.pop();
            a = eval(b, a, op_stack.top());
            op_stack.pop();
        }
    }
    
    return a;
}

void run(const Token & tok, SymTable & symtable)
{
    if (tok.size() == 1)
    {
        if (is_valid_var(tok[0]))
        {
            if (symtable.find(tok[0]) == symtable.end())
            {
                cout << "\"" << tok[0]
                     << "\" is neither a value nor found in the symtable\n";
            }
            else
                cout << symtable[tok[0]] << endl;
        }
        else
        {
            cout << get_numerics(tok[0]) << endl;
        }
    }
    else
    {
        int is_Eq = is_equation(tok);
        if (is_Eq == -1)
        {
            cout << evaluate(tok, symtable) << endl;
        }
        else if (is_Eq = 1)
        {
            if (is_valid_var(tok[0]))
            {
                symtable[tok[0]] = evaluate(Token(tok.begin() + 1, tok.end()), symtable);
            }
            else
            {
                cout << "not a variable name\n";
            }
        }
        else
            throw std::runtime_error("not a variable name");
    }
}

int main()
{
    SymTable symtable;
    while (1)
    {
        char s[MAX_BUF];
        cout << ">>>";
        cin.getline(s, MAX_BUF);
        if (cin.eof()) break;
        if (cin.fail() || cin.bad())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cout << '[' << s << "]\n";

        Token tok;
        
        lex(s, tok);
        run(tok, symtable);
        if (tok.size() == 0)
            continue;
        cout << tok << endl;
        
    }
    
    return 0;
}
