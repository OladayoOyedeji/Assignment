#include <iostream>
#include <cmath>

using namespace std;

bool sorted(int n)
{
    int prev = n % 10;
    n /= 10;
    while (n != 0)
    {
        
        if (n % 10 > prev) return false;
        prev = n % 10;
        n /= 10;
        
    }

    return true;
}

int sizei(int n)
{
    int size = 0;
    if (n == 0) return 1;
    while (n != 0)
    {
        size++;
        n /= 10;
    }
    return size;
}

int index_i(int n, int i)
{
    return int(n / pow(10, i)) % 10;
}

int max_digit(int n)
{
    int i = 0;
    int max_index = 0;
    int max = n % 10;

    while (n != 0)
    {
        if (n % 10 > max)
        {
            max = n % 10;
            max_index = i;
        }
        n /= 10;
        ++i;
    }

    return max_index;
}

int reverse_digit_leftmost(int n, int start, int size)
{
    int new_int = n;
    int end = size - 1;
    for (int i = start; i < size; ++i)
    {
        new_int -= (index_i(n, i)) * pow(10, i);
        new_int += (index_i(n, end--)) * pow(10, i);
    }

    return new_int;
}

int pancake_flip(int n, int start)
{
    int end = n % int(pow(10, start));
    n = n / pow(10, start);
    
    int chunk = max_digit(n);

    n = reverse_digit_leftmost(n, chunk, sizei(n));
    cout << n * pow(10, start) + end << endl;

    n = reverse_digit_leftmost(n, 0, sizei(n));

    return n * pow(10, start) + end;
}

int main()
{
    int n;
    cin >> n;
    cout << n << endl;
    int i = 0;
    while (!sorted(n))
    {
        //cout << "old: " << n << endl;
        n = pancake_flip(n, i++);
        cout << n << endl;
        // int d;
        // cin >> d;
        //cout << max_digit(n) << endl;
    }
    
    return 0;
}
