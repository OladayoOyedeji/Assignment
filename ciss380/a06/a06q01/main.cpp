#include <iostream>
#include "Mat.h"

int main()
{
    Mat<int> m(2, 2);

    float p[] = {1.333, 2, 44.99, 12.22,
        900.3, 22, 12.11, 4,
        5, 2.3, 33.33, 92.22,
        44.33, 34.44, 22.33, 56.33};
    Mat<float>m1(4, 4, p);

    std::cout << m << '\n' << m1 << std::endl;
    
    return 0;
}
