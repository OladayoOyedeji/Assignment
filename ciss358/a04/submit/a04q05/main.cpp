#include <iostream>

using namespace std;

int Max(int * start, int * end);
int Min(int * start, int * end);

int N_crossings(int * start, int * end)
{
    int * mid = start + (end - start)/ 2;
    int max = Max(start, mid);
    int min = Min(mid, end);
    int cross = 0;
    cout << *start << ' ' << *(mid-1) << ' '<< *(end-1) << endl;
    for (int * i = mid-1; i >= start; --i)
    {
        if (*i > min && *i != max)
        {
            cross++;
        }
    }

    for (int * i = mid; i < end; ++i)
    {
        if (*i < max && *i != min)
        {
            cross++;
        }
    }
    cout <<"minmax: " << min << ' ' << max << endl;
    return cross + (min < max ? 1: 0);
}

int Inversions(int * start, int * end)
{
    if (start >= end-1)
    {return 0;}
    else if (end - start == 2)
    {
        return (*start > *(start+1) ? 1 : 0);
    }
    int * mid = start + (end - start)/ 2;
    return N_crossings(start, end) +  Inversions(start, mid) + Inversions(mid, end);
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

    cout << Inversions(x, x+n) << endl;
    
    return 0;
}


int Max(int * start, int * end)
{
    int max = *start;
    for (int * i = start + 1; i < end; ++i)
    {
        if (*i > max)
            max = *i;
    }
    return max;
}

int Min(int * start, int * end)
{
    int min = *start;
    for (int * i = start + 1; i < end; ++i)
    {
        if (*i < min)
            min  = *i;
    }
    return min;
}
