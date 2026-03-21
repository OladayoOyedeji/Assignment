#include <iostream>
#include <list>
#include <vector>
#include <string>

using namespace std;

typedef vector< vector<int> > TwoArr;
typedef vector< vector<list<list<int>>> > TwoArrl;

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

// void find_path(const TwoArr & table, int i, int j)
// {
    
// }

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

void longest_palindrome_subsequence(string s)
{
    TwoArr table(s.size(), vector<int>(s.size(), -1));

    TwoArrl subsequence(s.size(), vector<list<list<int>>>(s.size()));
    for (int i = 0; i < s.size(); ++i)
    {
        table[i][i] = 1;
        list<int> lst;
        lst.push_back(i);
        subsequence[i][i].push_back(lst);
    }
    for (int i = 1; i < s.size(); ++i)
    {
        for (int j = 0; j < s.size() - i; ++j)
        {
            int k = j + i;
            int max_ = table[k-1][j+1] + 2 *(s[k]==s[j]);
            // table[k][j] = max(table[k][j+1], table[k-1][j]);
            // table[k][j] = max(max_, table[k][j]);
            // if (max_ == table[k][j])
            // {
            //     subsequence[k][j] = subsequence[k-1][j+1];
            //     for ()
            // }

            if (max_ > table[k][j+1])
            {
                if (max_ > table[k-1][j])
                {
                    subsequence[k][j] = subsequence[k-1][j+1];
                    if (s[k]==s[j])
                    {
                        for (auto & p: subsequence[k][j])
                        {
                            p.push_back(k);
                            p.push_front(j);
                        }
                    }
                    table[k][j] = max_;
                }
                else
                {
                    subsequence[k][j] = subsequence[k-1][j];
                    table[k][j] = table[k-1][j];
                }
            }
            else
            {
                if (table[k][j+1] > table[k-1][j])
                {
                    subsequence[k][j] = subsequence[k][j+1];
                    table[k][j] = table[k][j+1];
                }
                else
                {
                    subsequence[k][j] = subsequence[k-1][j];
                    table[k][j] = table[k-1][j];
                }
            }

        }
    }
    // find_path(table, i, j);
    for (auto p: subsequence[s.size()-1][0])
    {
        cout << "(\"";
        for (auto q: p)
        {
            cout << s[q];
        }
        cout << "\", " << p << ")" << endl;
    }
}

int main()
{
    string s;
    cin >> s;

    longest_palindrome_subsequence(s);
    
    return 0;
}
