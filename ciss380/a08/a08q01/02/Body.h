#ifndef BODY_H
#define BODY_H

#include "vec2.h"

class Body
{
public:
    Body( double mass=0, float radius=0)
        : mass_(mass), radius_(radius)
    {}
    // char *& name()
    // {
    //     return name_;
    // }
    
    double & mass()
    {
        return mass_;
    }
    
    vec2<float> & pos()
    {
        return p_;
    }
    
    vec2<float> & vel()
    {
        return v_;
    }
    
    float & radius()
    {
        return radius_;
    }
    
    // char * name() const
    // {
    //     return name_;
    // }
    
    double mass() const
    {
        return mass_;
    }
    
    vec2<float> pos() const
    {
        
        return p_;
    }
    
    vec2<float> vel() const
    {
        return v_;
    }
    
    float radius() const
    {
        return radius_;
    }
    
    // char * name_;
    double mass_;
    vec2<float> p_;
    vec2<float> v_;
    float radius_;
};

#endif
