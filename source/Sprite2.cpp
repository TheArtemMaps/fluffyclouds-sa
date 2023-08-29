#include "plugin.h"
#include "CDraw.h"
#include "CCamera.h"
#include "Sprite2.h"
#include "CScene.h"

#ifdef ASPECT_RATIO_SCALE
#include "Frontend.h"
#endif
using namespace std;

float CSprite2::m_f2DNearScreenZ;
float CSprite2::m_f2DFarScreenZ;
float CSprite2::m_fRecipNearClipPlane;
int32_t CSprite2::m_bFlushSpriteBufferSwitchZTest;

#define SPRITEBUFFERSIZE 64
static int32_t nSpriteBufferIndex;
static RwIm2DVertex SpriteBufferVerts[SPRITEBUFFERSIZE*6];
static RwIm2DVertex verts[4];

void
CSprite2::InitSpriteBuffer(void)
{
	m_f2DNearScreenZ = CDraw::ms_fNearClipZ;
	m_f2DFarScreenZ = CDraw::ms_fFarClipZ;
}

void
CSprite2::FlushSpriteBuffer(void)
{
	if(nSpriteBufferIndex > 0){
		if(m_bFlushSpriteBufferSwitchZTest){
			RwRenderStateSet(rwRENDERSTATEZTESTENABLE, (void*)FALSE);
			RwIm2DRenderPrimitive(rwPRIMTYPETRILIST, SpriteBufferVerts, nSpriteBufferIndex*6);
			RwRenderStateSet(rwRENDERSTATEZTESTENABLE, (void*)TRUE);
		}else
			RwIm2DRenderPrimitive(rwPRIMTYPETRILIST, SpriteBufferVerts, nSpriteBufferIndex*6);
		nSpriteBufferIndex = 0;
	}
}

void
CSprite2::RenderBufferedOneXLUSprite_Rotate_Aspect(float x, float y, float z, float w, float h, uint8_t r, uint8_t g, uint8_t b, int16_t intens, float recipz, float rotation, uint8_t a)
{
	m_bFlushSpriteBufferSwitchZTest = 0;
	float c = cos(rotation);
	float s = sin(rotation);

	float xs[4];
	float ys[4];
	float us[4];
	float vs[4];
	int i;

	xs[0] = x + w * (-c - s);	us[0] = 0.0f;
	xs[1] = x + w * (-c + s);	us[1] = 0.0f;
	xs[2] = x + w * (+c + s);	us[2] = 1.0f;
	xs[3] = x + w * (+c - s);	us[3] = 1.0f;

	ys[0] = y + h * (-c + s);	vs[0] = 0.0f;
	ys[1] = y + h * (+c + s);	vs[1] = 1.0f;
	ys[2] = y + h * (+c - s);	vs[2] = 1.0f;
	ys[3] = y + h * (-c - s);	vs[3] = 0.0f;

	// No clipping, just culling
	if (xs[0] < 0.0f && xs[1] < 0.0f && xs[2] < 0.0f && xs[3] < 0.0f) return;
	if (ys[0] < 0.0f && ys[1] < 0.0f && ys[2] < 0.0f && ys[3] < 0.0f) return;
	if (xs[0] > SCREEN_WIDTH && xs[1] > SCREEN_WIDTH &&
		xs[2] > SCREEN_WIDTH && xs[3] > SCREEN_WIDTH) return;
	if (ys[0] > SCREEN_HEIGHT && ys[1] > SCREEN_HEIGHT &&
		ys[2] > SCREEN_HEIGHT && ys[3] > SCREEN_HEIGHT) return;

	float screenz = m_f2DNearScreenZ +
		(z - CDraw::ms_fNearClipZ) * (m_f2DFarScreenZ - m_f2DNearScreenZ) * CDraw::ms_fFarClipZ /
		((CDraw::ms_fFarClipZ - CDraw::ms_fNearClipZ) * z);

	RwIm2DVertex* vert = &SpriteBufferVerts[nSpriteBufferIndex * 6];
	static int indices[6] = { 0, 1, 2, 3, 0, 2 };
	for (i = 0; i < 6; i++) {
		RwIm2DVertexSetScreenX(&vert[i], xs[indices[i]]);
		RwIm2DVertexSetScreenY(&vert[i], ys[indices[i]]);
		RwIm2DVertexSetScreenZ(&vert[i], screenz);
		RwIm2DVertexSetCameraZ(&vert[i], z);
		RwIm2DVertexSetRecipCameraZ(&vert[i], recipz);
		RwIm2DVertexSetIntRGBA(&vert[i], r * intens >> 8, g * intens >> 8, b * intens >> 8, a);
		RwIm2DVertexSetU(&vert[i], us[indices[i]], recipz);
		RwIm2DVertexSetV(&vert[i], vs[indices[i]], recipz);
	}
	nSpriteBufferIndex++;
	if (nSpriteBufferIndex >= SPRITEBUFFERSIZE)
		FlushSpriteBuffer();
}

void
CSprite2::RenderBufferedOneXLUSprite_Rotate_2Colours(float x, float y, float z, float w, float h, uint8_t r1, uint8_t g1, uint8_t b1, uint8_t r2, uint8_t g2, uint8_t b2, float cx, float cy, float recipz, float rotation, uint8_t a)
{
	m_bFlushSpriteBufferSwitchZTest = 0;
	float c = cos(rotation);
	float s = sin(rotation);

	float xs[4];
	float ys[4];
	float us[4];
	float vs[4];
	float cf[4];
	int i;

	xs[0] = x + w * (-c - s);	us[0] = 0.0f;
	xs[1] = x + w * (-c + s);	us[1] = 0.0f;
	xs[2] = x + w * (+c + s);	us[2] = 1.0f;
	xs[3] = x + w * (+c - s);	us[3] = 1.0f;

	ys[0] = y + h * (-c + s);	vs[0] = 0.0f;
	ys[1] = y + h * (+c + s);	vs[1] = 1.0f;
	ys[2] = y + h * (+c - s);	vs[2] = 1.0f;
	ys[3] = y + h * (-c - s);	vs[3] = 0.0f;

	// No clipping, just culling
	if (xs[0] < 0.0f && xs[1] < 0.0f && xs[2] < 0.0f && xs[3] < 0.0f) return;
	if (ys[0] < 0.0f && ys[1] < 0.0f && ys[2] < 0.0f && ys[3] < 0.0f) return;
	if (xs[0] > SCREEN_WIDTH && xs[1] > SCREEN_WIDTH &&
		xs[2] > SCREEN_WIDTH && xs[3] > SCREEN_WIDTH) return;
	if (ys[0] > SCREEN_HEIGHT && ys[1] > SCREEN_HEIGHT &&
		ys[2] > SCREEN_HEIGHT && ys[3] > SCREEN_HEIGHT) return;

	// Colour factors, cx/y is the direction in which colours change from rgb1 to rgb2
	cf[0] = (cx * (-c - s) + cy * (-c + s)) * 0.5f + 0.5f;
	cf[0] = clamp(cf[0], 0.0f, 1.0f);
	cf[1] = (cx * (-c + s) + cy * (c + s)) * 0.5f + 0.5f;
	cf[1] = clamp(cf[1], 0.0f, 1.0f);
	cf[2] = (cx * (c + s) + cy * (c - s)) * 0.5f + 0.5f;
	cf[2] = clamp(cf[2], 0.0f, 1.0f);
	cf[3] = (cx * (c - s) + cy * (-c - s)) * 0.5f + 0.5f;
	cf[3] = clamp(cf[3], 0.0f, 1.0f);

	float screenz = m_f2DNearScreenZ +
		(z - CDraw::ms_fNearClipZ) * (m_f2DFarScreenZ - m_f2DNearScreenZ) * CDraw::ms_fFarClipZ /
		((CDraw::ms_fFarClipZ - CDraw::ms_fNearClipZ) * z);

	RwIm2DVertex* vert = &SpriteBufferVerts[nSpriteBufferIndex * 6];
	static int indices[6] = { 0, 1, 2, 3, 0, 2 };
	for (i = 0; i < 6; i++) {
		RwIm2DVertexSetScreenX(&vert[i], xs[indices[i]]);
		RwIm2DVertexSetScreenY(&vert[i], ys[indices[i]]);
		RwIm2DVertexSetScreenZ(&vert[i], screenz);
		RwIm2DVertexSetCameraZ(&vert[i], z);
		RwIm2DVertexSetRecipCameraZ(&vert[i], recipz);
		RwIm2DVertexSetIntRGBA(&vert[i],
			r1 * cf[indices[i]] + r2 * (1.0f - cf[indices[i]]),
			g1 * cf[indices[i]] + g2 * (1.0f - cf[indices[i]]),
			b1 * cf[indices[i]] + b2 * (1.0f - cf[indices[i]]),
			a);
		RwIm2DVertexSetU(&vert[i], us[indices[i]], recipz);
		RwIm2DVertexSetV(&vert[i], vs[indices[i]], recipz);
	}
	nSpriteBufferIndex++;
	if (nSpriteBufferIndex >= SPRITEBUFFERSIZE)
		FlushSpriteBuffer();
}
