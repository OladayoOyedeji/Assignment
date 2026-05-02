#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

struct Point
{
    double x,y;
    
};

double dist(const Point & p1, const Point & p2)
{
    return sqrt((p1.x - p1.x) * (p1.x - p1.x) + (p1.y - p1.y) * (p1.y - p1.y));
}

struct less()
{
    bool operator()(const Point & p1, const Point & p2)
    {
        return (p1.x < p2.x);
    }
};

void merge(const vector<Point> & arr1, const vector<Point> & arr2, vector<Point> & Temp)
{}

// points are already sorted by x cord
int closest_pair_points(vector<Point> & points)
{
    int mid = points.size() / 2;
    sort(points.begin(), points.end(), less());
    // compute points of left
    vector<Point> Left = vector<Point>(points.begin(), points.begin() + points.size() / 2);
    int dL = closest_pair_points(Left);

    // compute points of the Right
    vector<Point> Right = vector<Point>(points.begin() + points.size() / 2, points.end());
    int dR = closest_pair_points(Right);
    int dLR = min(dL, dR);
    
    vector<Point> Py;
    merge(Left, Right, Py);

    int xmid = points[mid].x;

    vector<Point> V;
    for (int i = 0; i < Py.size(); ++i)
    {
        if (abs(Py[i].x - xmid) < dLR)
        {
            V.push_back(Py[i]);
        }
    }

    int v = V.size();
    int d = dLR;

    for (int i = 0; i < v - 1; ++i)
    {
        for (int j = i+1; j < min(i+7, v-1); ++j)
        {
            if (dist(V[i], V[j]) < d)
            {
                d = dist(V[i], V[j]);
            }
        }
    }
    points = Py;
    return d;
}

int main()
{
    return 0;
}
