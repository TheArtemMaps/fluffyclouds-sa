#include "plugin.h"

#include "Clouds.h"

using namespace plugin;
plugin::ThiscallEvent<AddressList<0x53EAD3, H_CALL>, PRIORITY_BEFORE, ArgPickNone, void()> movingThingsEvent;

class FluffyCloudsSA {
public:
    FluffyCloudsSA() {
        plugin::Events::initGameEvent += []() {
            CClouds::Init();
        };

        plugin::Events::gameProcessEvent += []() {
            CClouds::Update();
        };

        movingThingsEvent += []() {
            CClouds::Render();
        };

        plugin::Events::shutdownRwEvent += []() {
            CClouds::Shutdown();
        };
    }
} FluffyCloudsSA;
