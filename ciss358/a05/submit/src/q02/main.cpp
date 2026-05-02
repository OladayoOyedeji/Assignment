#include <iostream>

int Max(int x[], int start, int end)
{
    int max = start;
    for (int i = start + 1; i < end; ++i)
    {
        if (x[i] > max)
            max = i;
    }
    return max;
}

int Min(int x[], int start, int end)
{
    int min = start;
    for (int i = start + 1; i < end; ++i)
    {
        if (x[i] < x[min])
            min  = i;
    }
    return min;
}

int max_investment(int x[], int start, int end, int & l, int & r)
{
    // its basically difference between two points
    // divide and conquere
    // T(n) = 2T(n/2) + f(n)
    // f(n) is basically
    // [[        ][       ]]
    //      l         r
    // min(l) min(r)
    // so f(n) is 0(n)
    // T(n) = nlogn
    if (end - start <= 1)
    {
        l = start;
        r = end-1;
        return (x[end-1] - x[start]);
    }
    else
    {
        int mid = start + (end-start)/2;

        int al, ar, bl, br;
        int a = max_investment(x, start, mid, al, ar);
        int b = max_investment(x, mid, end, bl, br);

        l = Min(x, start, mid);
        r = Max(x, mid, end);
        
        int c = x[r] - x[l];
        if (c > a)
        {
            if (c > b)
            {
                return c;
            }
            else
            {
                l = bl;
                r = br;
                return b;
            }
        }
        else
        {
            if (a > b)
            {
                l = al;
                r = ar;
                return a;
            }
            else
            {
                l = bl;
                r = br;
                return b;
            }
        }
    }
}

void max_investmenth(int x[], int n)
{
    int l, r;
    int m = max_investment(x, 0, n, l, r);
    std::cout << m << " ";
    if (m <= 0)
    {
        std::cout << "None" << std::endl;
        return;
    }

    std::cout << x[l] << ' ' << x[r] << std::endl;
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

    max_investmenth(x, n);
    
    return 0;
}
