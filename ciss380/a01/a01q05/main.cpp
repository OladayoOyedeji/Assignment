#include <iostream>
#include <iomanip>

int calculate_sum(int num[], int n, int initial, int width, int height)
{
    int end = initial + width + height * n;
    int i = initial ;
    int sum = 0;
    std::cout << "end: " << end << std::endl;
    std::cout << "calculating rectangle: " << i
              << " width: " << width << " height: "
              << height << std::endl << std::endl;
    while (i <= end)
    {
        std::cout << "adding: " << i << std::endl;
        sum += num[i++];
        if (i > initial + width)
        {
            i +=  n - width - 1;
            initial = i;
        }
    }
    return sum;
}

void print_arr(int num[], int size, int n)
{
    for (int i = 0; i < size; ++i)
    {
        std::cout << std::setw(4) << num[i] << ' ';
        
        if ((i + 1) % n == 0) std::cout << std::endl;
    }
}

int main()
{
    int n, m;

    std::cin >> n >> m;

    int num[n * m];

    int size = n * m;

    for (int i = 0; i < size; ++i)
    {
        std::cin >> num[i];
    }

    print_arr(num, size, n);
    int max_sum = 0;
    int max_row = 0; int max_col = 0;
    int max_width = 0; int max_height = 0;
    max_sum = num[0];

    for (int i = 0; i < size; ++i)
    {
        int row = i % n;
        int col = i / m;
        for (int j = 0; j < n - row; ++j)
        {
            for (int k = 0; k < m - col; ++k)
            {
                int sum = calculate_sum(num, n, i, j, k);
                if (sum > max_sum)
                {
                    max_sum = sum;;
                    max_row = row;
                    max_col = col;
                    max_width = j;
                    max_height = k;
                }
            }
        }
    }

    std::cout << max_sum << ' ' << max_row << ' '
              << max_col << ' ' << max_width << ' '
              << max_height << std::endl;
}
