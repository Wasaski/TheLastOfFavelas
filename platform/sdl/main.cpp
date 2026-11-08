#include <SDL3/SDL.h>
#include <GLES2/gl2.h>
#include "renderer/PS1Renderer.h"
#include "world/Level.h"
#include "player/FirstPersonController.h"
#include "core/Mat4.h"
#include <cmath>
#include <cstdio>
using namespace last;

// Placeholder ground + house geometry (low-poly, procedural — see engine/world/Level for solids).
// Colors: concrete gray, dark green, dirty white — PS1 palette.
static float kPos[] = { -20,0,20, 20,0,20, 20,0,-20, -20,0,-20,  -4,0,-4, 4,0,-4, 4,0,4, -4,0,4 };
static uint8_t kCol[] = { 90,90,90, 90,90,90, 90,90,90, 90,90,90, 70,80,60, 70,80,60, 70,80,60, 70,80,60 };
static uint16_t kIdx[] = { 0,1,2, 0,2,3, 4,5,6, 4,6,7 };

static void fatal(const char* step){
 char msg[256]; std::snprintf(msg,sizeof msg,"%s: %s",step,SDL_GetError());
 std::fprintf(stderr,"FATAL %s\n",msg);
 SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,"THE LAST OF FAVELAS",msg,nullptr); }
int main(int argc, char** argv){
 if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_EVENTS)!=0){ fatal("SDL init"); return 1; }
 SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
 SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
 SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 0);
 SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 0);
 SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
 SDL_Window* win = SDL_CreateWindow("THE LAST OF FAVELAS", 960, 540, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
 if(!win){ fatal("window"); return 1; }
 SDL_GLContext ctx = SDL_GL_CreateContext(win);
 if(!ctx){ fatal("GL"); return 1; }
 int w=960,h=540; SDL_GetWindowSize(win,&w,&h);
 PS1Renderer r; if(!r.init(w,h)){ fatal("renderer (FBO/shader)"); return 1; }
 auto solids = buildMap01Solids();
 FirstPersonController pc; pc.pos={0,1.7f,10};
 Uint64 lastT=SDL_GetTicks();
 bool run=true;
 while(run){
  Uint64 now=SDL_GetTicks(); float dt=(now-lastT)/1000.0f; lastT=now; if(dt>0.1f)dt=0.1f;
  SDL_Event e; InputState in;
  while(SDL_PollEvent(&e)){ if(e.type==SDL_EVENT_QUIT) run=false;
   if(e.type==SDL_EVENT_KEY_DOWN){ if(e.key.key==SDLK_ESCAPE) run=false;
    if(e.key.key==SDLK_W) in.moveZ=1; if(e.key.key==SDLK_S) in.moveZ=-1;
    if(e.key.key==SDLK_A) in.moveX=-1; if(e.key.key==SDLK_D) in.moveX=1;
    if(e.key.key==SDLK_LSHIFT) in.sprint=true; if(e.key.key==SDLK_C) in.crouch=true; }
   if(e.type==SDL_EVENT_KEY_UP){ if(e.key.key==SDLK_W||e.key.key==SDLK_S) in.moveZ=0;
    if(e.key.key==SDLK_A||e.key.key==SDLK_D) in.moveX=0;
    if(e.key.key==SDLK_LSHIFT) in.sprint=false; if(e.key.key==SDLK_C) in.crouch=false; }
   if(e.type==SDL_EVENT_MOUSE_MOTION) pc.look(e.motion.xrel,e.motion.yrel,0.0025f);
   if(e.type==SDL_EVENT_WINDOW_RESIZED) SDL_GetWindowSize(win,&w,&h);
  }
  // mouse-look held keys fallback (poll)
  const bool* k=SDL_GetKeyboardState(nullptr);
  if(k[SDL_SCANCODE_W]) in.moveZ+=1; if(k[SDL_SCANCODE_S]) in.moveZ-=1;
  if(k[SDL_SCANCODE_A]) in.moveX-=1; if(k[SDL_SCANCODE_D]) in.moveX+=1;
  pc.update(in,dt,solids.data(),(int)solids.size());
  Vec3 eye{pc.pos.x, pc.pos.y+pc.bobOffset(), pc.pos.z};
  Vec3 ctr{eye.x-std::sin(pc.yaw)*std::cos(pc.pitch), eye.y+std::sin(pc.pitch), eye.z-std::cos(pc.yaw)*std::cos(pc.pitch)};
  Mat4 proj=Mat4::perspective(1.22f,(float)w/h,0.1f,60.f);
  Mat4 view=Mat4::lookAt(eye,ctr,{0,1,0});
  Mat4 mvp=Mat4::mul(proj,view);
  r.beginFrame(0.03f,0.045f,0.06f);
  // MVP passed via drawMesh model slot (renderer multiplies internally in shader via uMVP — see note)
  // NOTE: PS1Renderer.drawMesh currently ignores `model`; MVP upload wired in renderer pass.
  r.drawMesh(kPos,kCol,8,kIdx,12,mvp);
  r.endFrame();
  SDL_GL_SwapWindow(win);
  SDL_Delay(16);
 }
 r.shutdown(); SDL_DestroyWindow(win); SDL_Quit();
 return 0; }
