#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4244)	// int to float
#pragma warning(disable: 4800)	// int to bool
#pragma warning(disable: 4838)  // narrowing conversion
#pragma warning(disable: 4305)  // truncation from 'double' to 'float'
#pragma once
#include <windows.h>
#include <stdio.h>
#include <math.h>
#include <rw/rwcore.h>
#include "MemoryMgr.h"
#include "CVector.h"

// when this is defined, the whole TimeCycle is replaced,
// not just patched to use 24 hours
#define REPLACE

typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef uint8_t uint8;
typedef int16_t int16;
typedef int32_t int32;

#define NUMWEATHERS 23
#define NUMHOURS 24
#define EXTRASTART 21

struct sus
{
	RwMatrix sus2;
	RwMatrix *sus3;
	int haveRwMatrix2;
};


class CFileLoader
{
public:
	static char *LoadLine(int fd);
};

//struct CTimer
//{
//	static float &ms_fTimeStep;
//};

//struct CClock
//{
//	static ushort &ms_nGameClockSeconds;
//	static uchar  &ms_nGameClockMinutes;
//	static uchar  &ms_nGameClockHours;
//};

//struct CWeather
	//{
	//	static short &OldWeatherType;
	//	static short &NewWeatherType;
	//	static float &InterpolationValue;
	//	static float &UnderWaterness;
	//	static float &InTunnelness;
	//	static bool &bScriptsForceRain;
	//};

//struct CCoronas
	//{
	//	static float &LightsMult;
	//};

//struct CCullZones
//{
	//static bool PlayerNoRain(void);
	//static bool CamNoRain(void);
//};

//struct CCutsceneMgr
//{
	//static bool &ms_running;
//};


void CShadows__CalcPedShadowValues(float x, float y, float z, float* sfx, float* sfy, float* ssx, float* ssy, float* sdx, float* sdy);

//#include "ColourSet.h"
//#include "TimeCycle.h"
