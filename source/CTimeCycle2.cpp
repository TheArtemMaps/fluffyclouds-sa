#include "CTimeCycle2.h"
#include "plugin.h"
#include "CClock.h"
#include "CWeather.h"
#include "O:\re3-reVC_1.0\re3-reVC_1.0\src\core\config.h"
uint8_t CTimeCycle2::m_nFluffyCloudsTopRed[NUMHOURS][NUMWEATHERS];
uint8_t CTimeCycle2::m_nFluffyCloudsTopGreen[NUMHOURS][NUMWEATHERS];
uint8_t CTimeCycle2::m_nFluffyCloudsTopBlue[NUMHOURS][NUMWEATHERS];
uint8_t CTimeCycle2::m_nFluffyCloudsBottomRed[NUMHOURS][NUMWEATHERS];
uint8_t CTimeCycle2::m_nFluffyCloudsBottomGreen[NUMHOURS][NUMWEATHERS];
uint8_t CTimeCycle2::m_nFluffyCloudsBottomBlue[NUMHOURS][NUMWEATHERS];

int32_t CTimeCycle2::m_nCurrentFluffyCloudsTopRed;
int32_t CTimeCycle2::m_nCurrentFluffyCloudsTopGreen;
int32_t CTimeCycle2::m_nCurrentFluffyCloudsTopBlue;
int32_t CTimeCycle2::m_nCurrentFluffyCloudsBottomRed;
int32_t CTimeCycle2::m_nCurrentFluffyCloudsBottomGreen;
int32_t CTimeCycle2::m_nCurrentFluffyCloudsBottomBlue;

void
CTimeCycle2::Initialise(void) {
	int w, h;

	for (w = 0; w < NUMWEATHERS; w++)
		for (h = 0; h < NUMHOURS; h++) {
			}


	int fluffyTopR, fluffyTopG, fluffyTopB;
	int fluffyBotR, fluffyBotG, fluffyBotB;

	&fluffyTopR, & fluffyTopG, & fluffyTopB,
		&fluffyBotR, & fluffyBotG, & fluffyBotB,
		m_nFluffyCloudsTopRed[h][w] = fluffyTopR;
	m_nFluffyCloudsTopGreen[h][w] = fluffyTopG;
	m_nFluffyCloudsTopBlue[h][w] = fluffyTopB;
	m_nFluffyCloudsBottomRed[h][w] = fluffyBotR;
	m_nFluffyCloudsBottomGreen[h][w] = fluffyBotG;
	m_nFluffyCloudsBottomBlue[h][w] = fluffyBotB;
}

static float interp_c0, interp_c1, interp_c2, interp_c3;

float CTimeCycle2::Interpolate(int8_t* a, int8_t* b)
{
	return a[CWeather::OldWeatherType] * interp_c0 +
		b[CWeather::OldWeatherType] * interp_c1 +
		a[CWeather::NewWeatherType] * interp_c2 +
		b[CWeather::NewWeatherType] * interp_c3;
}

float CTimeCycle2::Interpolate(uint8_t* a, uint8_t* b)
{
	return a[CWeather::OldWeatherType] * interp_c0 +
		b[CWeather::OldWeatherType] * interp_c1 +
		a[CWeather::NewWeatherType] * interp_c2 +
		b[CWeather::NewWeatherType] * interp_c3;
}

float CTimeCycle2::Interpolate(int16_t* a, int16_t* b)
{
	return a[CWeather::OldWeatherType] * interp_c0 +
		b[CWeather::OldWeatherType] * interp_c1 +
		a[CWeather::NewWeatherType] * interp_c2 +
		b[CWeather::NewWeatherType] * interp_c3;
}

void
CTimeCycle2::Update(void) {

	int h1 = CClock::ms_nGameClockHours;
	int h2 = (h1 + 1) % 24;
	int w1 = CWeather::OldWeatherType;
	int w2 = CWeather::NewWeatherType;
#define INTERP(v) Interpolate(v[h1], v[h2])
#define INTERPscl(extra,scl,cur) (m_ExtraColourInter*extra[m_ExtraColour][WEATHER_EXTRACOLOURS]/scl + (1.0f-m_ExtraColourInter)*cur)
	m_nCurrentFluffyCloudsTopRed = INTERP(m_nFluffyCloudsTopRed, m_nCurrentFluffyCloudsTopRed);
	m_nCurrentFluffyCloudsTopGreen = INTERP(m_nFluffyCloudsTopGreen, m_nCurrentFluffyCloudsTopGreen);
	m_nCurrentFluffyCloudsTopBlue = INTERP(m_nFluffyCloudsTopBlue, m_nCurrentFluffyCloudsTopBlue);

	m_nCurrentFluffyCloudsTopRed = INTERP(m_nFluffyCloudsTopRed);
	m_nCurrentFluffyCloudsTopGreen = INTERP(m_nFluffyCloudsTopGreen);
	m_nCurrentFluffyCloudsTopBlue = INTERP(m_nFluffyCloudsTopBlue);

	m_nCurrentFluffyCloudsBottomRed = INTERP(m_nFluffyCloudsBottomRed);
	m_nCurrentFluffyCloudsBottomGreen = INTERP(m_nFluffyCloudsBottomGreen);
	m_nCurrentFluffyCloudsBottomBlue = INTERP(m_nFluffyCloudsBottomBlue);
	m_nCurrentFluffyCloudsBottomRed = INTERP(m_nFluffyCloudsBottomRed, m_nCurrentFluffyCloudsBottomRed);
	m_nCurrentFluffyCloudsBottomGreen = INTERP(m_nFluffyCloudsBottomGreen, m_nCurrentFluffyCloudsBottomGreen);
	m_nCurrentFluffyCloudsBottomBlue = INTERP(m_nFluffyCloudsBottomBlue, m_nCurrentFluffyCloudsBottomBlue);

	m_nCurrentFluffyCloudsBottomRed = INTERP(m_nFluffyCloudsBottomRed, m_nCurrentFluffyCloudsBottomRed);
	m_nCurrentFluffyCloudsBottomGreen = INTERP(m_nFluffyCloudsBottomGreen, m_nCurrentFluffyCloudsBottomGreen);
	m_nCurrentFluffyCloudsBottomBlue = INTERP(m_nFluffyCloudsBottomBlue, m_nCurrentFluffyCloudsBottomBlue);
#undef INTERP
#undef INTERPscl
}