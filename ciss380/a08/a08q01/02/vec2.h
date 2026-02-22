#ifndef VEC2_H
#define VEC2_H

#include <iostream>
#include <cmath>

class ValueError
{};

template < typename T >
class vec2
{
  public:
  vec2(T x = 0, T y = 0)
      : x_(x), y_(y)
    {}
    bool operator==(const vec2< T > & v) const
    {
        return (x_ == v.x() && y_ == v.y());
    }
    bool operator!=(const vec2< T > & v) const
    {
        return !(vec2(x_, y_) == v);
    }

    vec2 & operator=(const vec2<T> & v)
    {
        x_ = v.x(); y_ = v.y();
        
        return *this;
    }
    
    T & x()
    {
        return x_;
    }

    T & y()
    {
        return y_;
    }
    
    T x() const
    {
        return x_;
    }
    
    T y() const
    {
        return y_;
    }
    
    T operator[](int i) const
    {
        if (i > 1)
        {
            throw ValueError();
        }
        return (i > 0 ? y_ : x_);
    }
    
    T & operator[](int i)
    {
        if (i == 0)
        {
            return this->x_;
        }
        else
        {
            return this->y_;
        }
    }
    
    vec2< T > operator+() const
    {
        return vec2(x_, y_);
    }
    vec2< T > & operator+=(const vec2< T >& v)
    {
        x_ = x_ + v.x();
        y_ = y_ + v.y();
        return *this;
    }
    vec2< T > operator+(const vec2< T > & v) const
    {
        vec2 ret(x_ + x(), y_ + y());
        return ret;
    }
    vec2< T > operator-() const
    {
        return vec2(-x_, -y_);
    }
    
    vec2< T > & operator-=(const vec2< T > & v)
    {
        x_ = x_ - v.x();
        y_ = y_ - v.y();
        return *this;
    }
    vec2< T > operator-(const vec2< T > & v) const
    {
        vec2< T > ret(T(x_ - v.x()), T(y_ - v.y()));
        return ret;
    }
    vec2< T > & operator*=(T i)
    {
        x_ *= i;
        y_ *= i;
        return *this;
    }
    
    vec2< T > operator*(T i) const
    {
        return vec2(x_ * i, y_ * i);
    }
    
    vec2< T > & operator/=(T i)
    {
        x_ /= i;
        y_ /= i;
        return *this;
    }
    vec2< T > operator/(T i) const
    {
        return vec2(x_ / i, y_ / i);
    }
    double len() const
    {
        return sqrt((x_ * x_) + (y_ * y_));
    }
  private:
    T x_, y_;
};

typedef vec2< int > vec2i;
typedef vec2< float > vec2f;
typedef vec2< double > vec2d;

template < typename T >
vec2< T > operator*(T i, const vec2< T > & v)
{
    return (v * i);
}

template < typename T >
double len(const vec2< T > & v)
{
    return v.len();
}

template < typename T >
T dotprod(const vec2< T > & u, const vec2< T > & v)
{
    return ((u.x() * v.x()) + (u.y() * v.y()));
}

template < typename T >
vec2< T > norm(const vec2< T > & v)
{
    return v / len(v);
}

template < typename T >
std::ostream & operator<<(std::ostream & cout, const vec2< T > & v)
{
    cout << '<' << v.x() << ", " << v.y() << '>';
    return cout;
}

template < typename T >
std::istream & operator>>(std::istream & cin, vec2< T > & v)
{
    T x, y;
    std::cin >> x >> y;
    v.x() = x; v.y() = y;
    return cin;
}

#endif
