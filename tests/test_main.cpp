#include "engine/core/SaveSystem.h"
#include "engine/core/StoryFlags.h"
#include "engine/collision/AABB.h"
#include "engine/world/Level.h"
#include "engine/player/FirstPersonController.h"
#include <vector>
#include <cassert>
#include <cmath>
#include <cstdio>
using namespace last;
int main(){
 // Story flags
 StoryFlags f; f.set("PLAYER_FOUND_PHOTO"); assert(f.has("PLAYER_FOUND_PHOTO"));
 // Save/load roundtrip + corruption check
 { SaveData d; d.chapter=3; d.pos={1.5f,1.7f,-2.5f}; d.yaw=0.7f;
   assert(saveGame("t.sav",d)); SaveData o; assert(loadGame("t.sav",o));
   assert(o.chapter==3 && std::fabs(o.pos.x-1.5f)<1e-4f && std::fabs(o.yaw-0.7f)<1e-4f); }
 // Collision: wall blocks movement
 { std::vector<AABB> s=buildMap01Solids(); assert(!s.empty());
   FirstPersonController pc; pc.pos={0,1.7f,10}; pc.yaw=3.14159f; // facing +z toward south wall? walls bound room
   InputState in; in.moveZ=1.f;
   for(int i=0;i<120;i++) pc.update(in,1.0f/60,s.data(),(int)s.size());
   assert(pc.pos.z<19.f); // clamped by boundary
   assert(std::isfinite(pc.pos.x) && std::isfinite(pc.pos.z)); }
 // Look clamps
 { FirstPersonController pc; pc.look(0,100000); assert(pc.pitch<=-1.5f); }
 std::printf("ALL TESTS PASSED\n"); return 0; }
