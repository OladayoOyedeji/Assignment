#include "Complex.h"

void test_addeq()
{
    complex no1, no2;
    std::cin >> no1 >> no2;

    std::cout << "adding: " << no1 << " += " << no2 << std::endl;

    std::cout << (no1 += no2) << std::endl;
}
void test_subtracteq()
{
    complex no1, no2;
    std::cin >> no1 >> no2;

    std::cout << "subtracting: " << no1 << " -= " << no2 << std::endl;

    std::cout << (no1 -= no2) << std::endl;
}
void test_multeq()
{
    complex no1, no2;
    std::cin >> no1 >> no2;

    std::cout << "multiplying: " << no1 << " *= " << no2 << std::endl;

    std::cout << (no1 *= no2) << std::endl;
}
void test_diveq()
{
    complex no1, no2;
    std::cin >> no1 >> no2;

    std::cout << "dividing: " << no1 << " /= " << no2 << std::endl;

    std::cout << (no1 /= no2) << std::endl;
}
void test_add()
{
    complex no1, no2;
    std::cin >> no1 >> no2;

    std::cout << "adding: " << no1 << " + " << no2 << std::endl;

    std::cout << no1 + no2 << std::endl;
}
void test_subtract()
{
    complex no1, no2;
    std::cin >> no1 >> no2;

    std::cout << "subtracting: " << no1 << " - " << no2 << std::endl;

    std::cout << no1 - no2 << std::endl;
}
void test_mult()
{
    complex no1, no2;
    std::cin >> no1 >> no2;

    std::cout << "multiplying: " << no1 << " * " << no2 << std::endl;

    std::cout << no1 * no2 << std::endl;
}
void test_div()
{
    complex no1, no2;
    std::cin >> no1 >> no2;

    std::cout << "dividing: " << no1 << " / " << no2 << std::endl;

    std::cout << no1 / no2 << std::endl;
}
void test_abs()
{
    complex no;
    std::cin >> no;

    std::cout << "absolute: |" << no << "|\n";

    std::cout << no.abs() << std::endl;
}


int main()
{
    while (1)
    {
        int input;
        std::cin >> input;
    
        switch (input)
        {
            case 0:
                test_addeq();
                break;
            case 1:
                test_subtracteq();
                break;
            case 2:
                test_multeq();
                break;
            case 3:
                test_diveq();
                break;
            case 4:
                test_add();
                break;
            case 5:
                test_subtract();
                break;
            case 6:
                test_mult();
                break;
            case 7:
                test_div();
                break;
            case 8:
                test_abs();
                break;
        }
    }
    
    return 0;
}
