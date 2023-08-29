#pragma once

class CClouds
{
public:
	static float CloudRotation;
	static uint32_t IndividualRotation;

	static float ms_cameraRoll;
	static float ms_horizonZ;
	static float ms_HorizonTilt;
	static CRGBA ms_colourTop;
	static CRGBA ms_colourBottom;
	static CRGBA ms_colourBkGrd;

	static void Init(void);
	static void Shutdown(void);
	static void Update(void);
	static void Render(void);
};
