#include "Node.h"

void TreeNodev::clear_children()
{
    for (int i = 0; i < child_.size(); i++)
    {
        if (child_[i] != NULL)
        {
            child_[i]->clear_children();
            delete child_[i];
            child_[i] = NULL;
        }
        
    }
}
int TreeNodev::num_children()
{
    int size = 0;
    for (int i = 0; i < child_.size(); ++i)
    {
        if (child_[i] != NULL)
        {
            ++size;
        }
    }
    return size;
}

TreeNodev * TreeNodev::insert(char index, char key)
{
    if (child_[index - 'a'] == NULL)
    {
        child_[index - 'a'] = new TreeNodev(key, this);
    }
    return child_[index - 'a'];
}
void TreeNodev::insert(const std::string & word)
{
    TreeNodev * p = this;
    int i = 0;
    char c = ' ';
    while (i < word.size())
    {
        p = p->insert(word[i], c);
        i++;
    }
    p->key_ = '*';
}
void TreeNodev::insert(const char * word)
{
    std::string s = word;
    insert(s);
}

bool TreeNodev::search(const std::string & word) const
{
    const TreeNodev * p = this;
    int i = 0;
    while (i < word.size())
    {
        int j = word[i++] - 'a';
        if (p->child_[j] == NULL) return false;
        p = p->child_[j];
        
    }
    return (p->key() == '*');
}

std::vector<std::string> TreeNodev::complete(const std::string & word)
{
    std::vector<std::string> comp;
    int i = 0;
    TreeNodev * p = this;
    if (!(search(word)))
    {}
    else
    {
        comp.push_back(word);
        
        std::string s;
        p->add(comp, s);
    }
    return comp;
    
}

void TreeNodev::add(std::vector<std::string> & comp,
                    std::string & s)
{
    if (key_ == '*')
    {
        
        if (s != "")
            comp.push_back(s);
        //return;
    }
    for (int i = 0; i < 26; ++i)
    {
        if (child_[i] != NULL)
        {
            std::string w = s;
            w.push_back(i + 'a');
            child_[i]->add(comp, w);
        }
    }
}
