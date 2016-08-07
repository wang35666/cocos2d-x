#ifndef __LSURFACE_H__
#define __LSURFACE_H__

#include "math/Vec2.h"
#include "math/Vec3.h"

typedef unsigned short glIndex_t;

NS_CC_BEGIN


class CC_DLL LDrawVert
{
public:
	LDrawVert() {
		Clear();
	}

	Vec3	xyz;
	Vec2	st;
	Vec3	normal;
	Vec3	tangents[2];
	float   color[4];

	void Clear(void);
};

inline void LDrawVert::Clear()
{
	xyz.setZero();
	st.setZero();
	normal.setZero();
	tangents[0].setZero();
	tangents[1].setZero();
	color[0] = color[1] = color[2] = 0;
	color[3] = 1.0;
}

class CC_DLL LSurface
{
public:
	static LSurface* Create();

	LSurface(){}
	~LSurface() {}
	
	void AllocSurfVerts(int num);

	Vec3* basePoses;

	int	numVerts;
	LDrawVert* verts;

	int	numIndices;
	glIndex_t* indices;

	glIndex_t*	silIndices;
	
	// edges
	bool pickUp;
	int numSilEdges;

	// vbo
	//GLuint vbo[2];

	// pick
	int numPickIndices;
	glIndex_t* pickIndices;

	// draw
	glIndex_t drawBegin;
	glIndex_t drawCount;

	// 
	bool generateNormals;
	bool tangentsCalculated;
	bool facePlanesCalculated;
	bool perfectHull;
	bool calcShadow;
	bool bDrawSingleEdge;

public:
	void DeriveNormals();

	void BoundTriSurf();

	void CreateSilIndice();
};

NS_CC_END

#endif