#include "Mat.h"

int main()
{
    float x[] = {1, 2, 3, 4};
    Mat< float > m(1, 4, x);
    std::cout << 1.23f * m << std::endl;
    std::cout << m * 1.23f << std::endl;
    
    return 0;
}
