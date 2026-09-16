#include <iostream>
#include <vector>

using namespace std;


bool check(vector<int> & x, int d, vector<int> & delta)
{
    for (int i = 0; i < x.size(); ++i)
    {
        for (int j = i + 1; j < x.size(); ++j)
        {
            if (delta.find(abs(x[i] - x[j]) == delta.end()))
            {
                return false;
            }
        }
    }

    return true;
}


void X(vector<int> & X, vector<int> & Delta)
{
    for (int i = Delta.size() - 1; i >= 0; i++)
    {
        if (check(X, Delta[i], Delta))
            X.push_back();
    }
}

int main()
{
    vector<int> Delta;
    int input;
    cin >> input;
    while (input != -1)
    {
        Delta.push_back(input);
        cin >> input;
    }

    vector<int> X(0, 0);

    X.push_back(max(Delta));
    
    return 0;
}
