#include "stdalgo.cpp"

//Vector 2-Dimension
template<typename T> struct vec2
{
    T x,y;
    vec2(){}
    vec2(T x0,T y0) {x=x0;y=y0;}
    inline vec2 operator +(const vec2 &a) {return vec2<T>(x+a.x,y+a.y);}
    inline vec2 operator -(const vec2 &a) {return vec2<T>(x-a.x,y-a.y);}
    inline vec2 operator *(const vec2 &a) {return vec2<T>(x*a.x,y*a.y);}
    inline int operator /(const vec2 &a) {return x*a.y-y*a.x;}
};
//Line 2-Dimension 
template<typename T> struct line2
{
    T x[2],y[2];
    line2(){}
    line2(T x0,T y0,T x1,T y1) {x[0]=x0;x[1]=x1;y[0]=y0;y[1]=y1;}
    inline vec2<T> v() const {return vec2<T>(x[1]-x[0],y[1]-y[0]);}
    inline bool operator *(const line2 &a)
    {
        vec2<T> tmp=vec2<T>(a.x[1]-x[0],a.y[1]-y[0]);
        int p=sgn((v()/vec2<T>(a.x[0]-x[0],a.y[0]-y[0]))),
            q=sgn((v()/tmp)),
            r=sgn((a.v()/vec2<T>(x[1]-a.x[1],y[1]-a.y[1]))),
            s=sgn((a.v()/tmp));
        return (p*q<0&&r*s>0)
            ||(p==0&&at(x[0],a.x[0],x[1])&&at(y[0],a.y[0],y[1]))
            ||(s==0&&at(x[0],a.x[1],x[1])&&at(y[0],a.y[1],y[1]))
            ||(q==0&&at(a.x[0],x[0],a.x[1])&&at(a.y[0],y[0],a.y[1]))
            ||(r==0&&at(a.x[0],x[1],a.x[1])&&at(a.y[0],y[1],a.y[1]));
    }
};

//Vector 3-Dimension
template<typename T> struct vec3
{
	T x,y,z;
	vec3(){}
	vec3(T x0,T y0,T z0) {x=x0;y=y0;z=z0;}
	vec3 operator +(const vec3 &a) {return vec3<T>(x+a.x,y+a.y,z+a.z);}
	vec3 operator -(const vec3 &a) {return vec3<T>(x-a.x,y-a.y,z-a.z);}
	vec3 operator *(const vec3 &a) {return vec3<T>(x*a.x,y*a.y,z*a.z);}
	vec3 operator /(const vec3 &a) {return vec3<T>(y*a.z-z*a.y,z*a.x-x*a.z,x*a.y-y*a.x);}
};
//Line 3-Dimension
template<typename T> struct line3
{
	T x[2],y[2],z[2];
	inline vec3<T> v() const {return vec3<T>(x[1]-x[0],y[1]-y[0],z[1]-z[0]);}
};
