#include <iostream>
#include <iomanip>
#include <vector>
#include <list>
#include <string>

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

void find_path(std::vector< std::vector<int> > & t,
               int n, int i, std::list<int> & l,
               std::vector<int> & P)
{
    if (i < 0 || n <= 0)
    {
        return;
    }
    else
    {
        if (t[n][i-1] == t[n][i])
            find_path(t, n, i-1, l, P);
        if (t[n-i][i]+P[i] == t[n][i])
        {
            find_path(t, n-i, i, l, P);
            l.push_back(i);
        }
    }
}
int maximum_cost(int n, std::vector<int> & P)
{
    std::vector< std::vector<int> > t(n+1, std::vector< int >(P.size(), 0));
    std::cout << t.size() << ' ' << t[0].size() << std::endl;
    std::list<int> l;
    
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j < P.size(); ++j)
        {
           if ((i-j) < 0)
                t[i][j] = t[i][j-1];
            else
                t[i][j] = std::max<int>(t[i][j-1], t[i-j][j]+P[j]);
        }
    }

    
    for (int i = 0; i <= n; ++i)
    {
        std::string delim = "|";
        std::cout << i;
        for (int j = 0; j < P.size(); ++j)
        {
            std::cout << std::setw(3) << delim << t[i][j];
            delim = "|";
        }
        std::cout << "|\n";
    }
    find_path(t, n, P.size()-1, l, P);
    std::cout << l << std::endl;
    return t[n][P.size()-1];
}
int M(int n, std::vector<int> & P)
{
    if (n <= 0)
        return 0;
    else
    {
        int i = 1;
        int max = 0;
        while (n-i >= 0)
        {
            if (i < P.size() && P[i] != 0 && (M(n-i, P) + P[i] > max))
            {
                max = M(n-i, P) + P[i];
            }
            i++;
        }
        return max;
    }
}

int main()
{
    std::vector<int> C;
    int input;
    std::cin >> input;
    
    C.push_back(0);
    
    while (input != -1)
    {
        C.push_back(input);
        std::cin >> input;
    }

    std::string delim = "";
    std::cout << "{";
    for (int i = 0; i < C.size(); ++i)
    {
        std::cout << delim << C[i];
        delim = ", ";
    }
    std::cout << "}\n";
    
    int n;
    std::cin >> n;
    std::cout << "M: " <<  M(n,C) << std::endl;
    std::cout << maximum_cost(n,C) << std::endl;
}
