#include "Mat.h"

int main()
{
    float x[] = {1, 0, 0,
        -3, 1, 0,
        4, -1,1};
    float y[] = {2, -1, 2,
        0, -3, 4,
        0, 0, 1};

    Mat<float> m1(3, 3, x);
    Mat<float> m2(3, 3, y);
    std::cout << m1 * m2 << std::endl;
    // Mat< float > m(2, 2, y);

    // float c = det(m);
    // std::cout << "determinant: " << c << std::endl;

    // Mat<float> n(3, 3, x);
    
    // float d = det(n);
    // std::cout << "determinant: " << d << std::endl;
    
    return 0;
}
