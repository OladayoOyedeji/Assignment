#include "Trie.h"
#include <fstream>

void DF_allpaths(std::vector< std::list<int> > & u, int source, int sink, const string & word)
{
    stack< int > path;
    stack< stack<int> > s;
    path.push(source);
    s.push(path);
    vector< stack<int> > ret;
    while (!(s.empty()))
    {
        stack<int> path = s.top();
        s.pop();
        if (path.top() == sink)
        {
            ret.push_back(path);
        }
        else
        {
            int t = path.top();
            for (auto y: u[t])
            {
                stack<int> path0 = path;
                path0.push(y);
                s.push(path0);
            }
        }
    }
    
    cout << ret.size() << std::endl;
    for (int i = 0; i < ret.size(); i++)
    {
        string delim = "";
        std::stack<int> s_ = ret[i];
        
        int j = s_.top();
        s_.pop();
        while (!s_.empty())
        {
            int k = s_.top();
            cout << delim << word.substr(j, k-j);
            delim = " ";
            s_.pop();
            j = k;
        }
        cout << endl;
        
    }
}

void word_segmentation(std::string & s, const Trie & trie)
{
    std::vector<bool> table(s.size(), false);
    
    std::vector< std::list<int> > substring(s.size()+1);
    
    for (int j = 0; j < s.size(); ++j)
    {
        if ((j == 0 && !table[j])|| (table[j-1]))
        {
            for (int i = j; i < s.size(); ++i)
            {
                if (trie.find(s.substr(j, i-j+1)))
                {
                    table[i] = true;
                    substring[i+1].push_back(j);
                }
            }
        }
    }
    if (table[s.size()-1])
    {
        DF_allpaths(substring, substring.size() -1, 0, s);
    }
    else
    {
        cout << 0 << std::endl;
    }
}

int main()
{
    char s[1024];
    std::cin >> s;
    
    Trie pt;
    std::ifstream f;
    f.open(s, std::ios::in);
    while (!f.eof())
    {
        std::string s;
        f >> s;
        // std::cout << s << std::endl;
        // if (s == "re")
        // {
        //     int x;
        //     std::cin >> x;
        // }
        pt = s;
    }
    f.close();

    std::string word;
    std::cin >> word;
    // while (1)
    // {
    //     std::cout << pt.find(word) << std::endl;
    //     std::cin >> word;
    // }
    word_segmentation(word, pt);
    
    return 0;
}
