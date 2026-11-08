#pragma once
#include "../core/Vec3.h"
#include "../collision/AABB.h"
#include <cmath>
namespace last {
struct InputState { float moveX=0,moveZ=0; bool sprint=false,crouch=false; };
class FirstPersonController {
 public:
  Vec3 pos{0,1.7f,0}; float yaw=0,pitch=0; float bobT=0;
  float bobOffset()const{ return std::sin(bobT)*0.04f; }
  bool crouch()const{ return crouch_; }
  void update(const InputState& in, float dt, const AABB* solids, int n){
   crouch_=in.crouch;
   float speed=(in.crouch?1.6f:(in.sprint?7.5f:4.2f));
   Vec3 fwd{-std::sin(yaw),0,-std::cos(yaw)}, right{std::cos(yaw),0,-std::sin(yaw)};
   Vec3 delta=(fwd*in.moveZ + right*in.moveX)*speed*dt; delta.y=0;
   pos=slideMove(pos,delta,0.35f,1.8f,solids,n);
   if(delta.len()>0.001f) bobT+=dt*speed*1.4f; }
  void look(float dx,float dy,float sens=0.0025f){ yaw-=dx*sens; pitch=-dy*sens+pitch;
   const float lim=1.52f; if(pitch>lim)pitch=lim; if(pitch<-lim)pitch=-lim; }
 private: bool crouch_=false;
};
}
