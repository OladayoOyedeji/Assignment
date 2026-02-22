#include "Mat.h"

int main()
{
    float x[] = {13, 16,
        29, 36};
    Mat< float > m(2, 2, x);

    Mat<float> M_1 = m.inv();

    std::cout << M_1 << std::endl;
    
    return 0;
}
