#ifndef COMPLEX_H
#define COMPLEX_H

#include <iostream>
#include <cmath>

class complex
{   
public:
    complex()
        : re_(0), im_(0)
    {}
    
    complex(double re, double im)
        : re_(re), im_(im)
    {}
    
    complex(double re)
        : re_(re), im_(0)
    {}
    
    double re() const;
    
    double im() const;
    
    complex & operator+=(const complex & z);
    complex & operator-=(const complex & z);
    complex & operator*=(const complex & z);
    complex & operator/=(const complex & z);
    complex & operator=(const complex & z)
    {
        re_ = z.re(); im_ = z.im();
        return *this;
    }
    
    complex operator+(const complex & z) const;
    complex operator-(const complex & z);
    complex operator*(const complex & z);
    complex operator/(const complex & z) const;

    complex operator-() const
    {
        return complex(-1 * re_, -1 * im_);
    }
    complex conjugate() const
    {
        return complex(re_, -1 * im_);
    }
    double abs() const;
private:
    double re_, im_;
};

complex operator+(double x, const complex & z);
complex operator-(double x, const complex & z);
complex operator*(double x, const complex & z);
complex operator/(double x, const complex & z);
double abs(const complex z);
std::istream & operator>>(std::istream & cin, complex & z);
std::ostream & operator<<(std::ostream & cout, const complex & z);

#endif
