#include <iostream>
#include <algorithm>

using namespace std;

int MajorityElement(int x[], int start, int end)
{
    int n = x[start];
    int s = 1;
    for (int i = start; i < end; ++i)
    {
        if (s <= 0)
            n = x[i];
        s += (x[i] == n? 1: -1);
    }
    return (s > 1 ? n : 0);
}

int count(int * start, int * end, int target)
{
    int count = 0;
    for (int * i = start; i < end; ++i)
    {
        if (*i == target)
        {
            count++;
        }
    }
    return count;
}

int MajorityElementDAC(int * start, int * end)
{
    if (start >= end-1)
    {
        return *start;
    }
    else
    {
        int * mid = start + (end - start) / 2;
        int n = (end-start)/2;
        
        int l = MajorityElementDAC(start, mid);
        int r = MajorityElementDAC(mid,   end);

        int counta = count(start, end, l);
        int countb = count(start,   end, r);
       
        if (counta < n && countb < n) return 0;
        
        return (counta > countb ? l: r);
    }
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

    cout << MajorityElementDAC(x, x+n) << endl;
    cout << MajorityElement(x, 0, n) << endl;
    
    return 0;
}
