#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>

const int SIZE = 20;
const char C[] = {'a', 'b', 'c', 'd', 'e'};

//=============================================================================
// Fill 2D array m with characters chosen randomly from C.
//=============================================================================
void randarray(char m[SIZE][SIZE])
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            m[i][j] = C[rand() % 5];
        }
    }
}

//=============================================================================
// Print 2D array.
//=============================================================================
void printarray(char m[SIZE][SIZE])
{
    std::cout << "+--+";
    for (int i = 0; i < SIZE; ++i)
    {
        std::cout << "--+";
    }
    std::cout << "\n|  |";
    for (int i = 0; i < SIZE; ++i)
    {
        std::cout << std::setw(2) << i << "|";
    }
    std::cout << std::endl;
    for (int i = 0; i < SIZE; i++)
    {
        std::cout << "+--+";
        for (int j = 0; j < SIZE; ++j)
        {
            std::cout << "--+";
        }
        std::cout << "\n|" << std::setw(2) << i << '|';
        for (int j = 0; j < SIZE; j++)
        {
            std::cout <<  std::setw(2) << m[i][j] << '|';
        }
        std::cout << '\n';
    }
}

//=============================================================================
// Compute the first (row, col) position such that this is the center of a
// cross of 5 index positions where the characters in array m at these have
// distinct characters. For instance this is a cross
//         d
//        abc
//         e
// of distinct chracters. If the b is at row 5, column 2 then the function
// should set parameter row to 5 and col to 2.
// (Don't forget that we start counting row and column index values at 0.)
//=============================================================================
void f(char m[SIZE][SIZE], int & row, int & col)
{
    for (int r = 1; r < SIZE - 1; r++)
    {
        for (int c = 1; c < SIZE - 1; c++)
        {
            int center = m[r][c];
            int top = m[r-1][c];
            int bottom = m[r+1][c];
            int left = m[r][c+1];
            int right = m[r][c-1];
            if (center != top && center != bottom && center != left && center != right &&
                top != bottom && top != left && top != right &&
                bottom != left && bottom != right &&
                left != right)
            {
                std::cout << r << ' ' << c << std::endl;
                row = r; col = c; return;
            }
        }
    }
    row = col = -1;
    
}

int main()
{
    int seed;
    std::cin >> seed;
    srand(seed);
    
    char m[SIZE][SIZE];
    randarray(m);
    printarray(m);
    
    int row, col;
    f(m, row, col);
    std::cout << row << ' ' << col << std::endl;
    return 0;
}
