#include "Mat.h"

int main()
{
    float x[] = {4, -2,
        -3, 1};
    float y[] = {6, -4,
        -5, 3};
    // Mat< float > m(2, 2, x);
    // Mat< float > n(2, 2, y);
    // std::cout << m << '\n'
    //           << n << std::endl;
    // try
    // {
    //     m += n; // entries of m are incremented by corresponding
    // // entries in n
    //     std::cout << m << std::endl;
    // }
    // catch (SizeError & e)
    // {
    //     std::cout << "Sizes not compatible" << std::endl;
    // }
    
    // Mat< float > p = m + n;

    Mat< float > m(2, 2, x);
    Mat< float > n(2, 2, y);

    std::cout << m << '\n' << n << std::endl;

    float z[] = {1, 2, 3, 4};
    Mat< float > p = m * n; // a 2-by-4 matrix
    std::cout << p << std::endl;
    
    // Mat< float > q(2, 2, z);
    // std::cout << q << std::endl;
    // q *= q; // q becomes q * q
    // std::cout << q << std::endl;
    
    return 0;
}
