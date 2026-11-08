#pragma once
#include <cmath>
namespace last {
struct Vec3 { float x=0,y=0,z=0;
 Vec3 operator+(const Vec3&o)const{return{x+o.x,y+o.y,z+o.z};}
 Vec3 operator-(const Vec3&o)const{return{x-o.x,y-o.y,z-o.z};}
 Vec3 operator*(float s)const{return{x*s,y*s,z*s};}
 Vec3& operator+=(const Vec3&o){x+=o.x;y+=o.y;z+=o.z;return *this;}
 float len()const{return std::sqrt(x*x+y*y+z*z);} };
inline float dot(const Vec3&a,const Vec3&b){return a.x*b.x+a.y*b.y+a.z*b.z;}
inline Vec3 cross(const Vec3&a,const Vec3&b){return{a.y*b.z-a.z*b.y,a.z*b.x-a.x*b.z,a.x*b.y-a.y*b.x};}
inline Vec3 norm(const Vec3&v){float l=v.len(); return l>1e-6f? v*(1.0f/l):v;}
}
