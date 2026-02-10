// File: main.cpp
// Runtime: 0(lgn)

#include <iostream>
#include <vector>

using namespace std;

int median_of_three(vector<int> & arr, int start, int end)
{
    int mid = start + (end - start)/2;
    if (arr[start] > arr[end])
    {
        // start > end > mid
        if (arr[end] > arr[mid])
        {
            return end;
        }
        // start > mid > end or mid > start > end
        return (arr[start] > arr[end] ? mid : start);
    }
    // end > start
    // start > mid
    if (arr[start] > arr[mid])
    {
        return start;
    }
    // end > mid > start or mid > end > start
    return (arr[end] > arr[start] ? mid : end);
}

int pLRT(vector<int> & arr, int pivot, int start, int end)
{
    // swap start and pivot
    swap(arr[start], arr[pivot]);
    pivot = start;

    int l = start + 1;
    int r = start + 1;

    while (r < end)
    {
        if (arr[r] <= arr[start])
        {
            if (r-l > 0)
            {
                swap(arr[r], arr[l]);
            }
            l++;
        }
        r++;
    }

    // return
    if (l - (start + 1) > 0)
    {
        swap(arr[start], arr[l-1]);
        return l-1;
    }
    else
        return start;
}

int main()
{
    int n;
    cin >> n;
    vector<int> arr_(n);

    for (int i = 0; i < n; ++i)
    {
        cin >> arr_[i];
    }

    int start = 0, end = arr_.size();
    
    int i = median_of_three(arr_, start, end-1);
    i = pLRT(arr_, i, start, end);
    
    int mid = arr_.size() / 2;
    
    while (i != mid)
    {
        if (i < mid)
        {
            start = i;
        }
        else
        {
            end = i + 1;
        }
        i = median_of_three(arr_, start, end-1);
        i = pLRT(arr_, i, start, end);
    }

    int sum = 0;
    for (int j = 0; j < arr_.size(); ++j)
    {
        sum += abs(arr_[i] - arr_[j]);
    }
    
    std::cout << sum << ' ' << arr_[i] << std::endl;
    
    return 0;
}
