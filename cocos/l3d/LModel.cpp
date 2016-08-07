#include "LModel.h"

#include "LJoint.h"
#include "LSurface.h"
#include "math/Vec3.h"

NS_CC_BEGIN

LModel::LModel()
{

}

LModel::~LModel()
{

}

LSurface* LModel::AllocSurface()
{
	LSurface* geo = LSurface::Create();
	_surfaces.push_back(geo);
	return geo;
}

void LModel::GenerateNormals()
{
	for (unsigned int i = 0; i < _surfaces.size(); ++i)
	{
		_surfaces[i]->DeriveNormals();
	}
}

void LModel::CalcBounds()
{
	for (unsigned int i = 0; i < _surfaces.size(); ++i)
	{
		//R_BoundTriSurf(_surfaces[i]);
	}
}

typedef struct matchVert_s {
	struct matchVert_s	*next;
	int		v, tv;
	byte	color[4];
	Vec3	normal;
} matchVert_t;

LSurface* LModel::GetSurfaces(int idx)
{
	return _surfaces[idx];
}

int LModel::GetSurfaceCount()
{
	return 0;
}

void LModel::SetJoint(LJoint* root)
{
	//_root = root;
}

LJoint* LModel::GetRootJoint()
{
	return NULL;
	//return _root;
}

void LModel::SetNumFrames(int num)
{
	_numFrames = num;
}

void LModel::BuildDeformInfo()
{
	for (unsigned int i = 0; i < _surfaces.size(); ++i)
	{
		 // R_DeriveNormals(_surfaces[i]);
		 //	R_BoundTriSurf(_surfaces[i]);
		 //	R_CreateSilIndice(_surfaces[i]);
		 //	R_IdentifySilEdges(_surfaces[i])
	}
}

NS_CC_END