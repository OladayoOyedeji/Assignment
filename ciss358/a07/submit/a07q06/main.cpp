#include <iostream>
#include <cmath>
#include <vector>
#include <climits>
#include <list>

using namespace std;

class Point
{
public:
    double dist(const Point & p)
    {
        return sqrt((x-p.x) *(x-p.x) + (y-p.y) * (y-p.y));
    }
    double x, y;
};

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

// double MinTriangulationCost_memoization(int i, int j)
// {
//     vector< vector<int> > table(n, vector<int>(n, 0));
//     if (j <= i+1)
//     {
//         return 0;
//     }
//     else
//     {
//         int min = INT_MAX;
//         for (int k = i+1; k < j; ++k)
//         {
//             if (table[i][k] == -1)
//             {
//                 table[i][k] = MinTriangulationCost_memoization(i, k);
//             }
//             if (table[k][j] == -1)
//             {
//                 table[i][k] = MinTriangulationCost_memoization(k, j);
//             }
            
//             int cst = table[i][k] + table[k][j] + cost[j] - cost[i];
//             if (min > cst)
//             {
//                 min = cst;
//             }
//         }
//         return min;
//     }
// }

double MinTriangulationCost_BU(const vector<double> & values)
{
    int n = values.size();
    vector< vector<double> > table(n, vector<double>(n, 0));
        
    for (int i = n-1; i >= 0; --i)
    {
        for (int j = i+2; j < n; ++j)
        {
            double min = INT_MAX;
            for (int k = i+1; k < j; ++k)
            {
                 double x = table[i][k] + table[k][j] + (values[j] - values[i]);
                if (x < min)
                {
                    min = x;
                }
            }
            table[i][j] = min;
        }   
    }
    cout << table << endl;
    return table[0][n-1];
}

int main()
{
    int n;
    cin >> n;
    vector<Point> p(n);
    for (int i = 0; i < n; ++i)
    {
        double x, y;
        cin >> x >> y;
        p[i].x = x;
        p[i].y = y;
    }

    vector<double> values(1, 0);

    double sum = 0;
    for (int i = 0; i < n-1; ++i)
    {
        double dist = p[i].dist(p[i+1]) + sum;
        values.push_back(dist);
        sum = dist;
    }

    cout << values << endl;
    cout << MinTriangulationCost_BU(values) << endl;
    
    return 0;
}
