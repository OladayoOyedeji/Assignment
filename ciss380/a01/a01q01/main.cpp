#include <iostream>

void ASCII(int n)
{
    int stars;
    int spaces = n;
    for (int i = 1; i <= n; ++i)
    {
        stars = i;
        for (int j = 0; j < i; ++j)
        {
            for (int star = 0; star < stars; star++)
            {
                std::cout << '*';
            }
            for (int space = 0; space < spaces; space++)
            {
                std::cout << ' ';
            }
            stars--;
        }
        spaces--;
        std::cout << std::endl; 
    }
}

int main()
{
    int n;
    std::cin >> n;

    ASCII(n);
}
