#include "vec4f.h"

float vec4f::x() const
{
    return x_;
}
float vec4f::y() const
{
    return y_;
}
float vec4f::z() const
{
    return z_;
}

float vec4f::t() const
{
    return t_;
}

float & vec4f::x()
{
    return x_;
}

float & vec4f::y()
{
    return y_;
}

float & vec4f::z()
{
    return z_;
}

float & vec4f::t()
{
    return t_;
}
    
vec4f & vec4f::operator=(const vec4f & v)
{
    x_ = v.x();
    y_ = v.y();
    z_ = v.z();
    t_ = v.t();

    return *this;
}
vec4f & vec4f::operator+=(const vec4f & v)
{
    x_ += v.x();
    y_ += v.y();
    z_ += v.z();
    t_ += v.t();

    return *this;
}
vec4f & vec4f::operator-()
{
    x_ *= -1;
    y_ *= -1;
    z_ *= -1;
    t_ *= -1;
    return *this;
}
vec4f vec4f::operator+(const vec4f & v) const
{
    vec4f ret = *this;
    return (ret += v);
}
vec4f vec4f::operator-(const vec4f & v) const
{
    vec4f ret = v;
    -ret;
    return (ret += *this);
}
double vec4f::len() const
{
    std::cout << x_ << ' ' << y_ << ' ' << z_ << ' ' << t_ << std::endl;
    return sqrt((x_ * x_) + (y_ * y_) + (z_ * z_) + (t_ * t_));
}

vec4f & vec4f::operator*=(float i)
{
    x_ *= i;
    y_ *= i;
    z_ *= i;
    t_ *= i;

    return *this;
}

vec4f vec4f::operator*(float i) const
{
    return vec4f(x_ * i, y_ * i, z_ * i, t_ * i);
}

vec4f & vec4f::operator/=(float i)
{
    x_ /= i;
    y_ /= i;
    z_ /= i;
    t_ /= i;

    return *this;
}
vec4f vec4f::operator/(float i) const
{
    return vec4f(x_ / i, y_ / i, z_ / i, t_ / i);
}

vec4f operator*(float i, const vec4f & v)
{
    return (v * i);
}

std::ostream & operator<<(std::ostream & cout, const vec4f & v)
{
    std::cout << '<' << v.x() << ", " << v.y() << ", " << v.z() << ", " << v.t() << ">\n";
    return cout;
}
