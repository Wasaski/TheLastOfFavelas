#include "SaveSystem.h"
#include <fstream>
#include <sstream>
namespace last {
static unsigned checksum(const std::string&s){unsigned h=2166136261u; for(unsigned char c:s){h^=c;h*=16777619u;} return h;}
bool saveGame(const std::string&path, const SaveData& d){
 std::ostringstream o; o<<"TLF_SAVE v1\nversion="<<d.version<<"\nchapter="<<d.chapter
  <<"\npx="<<d.pos.x<<"\npy="<<d.pos.y<<"\npz="<<d.pos.z<<"\nyaw="<<d.yaw<<"\npitch="<<d.pitch<<"\n";
 std::string body=o.str(); std::ofstream f(path); if(!f) return false;
 f<<body<<"checksum="<<checksum(body)<<"\n"; return (bool)f; }
bool loadGame(const std::string&path, SaveData& out){
 std::ifstream f(path); if(!f) return false; std::string line,body; SaveData d;
 while(std::getline(f,line)){ if(line.rfind("checksum=",0)==0){
   if(checksum(body)!= (unsigned)std::stoul(line.substr(9))) return false; out=d; return true; }
  body+=line+"\n";
  auto eq=line.find('='); if(eq==std::string::npos) continue;
  std::string k=line.substr(0,eq), v=line.substr(eq+1);
  if(k=="chapter") d.chapter=std::stoi(v); else if(k=="px") d.pos.x=std::stof(v);
  else if(k=="py") d.pos.y=std::stof(v); else if(k=="pz") d.pos.z=std::stof(v);
  else if(k=="yaw") d.yaw=std::stof(v); else if(k=="pitch") d.pitch=std::stof(v); }
 return false; }
}
