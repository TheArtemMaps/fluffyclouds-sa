
#include "Weather.h"

// Map from VCS to SA weather
int CWeather2::weatherMap[8] = { SUNNY_SF, CLOUDY_SF, RAINY_SF, FOGGY_SF, EXTRASUNNY_SF, RAINY_COUNTRYSIDE, EXTRACOLORS_SA, EXTRASUNNY_COUNTRYSIDE };
// Map from SA to VCS weather
int CWeather2::revWeatherMap[23] = {
	EXTRASUNNY_MIAMI,	// LA
	SUNNY_MIAMI,		// LA
	EXTRASUNNY_MIAMI,	// SMOG LA
	SUNNY_MIAMI,		// SMOG LA
	CLOUDY_MIAMI,		// LA
	SUNNY_MIAMI,		//
	EXTRASUNNY_MIAMI,	//
	CLOUDY_MIAMI,		//
	RAINY_MIAMI,		//
	FOGGY_MIAMI,		//
	SUNNY_MIAMI,		// VEGAS
	EXTRASUNNY_MIAMI,	// VEGAS
	CLOUDY_MIAMI,		// VEGAS
	ULTRASUNNY_MIAMI,	//
	SUNNY_MIAMI,		// COUNTRYSIDE
	CLOUDY_MIAMI,		// COUNTRYSIDE
	HURRICANE_MIAMI,	//
	EXTRASUNNY_MIAMI,	// DESERT
	SUNNY_MIAMI,		// DESERT
	HURRICANE_MIAMI,	// SANDSTORM
	SUNNY_MIAMI,		// UNDERWATER
	EXTRACOLORS_MIAMI,	//
	EXTRACOLORS_MIAMI,	// 2
};

// straight out of VCS, mapped to SA weathers by the above map
static uint8_t weatherTypesList[256] = {
	1, 7, 7, 4, 4, 4, 2, 7, 7, 4, 7, 2, 7, 0, 7, 7, 4, 1, 2, 1, 1, 0, 0, 4, 7, 7, 7, 3, 1, 3, 7, 7, 7, 1, 7, 4, 4, 0, 7, 7, 7, 0, 7, 7, 7, 7, 3, 7, 7, 7, 4, 0, 7, 7, 7, 7, 3, 1, 3, 7, 7, 7, 4, 4,
	0, 7, 7, 4, 4, 4, 1, 7, 7, 3, 7, 7, 7, 0, 7, 7, 4, 4, 4, 4, 4, 7, 0, 7, 7, 7, 7, 3, 3, 3, 7, 1, 2, 1, 7, 4, 4, 0, 1, 1, 2, 1, 7, 7, 7, 7, 3, 1, 7, 7, 4, 0, 1, 7, 4, 7, 3, 3, 3, 7, 7, 7, 4, 4,
	0, 1, 2, 1, 4, 4, 7, 7, 7, 3, 7, 7, 7, 7, 7, 7, 0, 4, 4, 4, 4, 0, 7, 7, 7, 7, 7, 3, 3, 3, 7, 7, 7, 7, 7, 4, 4, 7, 7, 0, 7, 7, 1, 2, 2, 1, 3, 7, 7, 0, 0, 4, 7, 7, 7, 7, 1, 3, 3, 0, 7, 7, 4, 4,
	7, 7, 7, 4, 4, 4, 7, 7, 7, 3, 7, 7, 7, 7, 7, 7, 4, 4, 4, 4, 4, 7, 7, 7, 7, 7, 7, 3, 3, 3, 7, 7, 7, 7, 7, 4, 4, 7, 7, 7, 7, 7, 7, 7, 7, 7, 3, 7, 7, 7, 4, 4, 0, 2, 2, 1, 2, 5, 2, 2, 1, 1, 0, 0
};