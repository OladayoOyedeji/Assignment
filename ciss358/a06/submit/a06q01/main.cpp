#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <climits>

void coin_change(int n, const std::vector<int> & C)
{
    int Fail = n+1;
    int table_lookup[n+1][C.size()+1];
    std::vector<int> table_path[n+1][C.size()+1];
    
    for (int i = 0; i <= C.size(); ++i)
    {
        for (int j = 0; j <= n; ++j)
        {
            table_lookup[j][i] = Fail;
            table_path[0][i] = std::vector<int>(C.size(), 0);
        }
    }

    for (int i = 0; i <= C.size(); ++i)
    {
        table_lookup[0][i] = 0;
    }
    
    for (int i = 1; i <= C.size(); ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            if (j - C[i-1] >= 0)
            {
                if (table_lookup[j][i-1] < (table_lookup[j-C[i-1]][i]+1))
                {
                    table_lookup[j][i] = table_lookup[j][i-1];
                    table_path[j][i] = table_path[j][i-1];
                    // table_path[j][i][i-2]++;
                }
                else
                {
                    table_lookup[j][i] = (table_lookup[j-C[i-1]][i]+1);
                    table_path[j][i] = table_path[j-C[i-1]][i];
                    table_path[j][i][i-1]++;
                }
                
            }
            else
            {
                table_lookup[j][i] = table_lookup[j][i-1];
                table_path[j][i] = table_path[j][i-1];
                // table_path[j][i][i-2]++;
            }
        }
    }
    if (table_lookup[n][C.size()] == Fail)
    {
        std::cout << "Invalid" << std::endl;
        return;
    }
    else
    {
        std::cout << table_lookup[n][C.size()] << ' ';
    }
    std::string delim = "";
    for (int i = 0; i < table_path[n][C.size()].size(); ++i)
    {
        std::cout << delim << table_path[n][C.size()][i];
        delim = " ";
    }
    std::cout << "\n";
}

int main()
{
    std::vector<int> C;
    int input;
    std::cin >> input;
    while (input != -1)
    {
        C.push_back(input);
        std::cin >> input;
    }
    
    int n;
    std::cin >> n;
    coin_change(n,C);
}

//==============================
// l(n, c) = l()
