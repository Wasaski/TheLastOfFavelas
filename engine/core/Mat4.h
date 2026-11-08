#pragma once
#include "Vec3.h"
#include <cmath>
namespace last {
struct Mat4 { float m[16]={1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1};
 static Mat4 identity(){return Mat4{};}
 static Mat4 perspective(float fovY,float aspect,float zn,float zf){
  Mat4 r{}; float t=std::tan(fovY*0.5f); float d=1.0f/t;
  r.m[0]=d/aspect; r.m[5]=d; r.m[10]=(zf+zn)/(zn-zf); r.m[11]=-1; r.m[14]=(2*zf*zn)/(zn-zf); r.m[15]=0; return r;}
 static Mat4 lookAt(const Vec3&eye,const Vec3&ctr,const Vec3&up){
  Vec3 f=norm(ctr-eye), s=norm(cross(f,up)), u=cross(s,f); Mat4 r{};
  r.m[0]=s.x; r.m[1]=u.x; r.m[2]=-f.x; r.m[4]=s.y; r.m[5]=u.y; r.m[6]=-f.y;
  r.m[8]=s.z; r.m[9]=u.z; r.m[10]=-f.z;
  r.m[12]=-dot(s,eye); r.m[13]=-dot(u,eye); r.m[14]=dot(f,eye); r.m[15]=1; return r;}
 static Mat4 mul(const Mat4&a,const Mat4&b){ Mat4 r{}; for(int c=0;c<4;c++)for(int rw=0;rw<4;rw++){
  float s=0; for(int k=0;k<4;k++) s+=a.m[k*4+rw]*b.m[c*4+k]; r.m[c*4+rw]=s;} return r;}
};
}
