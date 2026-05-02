// T(n) = 0(n^2)
#include <iostream>
#include <string>
#include <climits>
#include <vector>
#include <list>

using namespace std;

typedef vector< vector<double> > two_arrd;


ostream & operator<<(ostream & cout, const pair<int, int> & p)
{
    cout << '(' << p.first << ", " << p.second << ')';
    return cout;
}

template <typename T>
ostream & operator<<(ostream & cout, const list<T> & l)
{
    string delim = "";
    cout << "(";
    for (auto p: l)
    {
        cout << delim << p;
        delim = ", ";
    }
    cout << ")";
    return cout;
}

template <typename T>
ostream & operator<<(ostream & cout, const vector<T> & v)
{
    string delim = "";
    for (int i = 0; i < v.size(); i++)
    {
        cout << delim << v[i];
        delim = "\n";
    }
    return cout;
}

void find_wide_cut(const two_arrd & table, const two_arrd & Pic,
                   int i, int j,
                   vector<list<pair<int,int> > > & ret,
                   const list<pair<int, int> > & lst)
{
    if (i == table.size()-2)
    {
        ret.push_back(lst);
    }
    else if (j <= 0 || j >= table[0].size() - 1)
    {
        
    }
    else
    {
        // vector v = 
        double diff = table[i][j] - Pic[i][j-1];
        if (diff == table[i+1][j-1])
        {
            list<pair<int,int> > list0 = lst;
            list0.push_back(pair<int,int>(i+1, j-2));
            find_wide_cut(table, Pic, i+1, j-1, ret, list0);
        }
        if (diff == table[i+1][j+1])
        {
            list<pair<int,int> > list0 = lst;
            list0.push_back(pair<int,int>(i+1, j));
            find_wide_cut(table, Pic, i+1, j+1, ret, list0);
        }
        if (diff == table[i+1][j])
        {
            list<pair<int,int> > list0 = lst;
            list0.push_back(pair<int,int>(i+1, j-1));
            find_wide_cut(table, Pic, i+1, j, ret, list0);
        }
            
    }
}

void wide_cut(const two_arrd & Pic, int m, int n)
{
    // initialization
    two_arrd table_lookup(m+1, vector<double>(n+2));
    for (int i = 0; i < m; ++i)
    {
        table_lookup[i][n+1] = INT_MAX;
        table_lookup[i][0] = INT_MAX;
    }
    for (int i = 0; i < n; ++i)
    {
        table_lookup[m][i] = 0;
    }

    // making the table
    for (int i = m-1; i >= 0; --i)
    {
        for (int j = 1; j <= n; ++j)
        {
            double min_ = table_lookup[i+1][j+1];
            min_ = min<double>(min_, table_lookup[i+1][j]);
            min_ = min<double>(min_, table_lookup[i+1][j-1]);
            table_lookup[i][j] = min_ + Pic[i][j-1];
        }
    }

    // get the minimum
    list<int> min_list;
    double min = INT_MAX;
    for (int i = 1; i <= n; ++i)
    {
        if (table_lookup[0][i] < min)
        {
            min = table_lookup[0][i];
            min_list = list<int>(i);
        }
        else if (table_lookup[0][i] == min)
        {
            min_list.push_back(i);
        }
    }
    cout << min << endl;
    vector<list<pair<int,int> > > ret;
    for (auto p: min_list)
    {
        list<pair<int, int> > lst;
        lst.push_back(pair<int, int>(0,p));
        find_wide_cut(table_lookup, Pic, 0, p+1, ret, lst);
    }
    cout<< ret << endl;
}

int main()
{
    int m, n;
    cin >> m >> n;

    two_arrd Pic(m, vector<double>(n));
    
    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < n; ++j)
        {

            cin >> Pic[i][j];
        }
    }
    wide_cut(Pic, m, n);
    
    return 0;
}
