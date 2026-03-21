#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <stack>

using namespace std;

template <typename T>
std::ostream & operator<<(std::ostream & cout, const std::list<T> & l)
{
    std::string delim = "";
    cout << "[";
    for (auto p: l)
    {
        cout << delim << p;
        delim = ", ";
    }
    cout << "]";
    return cout;
}

template <typename T>
std::ostream & operator<<(std::ostream & cout, const std::stack<T> & s)
{
    std::string delim = "";
    std::stack<T> s_ = s;
    cout << '[';
    while (!s_.empty())
    {
        cout << delim << s_.top();
        s_.pop();
        delim = ", ";
    }
    cout << ']';
    return cout;
}

template <typename T>
std::ostream & operator<<(std::ostream & cout, const std::vector<T> & v)
{
    std::string delim = "";
    cout << "{";
    for (int i = 0; i < v.size(); i++)
    {
        std::cout << delim << i << ":" << v[i];
        delim = ", ";
    }
    cout << "}";
    return cout;
}

class TreeNodev
{
public:
    TreeNodev(char key, TreeNodev * parent = NULL)
        : key_(key), parent_(NULL), child_(26, NULL)
    {
    }
    ~TreeNodev()
    {
        clear_children();
    }
    void clear_children();
    int num_children();
    TreeNodev * insert(char index, char key);
    char key() const
    {
        return key_;
    }
    void insert(const std::string & word);
    void insert(const char * word);
    bool search(const std::string & word) const;
    std::vector<std::string> complete(
        const std::string & word);
    void add(std::vector<std::string> & comp,
                    std::string & s);
private:
    TreeNodev * parent_;
    char key_;
    std::vector<TreeNodev *> child_;
};

#endif
