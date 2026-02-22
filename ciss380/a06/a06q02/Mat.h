#ifndef MAT_H
#define MAT_H

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

template < typename T >
class Mat
{
public:
    Mat(int rowsize, int colsize, T * p=NULL)
        : p_(new T[rowsize * colsize]),
          rowsize_(rowsize), colsize_(colsize)
    {
        if (p != NULL)
        {
            for (int i = 0; i < rowsize * colsize; ++i)
            {
                *(p_ + i) = *(p + i);
            }
        }
    }

    Mat(const Mat & m)
        : rowsize_(m.rowsize()), colsize_(m.colsize()),
          p_(new T[m.rowsize() * m.colsize()])
    {
        for (int i = 0; i < rowsize_ * colsize_; ++i)
        {
            *(p_ + i) = m[i];
        }
    
    }
    
    void clear()
    {
        delete [] p_;
    }
    
    ~Mat()
    {
        clear();
    }

    T & operator[](int i) const
    {
        return p_[i];
    }

    T & operator[](int i)
    {
        return p_[i];
    }
    
    T & operator()(int r, int c)
    {
        return *(p_ + r * colsize_ + c);
    }
    
    T & operator()(int r, int c) const
    {
        return *(p_ + r * colsize_ + c);
    }

    int rowsize() const
    {
        return rowsize_;
    }

    int colsize() const
    {
        return colsize_;
    }

    Mat & operator=(const Mat & m)
    {
        clear();
        rowsize_ = m.rowsize();
        colsize_ = m.colsize();
        p_ = new T[rowsize_ * colsize_];
        for (int i = 0; i < rowsize_ * colsize_; ++i)
        {
            *(p_ + i) = m[i];
        }
        return *this;
    }
    
private:
    T * p_;
    int rowsize_;
    int colsize_;
};

template <typename T>
std::ostream & operator<<(std::ostream & cout, const Mat<T> & m)
{
    int max_length = 0;
    int * column_ordering = new int[m.colsize()];
    for (int r = 0; r < m.rowsize(); ++r)
    {
        int length = 0;
        int * p = new int[m.colsize()];
        for (int c = 0; c < m.colsize(); ++c)
        {
            std::ostringstream s;
            s << m(r, c);
            std::string t(s.str());
            length += t.size();
            p[c] = t.size();
        }
        
        if (length > max_length)
        {
            max_length = length;
            delete [] column_ordering;
            column_ordering = p;
        }
        else
        {
            delete [] p;
        }
    }
    
    for (int r = 0; r < m.rowsize(); ++r)
    {
        std::string delim = "";
        std::cout << "[";
        int size = max_length;
        
        for (int c = 0; c < m.colsize(); ++c)
        {
            // std::cout << column_ordering[c] << std::endl;;
            std::cout << delim << std::setw(column_ordering[c])
                      << m(r, c);
            delim = " ";
            
        }
        std::cout << "]\n";
    }

    delete [] column_ordering;
    
    return cout;
}

#endif
