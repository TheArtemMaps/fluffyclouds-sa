#pragma once
#include "extensions/Screen.h"
#include "CRect.h"
#include "CPad.h"
#include "CDraw.h"
#include "CVector.h"

static float DotProduct(const CVector& v1, const CVector& v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

static float DotProduct2D(const CVector2D& v1, const CVector2D& v2) {
    return v1.x * v2.x + v1.y * v2.y;
}

static float CrossProduct2D(const CVector2D& v1, const CVector2D& v2) {
    return v1.x * v2.y - v1.y * v2.x;
}

static float Distance2D(const CVector2D& v, float x, float y) {
    return sqrt((v.x - x) * (v.x - x) + (v.y - y) * (v.y - y));
}

static float DistanceSqr2D(const CVector2D& v, float x, float y) {
    return (v.x - x) * (v.x - x) + (v.y - y) * (v.y - y);
}

#define SQR(x) ((x) * (x))

static int32_t GetRandomNumber() {
    return rand() & RAND_MAX;
}

static RwTexture* RwTextureRead(const char* name, const char* mask) {
    return plugin::CallAndReturn<RwTexture*, 0x07F3AC0>(name, mask);
}
