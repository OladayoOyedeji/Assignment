#include <iostream>
#include <algorithm>

using namespace std;

int LongestStrictlyIncreasingMDAC(int * start, int * end)
{
    int * mid = start + (end - start)/2;
    int * l = mid;
    for (int * i = mid-1; i >= start; --i)
    {
        if (*i > *(i+1))
        {
            break;
        }
        l = i;
    }

    int * r = mid;
    for (int * i = mid+1; i < end; ++i)
    {
        if (*i < *(i-1))
        {
            break;
        }
        r = i+1;
    }
    
    return (r-l);
}

int LongestStrictlyIncreasingSDAC(int * start, int * end)
{
    if (start >= end)
    {
        return 0;
    }
    if (end - start == 1)
    {
        return 1;
    }
    int * mid = start + (end-start)/2;
    int l = LongestStrictlyIncreasingSDAC(start, mid);
    int r = LongestStrictlyIncreasingSDAC(mid,   end);

    int m = LongestStrictlyIncreasingMDAC(start, end);

    return max(max(l,r),m);
}

int main()
{
    int n;
    cin >> n;

    const int size = n;

    int x[size];

    for (int i = 0; i < n; ++i)
    {
        cin >> x[i];
    }

    cout << LongestStrictlyIncreasingSDAC(x, x+n) << endl;
    
    return 0;
}
