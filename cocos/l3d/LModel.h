#ifndef __LMODEL_H__
#define __LMODEL_H__

#include <vector>
#include <string>

#include "platform/CCPlatformMacros.h"

NS_CC_BEGIN

class LJoint;
class LSurface;

class CC_DLL LModel
{
public:
	LModel();
	~LModel();

	LSurface* AllocSurface();
	LSurface* GetSurfaces(int idx);
	int GetSurfaceCount();
	void GenerateNormals();
	void CalcBounds();
	void BuildDeformInfo();
	void SetNumFrames(int num);
	int GetNumFrames() { return _numFrames; }

	void SetJoint(LJoint* root);

	LJoint* GetRootJoint();
private:

	std::vector<LSurface*> _surfaces;

	std::string _name;

	int _numFrames;

	LJoint* _root;
};

NS_CC_END

#endif