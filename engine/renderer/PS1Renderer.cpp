#include "PS1Renderer.h"
#include "shaders.h"
#include <GLES2/gl2.h>
#include <cstdio>
#include <vector>
namespace last {
static unsigned compile(unsigned type, const char* src){
 unsigned s=glCreateShader(type); glShaderSource(s,1,&src,nullptr); glCompileShader(s);
 int ok=0; glGetShaderiv(s,GL_COMPILE_STATUS,&ok);
 if(!ok){ char buf[512]; glGetShaderInfoLog(s,512,nullptr,buf); std::fprintf(stderr,"[SHADER] %s\n",buf); }
 return s; }
static unsigned link(unsigned v, unsigned f){
 unsigned p=glCreateProgram(); glAttachShader(p,v); glAttachShader(p,f); glLinkProgram(p);
 int ok=0; glGetProgramiv(p,GL_LINK_STATUS,&ok);
 if(!ok){ char buf[512]; glGetProgramInfoLog(p,512,nullptr,buf); std::fprintf(stderr,"[PROG] %s\n",buf); }
 return p; }
bool PS1Renderer::init(int outW,int outH){
 outW_=outW; outH_=outH;
 glGenFramebuffers(1,&fbo_); glBindFramebuffer(GL_FRAMEBUFFER,fbo_);
 glGenTextures(1,&tex_); glBindTexture(GL_TEXTURE_2D,tex_);
 glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
 glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
 glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,iw_,ih_,0,GL_RGBA,GL_UNSIGNED_BYTE,nullptr);
 glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D,tex_,0);
 glGenRenderbuffers(1,&rbo_); glBindRenderbuffer(GL_RENDERBUFFER,rbo_);
 glRenderbufferStorage(GL_RENDERBUFFER,GL_DEPTH_COMPONENT16,iw_,ih_);
 glFramebufferRenderbuffer(GL_FRAMEBUFFER,GL_DEPTH_ATTACHMENT,GL_RENDERBUFFER,rbo_);
 if(glCheckFramebufferStatus(GL_FRAMEBUFFER)!=GL_FRAMEBUFFER_COMPLETE) return false;
 unsigned vs=compile(GL_VERTEX_SHADER,kMeshVert), fs=compile(GL_FRAGMENT_SHADER,kMeshFrag);
 prog_=link(vs,fs); unsigned qvs=compile(GL_VERTEX_SHADER,kQuadVert), qfs=compile(GL_FRAGMENT_SHADER,kQuadFrag);
 quadProg_=link(qvs,qfs);
 return true; }
void PS1Renderer::shutdown(){ if(prog_)glDeleteProgram(prog_); if(quadProg_)glDeleteProgram(quadProg_);
 if(fbo_)glDeleteFramebuffers(1,&fbo_); if(tex_)glDeleteTextures(1,&tex_); if(rbo_)glDeleteRenderbuffers(1,&rbo_); }
void PS1Renderer::beginFrame(float r,float g,float b){
 glBindFramebuffer(GL_FRAMEBUFFER,fbo_); glViewport(0,0,iw_,ih_);
 glEnable(GL_DEPTH_TEST); glClearColor(r,g,b,1); glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
 glUseProgram(prog_);
 glUniform2f(glGetUniformLocation(prog_,"uRes"),(float)iw_,(float)ih_);
 glUniform1f(glGetUniformLocation(prog_,"uJitter"),jitter_);
 glUniform3f(glGetUniformLocation(prog_,"uFogCol"),0.03f,0.045f,0.06f);
 glUniform2f(glGetUniformLocation(prog_,"uFog"),fogN_,fogF_); }
void PS1Renderer::drawMesh(const float* pos,const uint8_t* col,int nverts,const uint16_t* idx,int nidx, const Mat4& model){
 glUniformMatrix4fv(glGetUniformLocation(prog_,"uMVP"),1,GL_FALSE,model.m);
 (void)model;
 GLuint vbo=0, ebo=0; glGenBuffers(1,&vbo); glBindBuffer(GL_ARRAY_BUFFER,vbo);
 glBufferData(GL_ARRAY_BUFFER,nverts*3*sizeof(float),pos,GL_STATIC_DRAW);
 GLuint cbo=0; glGenBuffers(1,&cbo); glBindBuffer(GL_ARRAY_BUFFER,cbo);
 glBufferData(GL_ARRAY_BUFFER,nverts*3*sizeof(uint8_t),col,GL_STATIC_DRAW);
 glGenBuffers(1,&ebo); glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ebo);
 glBufferData(GL_ELEMENT_ARRAY_BUFFER,nidx*sizeof(uint16_t),idx,GL_STATIC_DRAW);
 glEnableVertexAttribArray(0); glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,nullptr);
 glEnableVertexAttribArray(1); glVertexAttribPointer(1,3,GL_UNSIGNED_BYTE,GL_TRUE,0,nullptr);
 glDrawElements(GL_TRIANGLES,nidx,GL_UNSIGNED_SHORT,nullptr);
 glDeleteBuffers(1,&vbo); glDeleteBuffers(1,&cbo); glDeleteBuffers(1,&ebo); }
void PS1Renderer::endFrame(){
 glBindFramebuffer(GL_FRAMEBUFFER,0); glViewport(0,0,outW_,outH_);
 glDisable(GL_DEPTH_TEST); glUseProgram(quadProg_);
 glActiveTexture(GL_TEXTURE0); glBindTexture(GL_TEXTURE_2D,tex_);
 glUniform1i(glGetUniformLocation(quadProg_,"uTex"),0);
 static float quad[]={-1,-1, 1,-1, 1,1, -1,1};
 glEnableVertexAttribArray(0); glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,0,quad);
 glDrawArrays(GL_TRIANGLE_FAN,0,4); }
}
