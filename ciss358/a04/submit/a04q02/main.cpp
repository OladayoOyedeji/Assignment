#include <iostream>
#include <algorithm>

using namespace std;

int MiniminDistanceM(int * start, int * end, int n, int target)
{
    int * mid = start + (end - start) / 2;

    int * l = NULL;
    for (int * i = mid-1; i >= start; --i)
    {
        if (*i == target)
        {
            l = i;
            break;
        }
    }

    int * r = NULL;
    for (int * i = mid; i < end; ++i)
    {
        if (*i == target)
        {
            r = i;
            break;
        }
    }
    
    return (l == NULL || r == NULL ? n: r - l);
}

int MiniminDistanceR(int * start, int * end, int n, int target)
{
    if (start >= end-1)
    {
        return n;
    }
    else
    {
        int * mid = start + (end - start) / 2;
        //cout << start << ' ' << mid << ' ' << (end-1) << endl;
        int mina = MiniminDistanceR(start, mid, n, target);
        int minb = MiniminDistanceR(mid,   end, n, target);
        int minc = MiniminDistanceM(start, end, n, target);
        return min<int>(min<int>(mina, minb), minc);
    }
}

int main()
{
    int n;
    cin >> n;
    int target;
    cin >> target;

    const int size = n;
    int x[size];
    
    for (int i = 0; i < n; ++i)
    {
        cin >> x[i];
    }

    cout <<  MiniminDistanceR(x, x+n, n, target) << endl;
    
    return 0;
}
