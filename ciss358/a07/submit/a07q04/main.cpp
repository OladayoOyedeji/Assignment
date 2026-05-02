#include <iostream>
#include <climits>
#include <vector>
#include <list>
#include <string>

using namespace std;
typedef vector< vector<int> > two_arr;

enum {COPY, REPLACE, DELETE, INSERT, TWIDDLE, KILL};

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
    std::string delim = "";
    cout << "{";
    for (int i = 0; i < v.size(); i++)
    {
        std::cout << delim << v[i];
        delim = ", ";
    }
    cout << "}\n";
    return cout;
}

void find_path(const two_arr & t, vector<list<int> > & v, list<int> & lst,
               const string & x, const string & y, int cost[], int i, int j)
{
    if (j == 0 && i == 0)
    {
        if (x[0] == y[0])
            lst.push_back(COPY);
        else
            lst.push_back(REPLACE);
        lst.reverse();
        v.push_back(lst);
    }
    else if (i >= 0 || j >= 0)
    {
        if (i - 1 >= 0 &&  t[i-1][j] == t[i][j]-cost[DELETE])
        {
            list<int> lst0 = lst;
            lst0.push_back(DELETE);
            find_path(t, v, lst0, x, y, cost, i-1, j);
        }
        
        if (j-1 >= 0 && t[i][j-1] == t[i][j]-cost[INSERT])
        {
            list<int> lst0 = lst;
            lst0.push_back(INSERT);
            find_path(t, v, lst0, x, y, cost, i, j-1);
        }

        if (i-2 >= 0 && j-2 >= 0 && t[i-2][j-2] == t[i][j]-cost[TWIDDLE])
        {
            list<int> lst0 = lst;
            lst0.push_back(TWIDDLE);
            find_path(t, v, lst0, x, y, cost, i-2, j-2);
        }
        
        int c_r = (x[i] == y[j] ? COPY : REPLACE);
        if (i-1 >= 0 && j-1 >= 0 && t[i-1][j-1] == t[i][j]-cost[c_r])
        {   
            list<int> lst0 = lst;
            lst0.push_back(c_r);
            find_path(t, v, lst0, x, y, cost, i-1, j-1);
        }
    }
}

void edit_distance(const string & x, const string & y, int cost[])
{
    two_arr table(x.size(), vector<int>(y.size()));
    table[0][0] = (x[0]==y[0] ? cost[COPY] : cost[REPLACE]);

    for (int i = 0; i < x.size(); ++i)
    {
        for (int j = 0; j < y.size(); ++j)
        {
            if (i != 0 || j != 0)
            {
                int D1 = INT_MAX;
                int D2 = INT_MAX;
                int D3 = INT_MAX;
                int D4 = INT_MAX;

                //===================
                // D1
                //===================
                if (i-2>=0 && j-2>=0)
                {
                    if (x[i-1] == y[j] && x[i] == y[j-1])
                    {
                        D1 = table[i-2][j-2] + cost[TWIDDLE];
                    }
                }

                //===================
                // D2
                //===================
                if (i-1>=0 && j-1>=0)
                {
                    D2 = table[i-1][j-1]+ (x[i] == y[j] ? cost[COPY] : cost[REPLACE]);
                }
                
                //===================
                // D3
                //===================
                if (j-1>=0)
                {
                    D3 = table[i][j-1] + cost[INSERT];
                }
                
                //===================
                // D4
                //===================
                if (i-1>=0)
                {
                    D4 = table[i-1][j]+cost[DELETE];
                }
                
                table[i][j] = min<int>(min<int>(D1, D2), min<int>(D3, D4));
            }
        }
    }

    vector<list<int> > v;
    list<int> lst;
    lst.push_back(KILL);
    list<int> min_list;
    double min = INT_MAX;
    
    for (int i = 0; i < x.size(); ++i)
    {
        cout << table[i][y.size()-1] << " " << i << endl;
        if (table[i][y.size()-1] < min)
        {
            min = table[i][y.size()-1];
            min_list = list<int>();
            min_list.push_back(i);
        }
        else if (table[i][y.size()-1] == min)
        {
            min_list.push_back(i);
        }
    }

    for (auto p: min_list)
    {
        find_path(table, v, lst, x, y, cost, p, y.size()-1);
    }
    cout << min << endl;

    // cout << v << endl;
    // cout << min_list << endl;

    // for (int i = 0; i < )

    for (int l = 0; l < v.size(); ++l)
    {
        cout << "initial strings  >" << x << endl;
        int i = 0;
        int j = 0;
        for (auto p: v[l])
        {
            
            switch (p)
            {
                case COPY:
                    i++; j++;
                    cout << "copy             ";
                    break;
                case REPLACE:
                    cout << "replace by " << y[j] << "     ";
                    i++; j++;
                    break;
                case DELETE:
                    cout << "delete       ";
                    i++;
                    break;
                case INSERT:
                    cout << "insert " << y[j] << "         ";
                    j++;
                    break;
                case TWIDDLE:
                    cout << "twiddle      ";
                    j++;j++;i++;i++;
                    break;
                case KILL:
                    cout << "kill             ";
                    i = x.size();
            }
            for (int k = 0; k < x.size(); ++k)
            {
                if (k == i)
                {
                    cout << ">";
                }
                cout << x[k];
            }
            if (i == x.size())
            {
                cout << '>';
            }
            cout << "      ";
            for (int k = 0; k < j; ++k)
            {
                cout << y[k];
            }
            cout << endl;
        }
    }
    
    // cout << table << endl;
}
    
int main()
{
    string x, y;

    std::cin >> x >> y;

    int cost[6];
    for (int i = 0; i < 6; ++i)
    {
        std::cin >> cost[i];
    }

    edit_distance(x, y, cost);
    
    return 0;
}
