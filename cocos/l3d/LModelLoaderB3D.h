/*
http://www.blitzbasic.com/sdkspecs/sdkspecs/b3dfile_specs.txt
*/

#ifndef __LMODELLOADB3D_H__
#define __LMODELLOADB3D_H__

#include <string>
#include <vector>

#include "platform/CCPlatformMacros.h"

NS_CC_BEGIN

class LJoint;
class LModel;
class LFile;

class CC_DLL LModelLoaderB3D
{
public:
	LModelLoaderB3D();
	~LModelLoaderB3D();

	struct SB3dChunkHeader
	{
		char name[4];
		int size;
	};

	struct SB3dTexture
	{
		std::string TextureName;
		int Flags;
		int Blend;
		float Xpos;
		float Ypos;
		float Xscale;
		float Yscale;
		float Angle;
	};

	struct SB3dMaterial
	{
		SB3dMaterial() : red(1.0f), green(1.0f),
			blue(1.0f), alpha(1.0f), shininess(0.0f), blend(1),
			fx(0)
		{
		//	for (unsigned int i=0; i<3; ++i)
				//Textures[i]=0;
		}
		//video::SMaterial Material;
		float red, green, blue, alpha;
		float shininess;
		int blend, fx;
		//SB3dTexture *Textures[video::MATERIAL_MAX_TEXTURES];
	};

	bool Load(const char* file) ;
	LModel* GetModel();

private:
	void ReadTexs();
	bool ReadVrts();
	LJoint* ReadNode();
	void ReadBrus();
	void ReadBone(LJoint* joint);
	void ReadMesh();
	void ReadTris();
	void ReadAnim();
	void ReadKey(LJoint* joint);

	std::string ReadChunk();
	bool CheckSize();
	void ExitChunk();

	void PrintTree(const char *psz, ...);

	long _curpos;
	std::vector<unsigned int> _stack;
	std::vector<SB3dTexture> _textures;
	std::vector<unsigned short> _indices;

	LFile*  _file;
	LModel* _model;
};

NS_CC_END
#endif
