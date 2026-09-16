#include <iostream>
#include "Set.h"

int main()
{
    Set< int > X;
    X.insert(1);
    std::cout << "|X| = " << X.size() << ", X = " << X << std::endl;
    X.insert(1);
    std::cout << "|X| = " << X.size() << ", X = " << X << std::endl;
    
    X.insert(5);
    std::cout << "|X| = " << X.size() << ", X = " << X << std::endl;
    
    X.insert(0);
    std::cout << "|X| = " << X.size() << ", X = " << X << std::endl;
    
    return 0;
}
