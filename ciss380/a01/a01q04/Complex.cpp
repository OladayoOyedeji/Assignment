#include "Complex.h"

double complex::re() const
{
    return re_;
}

double complex::im() const
{
    return im_;
}

complex & complex::operator+=(const complex & z)
{
    re_ += z.re();
    im_ += z.im();
    
    return *this;
}

complex & complex::operator-=(const complex & z)
{
    *this += -z;
    
    return *this;
}

complex & complex::operator*=(const complex & z)
{
    int re = re_ * z.re() - im_ * z.im();
    int im = re_ * z.im() + im_ * z.re();

    re_ = re;
    im_ = im;

    return *this;
}

complex & complex::operator/=(const complex & z)
{
    re_ = re_ / (z.re() * z.re() + z.im() * z.im());
    im_ = re_ / (z.re() * z.re() + z.im() * z.im());

    *this *= z.conjugate();
    
    return *this;
}

complex complex::operator+(const complex & z) const
{
    complex ret(re_, im_);

    ret += z;
    
    return ret;
}
complex complex::operator-(const complex & z)
{
    complex ret(re_, im_);

    ret -= z;
    
    return ret;
}
complex complex::operator*(const complex & z)
{
    complex ret(re_, im_);

    ret *= z;
    
    return ret;
}

complex complex::operator/(const complex & z) const
{
    complex ret(re_, im_);

    ret /= z;
    
    return ret;
}

double complex::abs() const
{
    double ret = sqrt(re_ * re_ + im_ * im_);
    
    return ret;
}

complex operator+(double x, const complex & z)
{
    return complex(x + z.re(), z.im());
}

complex operator-(double x, const complex & z)
{
    return complex(x - z.re(), z.im());
}
complex operator*(double x, const complex & z)
{
    return complex(x * z.re(), x * z.im());
}
complex operator/(double x, const complex & z)
{
    complex ret(x);
    return ret / z;
}
double abs(const complex z);
std::istream & operator>>(std::istream & cin, complex & z)
{
    int re_, im_;
    
    cin >> re_ >> im_;

    z = complex(re_, im_);

    return cin;
}
std::ostream & operator<<(std::ostream & cout, const complex & z)
{
    cout << z.re();
    if (z.im() < 0)
    {
        cout << " - " << -1 * z.im();
    }
    else
    {
        cout << " + " << z.im();
    }
    cout << 'i'; 
    
    return cout;
}
