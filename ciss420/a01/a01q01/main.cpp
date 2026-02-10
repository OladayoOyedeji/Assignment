//======================================================//
// File: main.cpp                                       //
// Class: Computer Architecture(CISS 420)               //
// Women Type: whatever itadori says and what yuta says //
//======================================================//
#include <iostream>

using namespace std;

void shift_right(string & bits, int n)
{
    // basically shifting by resize() then x[i] = x[i - n];
    for (int i = bits.size() - n; i >= 0; --i)
    {
        bits[i +  n] = bits[i];
    }

    // put zeros from 0 - n
    for (int i = 0; i < n; ++i)
    {
        bits[i] = '0';
    }
}

void negate_bits(string & bits)
{
    for (int i = 0; i < bits.size(); ++i)
    {
        if (bits[i] == '1')
        {
            bits[i] = '0';
        }
        else
            bits[i] = '1';
    }
}

void add_one(string & bits)
{
    int count = 1;
    int i = bits.size() - 1;
    while (i >= 0 && count != 0)
    {
        int sum = bits[i] - '0' + count;
        count = sum / 2;
        bits[i] = sum % 2 + '0';
        --i;
    }
}

int main()
{
    int n;
    cin >> n;
    string bits;

    cin >> bits;

    // shift bits
    int shift_length = n - bits.size();
    bits.resize(n);
    shift_right(bits, shift_length);

    // negate bits
    negate_bits(bits);

    // add_one
    add_one(bits);
    cout << bits << endl;
    
    return 0;
}
