#include <iostream>
#include <string>
#include <list>

template <typename T, typename L>
std::ostream & operator<<(std::ostream & cout, const std::pair<T, L> & l)
{
    cout << "(" << l.first << ", " << l.second << ")";
    return cout;
}

template <typename T>
std::ostream & operator<<(std::ostream & cout, const std::list<T> & l)
{
    std::string delim = "";
    cout << "[";
    for (auto p: l)
    {
        cout << delim << p;
        delim = ", ";
    }
    cout << "]";
    return cout;
}

void longest_common_substring(std::string & text1, std::string & text2)
{
    // return (text1[0]==text2[0])
    // else
    // if (text1[i]==text2[j])
    //    0
    // else
    //    1 + (l_c_s(i-1, j-1))
    int t[text1.size()][text2.size()];
    t[0][0] = (text1[0]==text2[0]);

    int max_row = 0;
    int max_col = 0;
    std::list< std::pair<int,int> > max_string;
    
    for (int i = 1; i < text1.size(); ++i)
    {
        t[i][0] = (text1[i]==text2[0]);
    }
    
    for (int i = 1; i < text2.size(); ++i)
    {
        t[0][i] = (text1[0]==text2[i]);
    }

    for (int i = 1; i < text1.size(); ++i)
    {
        for (int j = 1; j < text2.size(); ++j)
        {
            t[i][j] = (text1[i]==text2[j]) * ((t[i-1][j-1]) + 1);
            std::pair<int, int> x(i-t[i][j]+1, j-t[i][j]+1);
            if (t[max_row][max_col] < t[i][j])
            {
                max_row = i;
                max_col = j;
                max_string.clear();
                
                max_string.push_back(x);
            }
            else if (t[max_row][max_col] == t[i][j])
            {
                max_string.push_back(x);
            }
        }
    }

    int max = t[max_row][max_col];
    for (auto p: max_string)
    {
        int i = p.first;
        int j = p.second;
        std::cout << i << ' ' << j << ' ' << max
                  << ' ' << text1.substr(i, max) << std::endl;
    }
    
}

int main()
{
    std::string text1;
    std::string text2;
    std::cin >> text1;
    std::cin >> text2;

    longest_common_substring(text1, text2);
    return 0;
}
