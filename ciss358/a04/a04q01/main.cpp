#include <iostream>

using namespace std;

void MaximumSubArray     (int x[], int start, int end);
void MaximumSubArrayDAC  (int x[], int start, int end);
int  MaximumMidArrayDAC  (int x[], int start, int end, int &l, int &r);
int  MaximumSubArrayDAC_r(int x[], int start, int end, int &l, int &r);

int main()
{
    int mode;
    cin >> mode;
    
    int n;
    cin >> n;

    const int size = n;

    int x[size];

    for (int i = 0; i < size; ++i)
    {
        cin >> x[i];
    }

    if (mode)
    {
        MaximumSubArrayDAC(x, 0, size);
    }
    else
    {
        MaximumSubArray(x, 0, size);
    }
    
    return 0;
}

void MaximumSubArray(int x[], int start, int end)
{
    int l = start;
    int r = start+1;
    int sum = start;
    int max = sum;
    
    for (int i = start+1; i < end; ++i)
    {
        sum += x[i];
        if (sum > max)
        {
            r = i+1;
            max = sum;
        }

        else if (sum < 0)
        {
            l = i+1;
            sum = 0;
            
        }
    }
    cout << max << ' ' << l << ' ' << r << endl;
}

void MaximumSubArrayDAC(int x[], int start, int end)
{
    int l, r;
    int max = MaximumSubArrayDAC_r(x, start, end, l, r);
    cout << max << ' ' << l << ' ' << r << endl;
}

int MaximumSubArrayDAC_r(int x[], int start, int end, int &l, int &r)
{
    l = start;
    r = end;
    if (end <= start)
    {
        return 0;
    }
    else if (start+1 == end)
    {
        return x[start];
    }
    else
    {
        int mid = start + (end - start) / 2;
        int max;
        int a_l, a_r, b_l, b_r, c_l, c_r;
        int a = MaximumSubArrayDAC_r(x, start, mid, a_l, a_r);
        int b = MaximumSubArrayDAC_r(x, mid,   end, b_l, b_r);
        int c = MaximumMidArrayDAC  (x, start, end, c_l, c_r);

        // a > b
        if (a > b)
        {
            // a > b && a > c
            if (a > c)
            {
                l = a_l; r = a_r; max = a;
            }
            // c > a > b
            else
            {
                l = c_l; r = c_r; max = c;
            }
        }
        // b > a
        else
        {
            // b > a and b > c
            if (b > c)
            {
                l = b_l; r = b_r; max = b;
            }
            // c > b > a
            else
            {
                l = c_l; r = c_r; max = c;
            }
        }
        return max;
    }
}

int MaximumMidArrayDAC(int x[], int start, int end, int &l, int &r)
{
    int mid = start + (end - start) / 2;
    l = mid;
    int lmax = x[mid];
    int sum = 0;
    
    for (int i = mid; i >= start; --i)
    {
        sum += x[i];
        if (sum > lmax)
        {
            lmax = sum;
            l = i;
        }
    }

    r = mid+1;
    int rmax = 0;
    sum = 0;
    for (int i = mid + 1; i < end; ++i)
    {
        sum += x[i];
        if (sum > rmax)
        {
            rmax = sum;
            r = i+1;
        }
    }
    
    return lmax + rmax;
}
