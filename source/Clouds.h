#pragma once
#include <game_sa/CTimer.h>
class CClouds
{
public:
	static float CloudRotation;
	static uint32_t IndividualRotation;

	static float ms_cameraRoll;
	//static bool FluffyCloudsInvisible;
	static float ms_horizonZ;
	static float ms_HorizonTilt;
	static RwRGBA ms_colourTop;
	static RwRGBA ms_colourBottom;
	static RwRGBA ms_colourBkGrd;
	static void Init(void);
	static void Shutdown(void);
	static void Update(void);
	static void Render(void);
	static float GetDefaultTimeStep(void) { return 50.0f / 30.0f; }
	static float GetTimeStepFix(void) { return CTimer::ms_fTimeStep / GetDefaultTimeStep(); }
};