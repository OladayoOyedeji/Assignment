#include <iostream>

bool walks_slowly(int x[], int n)
{
    if (n <= 1)
    {
        return true;
    }
    else
    {
        return x[n - 1] - x[n - 2] < 2 && walks_slowly(x, n - 1);
    }
}

int main()
{
    int n;
    std::cin >> n;
    int x[n];
    for (int i = 0; i < n; ++i)
    {
        std::cin >> x[i];
    }
    std::cout << walks_slowly(x, n)<< std::endl;
    
    
    return 0;
}
