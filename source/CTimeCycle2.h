#pragma once
#include <cstdint>
#include "plugin.h"
#include "O:\re3-reVC_1.0\re3-reVC_1.0\src\core\config.h"
class CTimeCycle2 {
	static uint8_t m_nFluffyCloudsTopRed[NUMHOURS][NUMWEATHERS];
	static uint8_t m_nFluffyCloudsTopGreen[NUMHOURS][NUMWEATHERS];
	static uint8_t m_nFluffyCloudsTopBlue[NUMHOURS][NUMWEATHERS];
	static uint8_t m_nFluffyCloudsBottomRed[NUMHOURS][NUMWEATHERS];
	static uint8_t m_nFluffyCloudsBottomGreen[NUMHOURS][NUMWEATHERS];
	static uint8_t m_nFluffyCloudsBottomBlue[NUMHOURS][NUMWEATHERS];

	static int32_t m_nCurrentFluffyCloudsTopRed;
	static int32_t m_nCurrentFluffyCloudsTopGreen;
	static int32_t m_nCurrentFluffyCloudsTopBlue;
	static int32_t m_nCurrentFluffyCloudsBottomRed;
	static int32_t m_nCurrentFluffyCloudsBottomGreen;
	static int32_t m_nCurrentFluffyCloudsBottomBlue;
	static float Interpolate(int8_t* a, int8_t* b);
	static float Interpolate(uint8_t* a, uint8_t* b);
	static float Interpolate(int16_t* a, int16_t* b);

public:
	static void Initialise(void);
	static void Update(void);
	static int32_t GetFluffyCloudsTopRed(void) { return m_nCurrentFluffyCloudsTopRed; }
	static int32_t GetFluffyCloudsTopGreen(void) { return m_nCurrentFluffyCloudsTopGreen; }
	static int32_t GetFluffyCloudsTopBlue(void) { return m_nCurrentFluffyCloudsTopBlue; }
	static int32_t GetFluffyCloudsBottomRed(void) { return m_nCurrentFluffyCloudsBottomRed; }
	static int32_t GetFluffyCloudsBottomGreen(void) { return m_nCurrentFluffyCloudsBottomGreen; }
	static int32_t GetFluffyCloudsBottomBlue(void) { return m_nCurrentFluffyCloudsBottomBlue; }
};