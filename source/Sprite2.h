#pragma once

class CSprite2
{
	static float m_f2DNearScreenZ;
	static float m_f2DFarScreenZ;
	static float m_fRecipNearClipPlane;
	static int32_t m_bFlushSpriteBufferSwitchZTest;
public:
	static void FlushSpriteBuffer(void);
	static void InitSpriteBuffer(void);
	static void RenderBufferedOneXLUSprite_Rotate_Aspect(float x, float y, float z, float w, float h, uint8_t r, uint8_t g, uint8_t b, int16_t intens, float recipz, float roll, uint8_t a);
	static void RenderBufferedOneXLUSprite_Rotate_2Colours(float x, float y, float z, float w, float h, uint8_t r1, uint8_t g1, uint8_t b1, uint8_t r2, uint8_t g2, uint8_t b2, float cx, float cy, float recipz, float rotation, uint8_t a);
};