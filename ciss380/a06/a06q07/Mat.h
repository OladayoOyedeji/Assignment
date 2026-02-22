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
        for (int i = 0; i < rowsize * colsize; ++i)
        {
            *(p_ + i) = 0;
        }
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

    Mat row(int i) const
    {
        T * x = new T[colsize_];
        for (int c = 0; c < colsize_; c++)
        {
            x[c] = this->operator()(i, c);
        }
        Mat<T> ret(1, colsize_, x);

        delete [] x;
         
        return ret;
    }

    void insert_row(const Mat & m, int r)
    {
        for (int c = 0; c < colsize_; ++c)
        {
            p_[r * colsize_ + c] = m(0, c);
        }
    }

    void row_multiply(int r, T s)
    {
        for (int c = 0; c < colsize_; c++)
        {
            this->operator()(r, c) *= s;
        }
    }

    void swap(int r1, int r2)
    {
        if (r1 == r2) return; 
        for (int c = 0; c < colsize_; c++)
        {
            // swap((r1, c), (r2, c))

            int t = this->operator()(r1, c);
            this->operator()(r1, c) = this->operator()(r2, c);
            this->operator()(r2, c) = t;
        }
    }

    int find_row_pivot(int c)
    {
        for (int r = c; r < rowsize_; ++r)
        {
            if (this->operator()(r, c) != 0)
            {
                return r;
            }
        }
        return -1;
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

    void ref(Mat & I)
    {
        for (int i = 0; i < rowsize(); ++i)
        {
            int r = find_row_pivot(i);

            if (r == -1)
            {
                throw NotInvertibleError();
            
            }
            swap(r, i);
            I.swap(r, i);
        

            // std::cout << "swapped\n" << m << std::endl;

            int d = i * (colsize_ + 1);
            I.row_multiply(i, 1/float(p_[d]));
            row_multiply(i, 1/float(p_[d]));
            // std::cout << "minus" << std::endl;
            for (int j = 0; j < rowsize(); ++j)
            {
                if (i != j)
                {
                    T c = p_[j * colsize_ + i];
                    // std::cout << c << std::endl;
                    // std::cout << row(i) << std::endl;
                    // std::cout << row(i) * c << row(j) << std::endl;;
                    Mat<T> ret = row(j) - c * row(i);
                    Mat<T> retI = I.row(j) - c * I.row(i);
                    //std::cout << ret << std::endl;
                    insert_row(ret, j);
                    I.insert_row(retI, j);
                }
                // std::cout << m << I << std::endl;;
            }
        }
    }



    
    Mat inv() const
    {
        if (rowsize_ != colsize_) throw SizeError();
        
        Mat ret(*this);
        Mat I(rowsize_, colsize_);

        for (int i = 0; i < rowsize_; ++i)
        {
            I(i, i) = 1;
        }
        std::cout << I << std::endl;
        ret.ref(I);

        return I;
    }
    
    Mat operator-() const
    {
        return *this * -1;
    }
    
    Mat operator+(const Mat & m)
    {
        Mat<T> ret(*this);

        ret += m;
        
        return ret;
    }

    Mat operator-(const Mat & m) const
    {
        Mat<T> ret = -m;
        // std::cout << "sub" << std::endl;
        // std::cout << ret << m << std::endl;
        ret += *this;
        return ret;
    }

    Mat & operator-=(const Mat & m)
    {
        
        return (*this += -m);
    }

    Mat operator*=(const Mat & m)
    {
        *this = (*this * m);

        return *this;
    }

    Mat & operator*=(const T & c)
    {
        for (int i = 0; i < rowsize_ * colsize_; ++i)
        {
            p_[i] *= c;
        }
        return *this;
    }
    
    Mat operator*(const T & c) const
    {
        Mat<T> ret(*this);
        
        for (int i = 0; i < rowsize_ * colsize_; ++i)
        {
            ret[i] *= c;
        }
        return ret;
    }
    
private:
    T * p_;
    int rowsize_;
    int colsize_;
};

template < typename T >
Mat< T > operator*(const T & c, const Mat< T > & m)
{
    return (m * c);
}

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
