#include "Mat.h"

int main()
{
    Mat<float> m(3, 2);

    try
    {
        std::cout << m(3, 2) << std::endl;
    }
    catch (IndexError & e)
    {
        std::cout << "index out of bound" << std::endl;
    }
    
    return 0;
}
