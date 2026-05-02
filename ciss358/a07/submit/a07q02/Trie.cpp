#include "Trie.h"

void Trie::print(const std::string & word)
{
    std::vector<std::string> v = root_->complete(word);
    if (v.size() == 0)
    {
        std::cout << '?';
    }
    else
    {
        if (v.size() == 1)
        {
            std::cout << '*';
        }
        else
            std::cout << '+';
            
    }
    std::cout << word;
    char c = ':';
    for (int i = 1; i < v.size(); ++i)
    {
        std::cout << c << v[i];
        c = ',';
    }
    std::cout << std::endl;
}

bool Trie::find(const std::string & s) const
{
    return root_->search(s);
}
