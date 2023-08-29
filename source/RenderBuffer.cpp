#include "plugin.h"

#include "RenderBuffer.h"

int32_t TempBufferVerticesStored;
int32_t TempBufferIndicesStored;

RwIm3DVertex TempBufferRenderVertices[TEMPBUFFERVERTSIZE];
RwImVertexIndex TempBufferRenderIndexList[TEMPBUFFERINDEXSIZE];

int RenderBuffer::VerticesToBeStored;
int RenderBuffer::IndicesToBeStored;

void RenderBuffer::ClearRenderBuffer() {
	TempBufferVerticesStored = 0;
	TempBufferIndicesStored = 0;
}

void RenderBuffer::StartStoring(int numIndices, int numVertices, RwImVertexIndex** indexStart, RwIm3DVertex** vertexStart) {
	if (TempBufferIndicesStored + numIndices >= TEMPBUFFERINDEXSIZE)
		RenderStuffInBuffer();
	if (TempBufferVerticesStored + numVertices >= TEMPBUFFERVERTSIZE)
		RenderStuffInBuffer();
	*indexStart = &TempBufferRenderIndexList[TempBufferIndicesStored];
	*vertexStart = &TempBufferRenderVertices[TempBufferVerticesStored];
	IndicesToBeStored = numIndices;
	VerticesToBeStored = numVertices;
}

void RenderBuffer::StopStoring() {
	int i;
	for (i = TempBufferIndicesStored; i < TempBufferIndicesStored + IndicesToBeStored; i++)
		TempBufferRenderIndexList[i] += TempBufferVerticesStored;
	TempBufferIndicesStored += IndicesToBeStored;
	TempBufferVerticesStored += VerticesToBeStored;
}

void RenderBuffer::RenderStuffInBuffer() {
	if (TempBufferVerticesStored && RwIm3DTransform(TempBufferRenderVertices, TempBufferVerticesStored, NULL, rwIM3D_VERTEXUV)) {
		RwIm3DRenderIndexedPrimitive(rwPRIMTYPETRILIST, TempBufferRenderIndexList, TempBufferIndicesStored);
		RwIm3DEnd();
	}
	ClearRenderBuffer();
}
