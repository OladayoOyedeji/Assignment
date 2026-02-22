#ifndef VEC4F_H
#define VEC4F_H

#include <iostream>
#include <cmath>
#include <ctime>

class vec4f
{
public:
    vec4f(float x=0, float y=0, float z=0, float t=1)
        : x_(x), y_(y), z_(z), t_(t)
    {}

    vec4f(const vec4f & v)
        : x_(v.x()), y_(v.y()), z_(v.z()), t_(v.t())
    {}

    float x() const;
    float y() const;
    float z() const;
    float t() const;

    float & x();
    float & y();
    float & z();
    float & t();
    
    vec4f & operator=(const vec4f & v);
    vec4f & operator+=(const vec4f & v);
    vec4f & operator-();
    vec4f operator+(const vec4f & v) const;
    vec4f operator-(const vec4f & v) const;
    vec4f & operator*=(float i);
    vec4f operator*(float i) const;
    vec4f & operator/=(float i);
    vec4f operator/(float i) const;
    double len() const;
private:
    float x_, y_, z_, t_;
};

vec4f operator*(float i, const vec4f & v);

std::ostream & operator<<(std::ostream & cout, const vec4f & v);

#endif
