#pragma once
#include "../core/Vec3.h"
namespace last {
struct AABB { Vec3 min,max; };
inline bool overlaps(const AABB&a,const AABB&b){ return a.min.x<b.max.x&&a.max.x>b.min.x&&a.min.y<b.max.y&&a.max.y>b.min.y&&a.min.z<b.max.z&&a.max.z>b.min.z; }
inline Vec3 slideMove(Vec3 pos, Vec3 delta, float radius, float height, const AABB* solids, int n){
 Vec3 p=pos; auto box=[&](Vec3 c){ return AABB{Vec3{c.x-radius,c.y,c.z-radius}, Vec3{c.x+radius,c.y+height,c.z+radius}}; };
 p.x+=delta.x; { AABB b=box(p); for(int i=0;i<n;i++) if(overlaps(b,solids[i])){ p.x=delta.x>0? solids[i].min.x-radius : solids[i].max.x+radius; } }
 p.z+=delta.z; { AABB b=box(p); for(int i=0;i<n;i++) if(overlaps(b,solids[i])){ p.z=delta.z>0? solids[i].min.z-radius : solids[i].max.z+radius; } }
 return p; }
}
