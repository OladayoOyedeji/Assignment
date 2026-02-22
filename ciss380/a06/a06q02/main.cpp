#include "Mat.h"

int main()
{
    float p[] = {1.333, 2, 44.99, 12.22,
        900.3, 22, 12.11, 4,
        5, 2.3, 33.33, 92.22,
        44.33, 34.44, 22.33, 56.33};
    Mat<float>m(4, 4, p);

    Mat<float> copy_of_m(m);

    std::cout << m << copy_of_m << std::endl;
    
    return 0;
}
