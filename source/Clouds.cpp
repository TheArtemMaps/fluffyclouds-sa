#include "plugin.h"

#include "CGeneral.h"
#include "CTimer.h"
#include "CWeather.h"
#include "CCamera.h"
#include "CWorld.h"
#include "CVehicle.h"
#include "CTxdStore.h"
#include "CVector.h"


#include "Clouds.h"

#include "Utility.h"
#include "CGame.h"
#include "CCoronas.h"
#include "CClock.h"
#include "Sprite2.h"
#include "CSprite.h"


RwTexture* gpCloudTex[5];

CRGBA CClouds::ms_colourTop;
CRGBA CClouds::ms_colourBottom;
//bool CClouds::FluffyCloudsInvisible;
//int32_t fluffyalpha2 = 160 * (1.0f - max(CWeather::Foggyness, CWeather::ExtraSunnyness));
float CClouds::ms_cameraRoll;
float CClouds::CloudRotation;
uint32_t CClouds::IndividualRotation;
void
CClouds::Init(void)
{
	CTxdStore::PushCurrentTxd();
	int32_t fluffycloud = CTxdStore::AddTxdSlot("fluffycloudsSA");
	CTxdStore::LoadTxd(fluffycloud, "MODELS\\FLUFFYCLOUDSSA.TXD");
	int32_t slotfluff = CTxdStore::FindTxdSlot("fluffycloudsSA");
	CTxdStore::SetCurrentTxd(slotfluff);
	gpCloudTex[0] = RwTextureRead("cloud1", NULL);
	gpCloudTex[1] = RwTextureRead("cloud2", NULL);
	gpCloudTex[2] = RwTextureRead("cloud3", NULL);
	gpCloudTex[3] = RwTextureRead("cloudmasked", NULL);
	gpCloudTex[4] = RwTextureRead("cloudhilit", NULL);
	CTxdStore::PopCurrentTxd();
	//fluffyalpha2 = 160;
	CloudRotation = 0.0f;
	//FluffyCloudsInvisible = false;
}

void
CClouds::Shutdown(void)
{
	RwTextureDestroy(gpCloudTex[0]);
	gpCloudTex[0] = NULL;
	RwTextureDestroy(gpCloudTex[1]);
	gpCloudTex[1] = NULL;
	RwTextureDestroy(gpCloudTex[2]);
	gpCloudTex[2] = NULL;
	RwTextureDestroy(gpCloudTex[3]);
	gpCloudTex[3] = NULL;
	RwTextureDestroy(gpCloudTex[4]);
	gpCloudTex[4] = NULL;
}

void
CClouds::Update(void)
{
	float s = sin(TheCamera.m_fOrientation - 0.85f);
	CloudRotation += CWeather::Wind * s * 0.001f * CTimer::ms_fOldTimeStep;
	IndividualRotation += (CWeather::Wind * CTimer::ms_fTimeStep * 0.5f + 0.3f * CTimer::ms_fOldTimeStep) * 60.0f;
	/*if (FluffyCloudsInvisible) {
		fluffyalpha2 -= 5;
		if (fluffyalpha2 < 0)
			fluffyalpha2 = 0;
	}
	else {
		fluffyalpha2 += 5;
		if (fluffyalpha2 > 160)
			fluffyalpha = 160;
	}*/
}

float CoorsOffsetX[37] = {
	0.0f, 60.0f, 72.0f, 48.0f, 21.0f, 12.0f,
	9.0f, -3.0f, -8.4f, -18.0f, -15.0f, -36.0f,
	-40.0f, -48.0f, -60.0f, -24.0f, 100.0f, 100.0f,
	100.0f, 100.0f, 100.0f, 100.0f, 100.0f, 100.0f,
	100.0f, 100.0f, -30.0f, -20.0f, 10.0f, 30.0f,
	0.0f, -100.0f, -100.0f, -100.0f, -100.0f, -100.0f, -100.0f
};
float CoorsOffsetY[37] = {
	100.0f, 100.0f, 100.0f, 100.0f, 100.0f, 100.0f,
	100.0f, 100.0f, 100.0f, 100.0f, 100.0f, 100.0f,
	100.0f, 100.0f, 100.0f, 100.0f, -30.0f, 10.0f,
	-25.0f, -5.0f, 28.0f, -10.0f, 10.0f, 0.0f,
	15.0f, 40.0f, -100.0f, -100.0f, -100.0f, -100.0f,
	-100.0f, -40.0f, -20.0f, 0.0f, 10.0f, 30.0f, 35.0f
};
float CoorsOffsetZ[37] = {
	2.0f, 1.0f, 0.0f, 0.3f, 0.7f, 1.4f,
	1.7f, 0.24f, 0.7f, 1.3f, 1.6f, 1.0f,
	1.2f, 0.3f, 0.7f, 1.4f, 0.0f, 0.1f,
	0.5f, 0.4f, 0.55f, 0.75f, 1.0f, 1.4f,
	1.7f, 2.0f, 2.0f, 2.3f, 1.9f, 2.4f,
	2.0f, 2.0f, 1.5f, 1.2f, 1.7f, 1.5f, 2.1f
};

uint8_t BowRed[6] = { 30, 30, 30, 10, 0, 15 };
uint8_t BowGreen[6] = { 0, 15, 30, 30, 0, 0 };
uint8_t BowBlue[6] = { 0, 0, 0, 10, 30, 30 };


void
CClouds::Render(void)
{
	CSprite2::InitSpriteBuffer();
	//fluffy clouds
	if (!CGame::CanSeeOutSideFromCurrArea())
		return;

	CCoronas::SunBlockedByClouds = false;
	int i;
	float szx, szy;
	RwV3d screenpos;
	RwV3d worldpos;

	CVector campos = TheCamera.GetPosition();
	float rot_sin = sin(CloudRotation);
	float rot_cos = cos(CloudRotation);
	int fluffyalpha = 160 * (1.0f - max(CWeather::Foggyness, CWeather::ExtraSunnyness));
	if (fluffyalpha != 0) {
		static bool bCloudOnScreen[37];
		float sundist, hilight;
		RwRenderStateSet(rwRENDERSTATESRCBLEND, (void*)rwBLENDSRCALPHA);
		RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void*)rwBLENDINVSRCALPHA);
		RwRenderStateSet(rwRENDERSTATETEXTURERASTER, RwTextureGetRaster(gpCloudTex[3]));
		for (i = 0; i < 37; i++) {
			RwV3d pos = { 2.0f * CoorsOffsetX[i], 2.0f * CoorsOffsetY[i], 40.0f * CoorsOffsetZ[i] + 40.0f };
			worldpos.x = pos.x * rot_cos + pos.y * rot_sin + campos.x;
			worldpos.y = pos.x * rot_sin - pos.y * rot_cos + campos.y;
			worldpos.z = pos.z;

			if (CSprite::CalcScreenCoors(worldpos, &screenpos, &szx, &szy, false, false)) {
				sundist = sqrt(SQR(screenpos.x - CCoronas::SunScreenX) + SQR(screenpos.y - CCoronas::SunScreenY));
				int tr = ms_colourTop.r = 160;
				int tg = ms_colourTop.g = 160;
				int tb = ms_colourTop.b = 160;
				int br = ms_colourBottom.r = 0;
				int bg = ms_colourBottom.g = 0;
				int bb = ms_colourBottom.b = 0;

					int distLimit = (3 * SCREEN_WIDTH) / 4;
				if (sundist < distLimit) {
					hilight = (1.0f - max(CWeather::Foggyness, CWeather::CloudCoverage)) * (1.0f - sundist / (float)distLimit);
					tr = tr * (1.0f - hilight) + 255 * hilight;
					tg = tg * (1.0f - hilight) + 190 * hilight;
					tb = tb * (1.0f - hilight) + 190 * hilight;
					br = br * (1.0f - hilight) + 255 * hilight;
					bg = bg * (1.0f - hilight) + 190 * hilight;
					bb = bb * (1.0f - hilight) + 190 * hilight;
					if (sundist < SCREEN_WIDTH / 10)
						CCoronas::SunBlockedByClouds = true;
				}
				else
					hilight = 0.0f;
				CSprite2::RenderBufferedOneXLUSprite_Rotate_2Colours(screenpos.x, screenpos.y, screenpos.z,
					szx * 55.0f, szy * 55.0f,
					tr, tg, tb, br, bg, bb, 0.0f, -1.0f,
					1.0f / screenpos.z,
					(uint16_t)IndividualRotation / 65336.0f * 6.28f + ms_cameraRoll,
					fluffyalpha);
				bCloudOnScreen[i] = true;
			}
			else
				bCloudOnScreen[i] = false;
		}
		CSprite2::FlushSpriteBuffer();

		// Highlights
		RwRenderStateSet(rwRENDERSTATESRCBLEND, (void*)rwBLENDONE);
		RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void*)rwBLENDONE);
		RwRenderStateSet(rwRENDERSTATETEXTURERASTER, RwTextureGetRaster(gpCloudTex[4]));


		for (i = 0; i < 37; i++) {
			RwV3d pos = { 2.0f * CoorsOffsetX[i], 2.0f * CoorsOffsetY[i], 40.0f * CoorsOffsetZ[i] + 40.0f };
			worldpos.x = pos.x * rot_cos + pos.y * rot_sin + campos.x;
			worldpos.y = pos.x * rot_sin + pos.y * rot_cos + campos.y;
			worldpos.z = pos.z;
			if (bCloudOnScreen[i] && CSprite::CalcScreenCoors(worldpos, &screenpos, &szx, &szy, false, false)) {
				if (sundist < SCREEN_WIDTH / 3) {
					CSprite2::RenderBufferedOneXLUSprite_Rotate_Aspect(screenpos.x, screenpos.y, screenpos.z,
						szx * 30.0f, szy * 30.0f,
						200 * hilight, 0, 0, 255, 1.0f / screenpos.z,
						1.7f - CGeneral::GetATanOfXY(screenpos.x - CCoronas::SunScreenX, screenpos.y - CCoronas::SunScreenY) + CClouds::ms_cameraRoll, 255);
				}
			}
		}
		CSprite2::FlushSpriteBuffer();
	}
}

