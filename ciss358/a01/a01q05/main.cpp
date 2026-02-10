#include <iostream>
#include <set>
#include <vector>
#include <string>

using namespace std;
const int N = 9;

// class cell
//       - set<int> neigbhors_;
//       - int available_number = 511;

// could turn to
typedef pair<set<int>, int> Cell;
vector<Cell *> board_(N*N, NULL);

void printbits(int x)
{
    for (int i = 31; i >= 0; --i)
    {
        cout << ((x >> i) & 1);
    }
    cout << ' ' << x; 
}

std::ostream & operator<<(std::ostream & cout, const Cell & cell)
{
    cout << "{";
    string delim = "";
    for (auto p: cell.first)
    {
        cout << delim << p;
        delim = ", ";
    }
    cout << "}\n";
    printbits(cell.second);

    return cout;
}

void print_sudoku(const string & s)
{
    for (int i = 0; i < N * N; ++i)
    {
        if (i % 27 == 0)
            cout << "+-------+-------+-------+\n";
        if (i % 3 == 0)
            cout << "| ";
        cout << s[i] << " ";
        if ((i+1) % N == 0)
            cout << "|" << endl;
    }
    cout << "+-------+-------+-------+\n";
}

void rem_from_avaiNum(int n, Cell * cell, vector<int> & v)
{
    v.resize(cell->first.size());
    int j = 0;
    for (auto i: cell->first)
    {
        v[j++] = cell->second & ((1 << 9) - 1);
        
        board_[i]->second &= ~(1 << (n-1));
    }
}

void ins_to_availNum(int n, Cell * cell, vector<int> & v)
{
    int j = 0;
    for (auto i: cell->first)
    {
        int k = v[j++] >> (n-1) & 1;
        board_[i]->second |= (1 << k);
    }
}

void rem_from_neigbhors(int pos, Cell * cell)
{
    for (auto i: cell->first)
    {
        board_[i]->first.erase(pos);
    }
}

void ins_to_neigbhors(int pos, Cell * cell)
{
    for (auto i: cell->first)
    {
        board_[i]->first.insert(pos);
    }
}

bool solve_sudoku(string & s, Cell * cell)
{
    int pos = cell->second >> 9;
    int av = cell->second & ((1 << 9) - 1);
    if (av == 0) return false;

    for (int i = 1; i <= 10; i++)
    {
        int n = av >> (i-1) & 1;
        if (n)
        {
            // remove n from neigbhors available numbers;
            vector<int> v;
            s[pos] = i + '0';
            rem_from_avaiNum(i, cell, v);
            // remove pos from neigbhors neigbhors;
            rem_from_neigbhors(pos, cell);
            
            // to get the next
            bool solved = true;
            for (int j = pos+1; j < 81; j++)
            {
                if (board_[j] != NULL)
                {
                    solved = solve_sudoku(s, board_[j]);
                    break;
                }
            }

            if (solved) return true;
            
            s[pos] = '.';
            // add n to neigbhors available numbers;
            ins_to_availNum(i, cell, v);
            // add pos to neigbhors
            ins_to_neigbhors(pos, cell);
        }
    }
    return false;
}

void init_sudoku(const string & s)
{
    for (int i = 0; i < s.size(); ++i)
    {
        if (s[i] == '.')
        {
            if (board_[i] == NULL)
            {
                board_[i] = new Cell;
                board_[i]->second = (i << 9) | 511;
                
            }
            // horizontal
            int r = i / 9 * 9;
            for (int j = r; j < r + 9; ++j)
            {
                if (j != i)
                {
                    if (s[j] == '.')
                    {
                        (board_[i]->first).insert(j);
                        
                    }
                    else
                    {
                        int a = (s[j] - '0') - 1;
                        board_[i]->second &= ~(1 << a);
                    }
                }
            }
            r /= 9;

            // vertical
            int c = i % 9;
            for (int j = c; j < 81; j += 9)
            {
                if (j != i)
                {
                    if (s[j] == '.')
                    {
                        (board_[i]->first).insert(j);
                        
                    }
                    else
                    {
                        int a = (s[j] - '0') - 1;
                        board_[i]->second &= ~(1 << a);
                    }
                }
            }

            // box
            (r /= 3) *= 3;
            (c /= 3) *= 3;
            //cout << r << ' ' << c << endl;
            for (int j = r; j < r + 3; j++)
            {
                for (int k = c; k < c + 3; k++)
                {
                    int pos = j * 9 + k;
                    
                    if (pos != i)
                    {
                        if (s[pos] == '.')
                        {
                            (board_[i]->first).insert(pos);
                            
                        }
                        else
                        {
                            int a = (s[pos] - '0') - 1;
                            board_[i]->second &= ~(1 << a);
                        }
                    }
                }
            }
        }

    }    
}

int main()
{
    string s;
    cin >> s;
    init_sudoku(s);

    Cell * c = NULL;
    for (int i = 0; i < N*N; ++i)
    {
        if (board_[i] != NULL)
        {
            c = board_[i];
            break;
        }
    }
    if (c != NULL)
    {
        solve_sudoku(s, c);
    }
    print_sudoku(s);
    
    return 0;
    
}
