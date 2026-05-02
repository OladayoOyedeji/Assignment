// File: main.cpp
// Runtime: 0(nlgn)
#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<int> arr_(n);
    unordered_map<int, int> arr_index;

    for (int i = 0; i < n; ++i)
    {
        cin >> arr_[i];
        arr_index[arr_[i]] = i;
    }

    sort(arr_.begin(), arr_.end());

    int min_i = arr_index[arr_[0]], min_j = arr_index[arr_[1]];
    int min_diff =abs(arr_[0]-arr_[1]);
    for (int i = 1; i < arr_.size()-1; ++i)
    {
        int diff = abs(arr_[i]-arr_[i+1]);
        if (diff < min_diff)
        {
            min_diff = diff;
            min_i = arr_index[arr_[i]];
            min_j = arr_index[arr_[i+1]];
        }
    }

    cout << min_diff << ' ' << min_i << ' ' << min_j << endl;
    
    return 0;
}
