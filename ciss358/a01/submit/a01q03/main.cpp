// File: main.cpp
// Runtime: 0(n)
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

int main()
{
    unordered_map<int, int> two_sum;
    int n;
    int N;
    cin >> n >> N;
    vector<int> arr_(n);
    
    for (int i = 0;i < n; ++i)
    {
        cin >> arr_[i];
        
        int diff = N - arr_[i];
        if (two_sum.find(diff) != two_sum.end())
        {
            cout << two_sum[diff] << ' ' << i << endl;
            break;
        }
        else
        {
            two_sum[arr_[i]] = i;
        }
    }
    
    return 0;
}
