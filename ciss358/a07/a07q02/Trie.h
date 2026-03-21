#ifndef TRIE_H
#define TRIE_H

#include "Node.h"

class Trie
{
  public:
    Trie()
        : root_(new TreeNodev(' '))
    {}
    ~Trie()
    {
        root_->clear_children();
        delete root_;
    }
    void operator=(const std::string & s)
    {
        root_->insert(s);
    }
    void print(const std::string & word);
    bool find(const std::string & s) const;
    
  private:
    TreeNodev * root_;
};

#endif
