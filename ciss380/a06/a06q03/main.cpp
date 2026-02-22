#include "Mat.h"

int main()
{
    float p[] = {1.333, 2, 44.99,
        900.3, 22, 12.11,
        5, 2.3, 33.33};
    Mat<float> m(3, 3, p);

    Mat<float> m1(m);
    
    std::cout << m << m1 << '\n'
              << (m1 == m) << ' '
              << (m1 != m) << std::endl;

    m1(2, 1) = 4.3;
    
    std::cout << m << m1 << '\n'
              << (m1 == m) << ' '
              << (m1 != m) << std::endl;

    return 0;
}
