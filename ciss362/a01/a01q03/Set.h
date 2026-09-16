// File: Set.h
#ifndef MYSET_H
#define MYSET_H
#include <iostream>
#include <set>

template < class T >
class Set
{
public:
    Set() {}
    
    void insert(const T & x) { set.insert(x); }
    int size() const { return set.size(); }
    
    const typename std::set< T >::iterator begin() const
    {
        return set.begin();
    }
    
    const typename std::set< T >::iterator end() const
    {
        return set.end();
    }
private:
    std::set< T > set;
};

template < class T >
std::ostream & operator<<(std::ostream & cout, const Set< T > & X)
{
    cout << '{';
    if (X.size() > 0)
    {
        typename std::set< T >::iterator p = X.begin();
        cout << (*p);
        typename std::set< T >::iterator end = X.end();
        for (p++; p != end; p++)
        {
            cout << ", " << (*p);
        }

    }
    cout << '}';
    return cout;
}

#endif
