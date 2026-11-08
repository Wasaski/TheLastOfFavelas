#pragma once
#include "../core/Mat4.h"
#include <cstdint>
namespace last {
class PS1Renderer {
 public:
  bool init(int outW,int outH); void shutdown();
  void beginFrame(float r,float g,float b);
  void drawMesh(const float* pos,const uint8_t* col,int nverts,const uint16_t* idx,int nidx, const Mat4& model);
  void endFrame();
  int internalW()const{return iw_;} int internalH()const{return ih_;}
  void setJitter(float j){jitter_=j;} void setFog(float nearD,float farD){fogN_=nearD;fogF_=farD;}
 private: int iw_=320, ih_=240; float jitter_=0.5f, fogN_=8.f, fogF_=38.f;
  unsigned fbo_=0, tex_=0, rbo_=0, prog_=0, quadProg_=0; int outW_=0,outH_=0; };
}
