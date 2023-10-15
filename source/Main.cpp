
#include "plugin.h"
#include "Clouds.h"
//#include "debugmenu_public.h"
//DebugMenuAPI gDebugMenuAPI;
using namespace plugin;
plugin::ThiscallEvent<AddressList<0x7178F0, H_CALL>, PRIORITY_BEFORE, ArgPickNone, void()> movingThingsEvent;

class FluffyCloudsSA {
public:
	FluffyCloudsSA() {
		plugin::Events::initRwEvent += []() {
			CClouds::Init();
		};

		plugin::Events::gameProcessEvent += []() {
			CClouds::Update();
		};
		/*if (DebugMenuLoad()) {
			DebugMenuAddVarBool8("Rendering", "Fluffy clouds invisible", (int8_t*)&CClouds::FluffyCloudsInvisible, NULL);
		}*/
		movingThingsEvent += []() {
			CClouds::Render();
		};

		plugin::Events::shutdownRwEvent += []() {
			CClouds::Shutdown();
		};
	}
} FluffyCloudsSA;
