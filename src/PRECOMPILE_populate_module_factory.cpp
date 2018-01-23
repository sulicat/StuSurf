#include "../include/common.h"
#include "../include/headers.h"

std::map<std::string, std::function<ModuleBase*( int, int, int, int, std::string)> > MODULE_FACTORY;
void common::PRECOMPILE_populate_module_factory(){

	MODULE_FACTORY.insert( std::pair<std::string, std::function<ModuleBase*(int,int,int,int,std::string)> >( "MultiMeter1",	[](int _x, int _y, int _w, int _h, std::string _f){ModuleBase* out = new MultiMeter1(_x, _y, _w, _h); out->setDataFile(_f); return out;} ));
	MODULE_FACTORY.insert( std::pair<std::string, std::function<ModuleBase*(int,int,int,int,std::string)> >( "PinkModule", 	[](int _x, int _y, int _w, int _h, std::string _f){ModuleBase* out = new PinkModule(_x, _y, _w, _h); out->setDataFile(_f); return out;} ));
	MODULE_FACTORY.insert( std::pair<std::string, std::function<ModuleBase*(int,int,int,int,std::string)> >( "TextModule", 	[](int _x, int _y, int _w, int _h, std::string _f){ModuleBase* out = new TextModule(_x, _y, _w, _h); out->setDataFile(_f); return out;} ));
}
