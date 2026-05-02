#include <iostream>

int maximum(int x[], int start, int end)
{
    if (end - start == 1)
    {
        return start;
    }
    if (end - start == 2)
    {
        return (x[start] > x[end-1] ? start : end-1);
    }
    else
    {
        int mid = start + (end - start) / 2;
        int a = maximum(x, start, mid);
        int b = maximum(x, mid, end);

        return (x[a] > x[b] ? a : b);
    }
}

int main()
{
    int n;
    std::cin >> n;
    const int size = n;

    int x[size];
    
    for (int i = 0; i < n; ++i)
    {
        std::cin >> x[i];
    }

    std::cout << maximum(x, 0, n) << std::endl;
    
    return 0;
}
