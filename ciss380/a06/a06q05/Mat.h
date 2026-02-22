#ifndef MAT_H
#define MAT_H

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <exception>

class IndexError: public std::exception
{};

class SizeError: public std::exception
{};

class NotInvertibleError: public std::exception
{};

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

    bool operator==(const Mat & m) const
    {
        if (m.rowsize() != rowsize_ || m.colsize() != colsize_)
            return false;

        int size = rowsize_ * colsize_;
        for (int i = 0; i < size; ++i)
        {
            if (*(p_ + i) != m[i])
            {
                return false;
            }
        }
        return true;
    }

    bool operator!=(const Mat & m) const
    {
        return !(*this == m);
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
        if (r >= rowsize_ || c >= colsize_) throw IndexError();
        return *(p_ + r * colsize_ + c);
    }
    
    T & operator()(int r, int c) const
    {
        if (r >= rowsize_ || c >= colsize_) throw IndexError();
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

    Mat & operator+=(const Mat & m)
    {
        if (m.rowsize() != rowsize_ || m.colsize() != colsize_)
            throw SizeError();
        for (int i = 0; i < rowsize_ * colsize_; ++i)
        {
            p_[i] += m[i];
        }

        return *this;
    }

    Mat operator*(const Mat & m) const
    {
        if (colsize_ != m.rowsize()) throw SizeError();
        int size = colsize_;
        
        Mat<T> ret(rowsize_, m.colsize());

        for (int r = 0; r < rowsize_; r++)
        {
            // multiply that with colums
            for (int c = 0; c < m.colsize(); c++)
            {
                for (int i = 0; i < size; ++i)
                {
                    ret(r, c) += this->operator()(r, i) * m(i, c);
                }
            }
        }

        return ret;
    }

    Mat operator+(const Mat & m)
    {
        Mat<T> ret(*this);

        ret += m;
        
        return ret;
    }

    Mat operator*=(const Mat & m)
    {
        *this = (*this * m);

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
