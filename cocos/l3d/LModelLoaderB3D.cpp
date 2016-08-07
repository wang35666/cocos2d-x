#include "LModelLoaderB3D.h"
#include "LJoint.h"
#include "LModel.h"
#include "LSurface.h"
#include "LFile.h"

#include "lcommon/LVarSystem.h"

NS_CC_BEGIN

static LVar debugb3d("debugb3d", "0", 0, "");

LModelLoaderB3D::LModelLoaderB3D() 
{
}

LModelLoaderB3D::~LModelLoaderB3D() 
{
}

bool LModelLoaderB3D::Load(const char* file) 
{
	_file = new LFile;
	if( !_file->Open(file) )
		return false;

	_model = new LModel;
	std::string head = ReadChunk();
	int nB3DVersion = _file->ReadInt();

	CCLOG("load b3d file %s, version %s %d\n", file, head.c_str(), nB3DVersion);

	while( CheckSize() ) {
		std::string& t = ReadChunk();
		if (t == "TEXS")
			ReadTexs();
		else if (t == "BRUS")
			ReadBrus();
		else if (t == "NODE")
			_model->SetJoint(ReadNode());

		ExitChunk();
	}

	delete _file;
	_file = NULL;

	// The MESH chunk describes a mesh. 
	// A mesh only has one VRTS chunk, but potentially many TRIS chunks.
	LSurface* tri = _model->GetSurfaces(0);
	tri->numIndices = _indices.size();
	//tri->indices = _indices.pointer();

	tri->indices = new glIndex_t[tri->numIndices];
	memcpy(tri->indices, _indices.data(), tri->numIndices);

	if (debugb3d.getBool())
	{
		CCLOG("model:%s\n"
				"vert %d\n"
				"indice %d", file, _model->GetNumFrames(), _model->GetNumFrames());
	}

	return true;
}

bool LModelLoaderB3D::ReadVrts() 
{
	const int max_tex_coords = 3;
	int flags, tex_coord_sets, tex_coord_set_size;

	flags = _file->ReadInt();
	tex_coord_sets = _file->ReadInt();
	tex_coord_set_size = _file->ReadInt();

	if (tex_coord_sets >= max_tex_coords || tex_coord_set_size >= 4) // Something is wrong 
	{
		CCLOG("tex_coord_sets or tex_coord_set_size too big");
		return false;
	}

	//------ Allocate Memory, for speed -----------//
	int sizeOfVertex = 3;
	bool hasNormal = false;
	bool hasVertexColors = false;
	if (flags & 1) {
		hasNormal = true;
		sizeOfVertex += 3;
	}
	if (flags & 2) {
		sizeOfVertex += 4;
		hasVertexColors=true;
	}

	sizeOfVertex += tex_coord_sets*tex_coord_set_size;
	unsigned int size = _stack[_stack.size() - 1] - _file->Tell();
	//106407 16800
	unsigned int numVertex = size / sizeof(float) ;
	numVertex /= sizeOfVertex;

	LSurface* tri = _model->AllocSurface();
	tri->AllocSurfVerts(numVertex);

	int idx = 0;
	while( CheckSize()) {
		float color[4]={1.0f, 1.0f, 1.0f, 1.0f};
		tri->verts[idx].xyz = _file->ReadVec3();

		if (flags & 1) {
			tri->verts[idx].normal = _file->ReadVec3();
		}
		if (flags & 2) {
			color[0] = _file->ReadFloat();
			color[1] = _file->ReadFloat();
			color[2] = _file->ReadFloat();
			color[3] = _file->ReadFloat();
		}
		float u, v;
		for (int i = 0; i < tex_coord_sets; ++i) {
			//for (int j = 0; j < tex_coord_set_size; ++j)
			{
				u = _file->ReadFloat();
				v = 1.0f - _file->ReadFloat();
			}
		}

		tri->verts[idx].st = Vec2(u, v);
		idx++;
	}

	return true;
}

std::string LModelLoaderB3D::ReadChunk()
{
	std::string s;
	for (int i = 0; i < 4;++i) {
		s += char(_file->ReadChar());
	}
	
	unsigned int size = _file->ReadInt();
	unsigned int pos = _file->Tell();
	_stack.push_back(pos + size);
	return s;
}

bool LModelLoaderB3D::CheckSize()
{
	unsigned int pos = _file->Tell();
	unsigned int size = _stack[_stack.size() - 1];
	return size > pos;
}

void LModelLoaderB3D::ExitChunk()
{
	_curpos = _stack.back();
	_stack.pop_back();
	//_stack.erase(_stack.size() - 1);
}

void LModelLoaderB3D::ReadTexs()
{
	while (CheckSize()) {
		PrintTree("read texs \n");
		SB3dTexture tex;
		tex.TextureName = _file->ReadString();
		tex.Flags = _file->ReadInt();
		tex.Blend = _file->ReadInt();
		tex.Xpos = _file->ReadFloat();
		tex.Ypos = _file->ReadFloat();
		tex.Xscale = _file->ReadFloat();
		tex.Yscale = _file->ReadFloat();
		tex.Angle = _file->ReadFloat();
		_textures.push_back(tex);
	}
}

LJoint* LModelLoaderB3D::ReadNode()
{
	LJoint* joint = new LJoint;

	std::string str = _file->ReadString();
	PrintTree(str.c_str());

	Vec3 t = _file->ReadVec3();
	Vec3 s = _file->ReadVec3();
	Quaternion r = _file->ReadQuat();

	joint->name = str;
	joint->position = t;
	joint->scale = s;
	joint->rotation = r;

	while( CheckSize() ){
		std::string t = ReadChunk();
		if( t=="MESH" ){
			ReadMesh();
		}else if( t=="BONE" ){
			ReadBone(joint);
		}else if( t=="ANIM" ){
			ReadAnim();
		}else if( t=="KEYS" ){
			ReadKey(joint);
		}else if( t=="NODE" ){
			LJoint* child = ReadNode();
			//Sys_Printf("parent %s children %s\n", joint->name.c_str(), child->name.c_str());
			joint->children.push_back(child);
			child->parent = joint;
		}
		ExitChunk();
	}
	return joint;

}

void LModelLoaderB3D::ReadBrus()
{
	int n_texs = _file->ReadInt();
	if( n_texs<0 || n_texs>8 ){
		printf( "Bad texture count" );
	}
	while( CheckSize() ){
		std::string& name = _file->ReadString();
		PrintTree(name.c_str());
		Vec3 color = _file->ReadVec3();
		float alpha = _file->ReadFloat();
		float shiny = _file->ReadFloat();
		/*int blend=**/_file->ReadInt();
		int fx = _file->ReadInt();

		//Textures
		for( int i=0;i<n_texs;++i ){
			int texid= _file->ReadInt();
		}
	}
}

void LModelLoaderB3D::ReadBone( LJoint* joint )
{
	int i = 0;
	while( CheckSize() ){
		int vertex = _file->ReadInt();
		float weight = _file->ReadFloat();
		joint->vertexIndices.push_back(vertex);
		joint->vertexWeights.push_back(weight);
		i++;
	}
	PrintTree("vertex count: %d", i);
}

void LModelLoaderB3D::ReadMesh() {
	/*int matid=*/_file->ReadInt();

	//printTree("mesh");
	while( CheckSize() ){
		std::string& t = ReadChunk();
		if( t=="VRTS" ){
			ReadVrts();
		}else if( t=="TRIS" ){
			ReadTris();
		}
		ExitChunk();
	}
}

void LModelLoaderB3D::PrintTree(const char *psz, ...) {
	//char sBuf[128];
	//va_list ap;
	//va_start(ap, psz);
	//vsnprintf_s(sBuf, 128, 128, psz, ap);
	//va_end(ap);

	//for (int i = 0; i < _stack.size();i++)
	//	Sys_Printf("-");

	//Sys_Printf(sBuf);
	//Sys_Printf("\n");
}

void LModelLoaderB3D::ReadTris(){
	int matid = _file->ReadInt();
	if( matid==-1 ){
		matid=0;
	}
	int size = _stack.back() - _file->Tell();
	int n_tris=size/12;

	for( int i=0;i<n_tris;++i ){
		int i0 = _file->ReadUnsignedInt();
		int i1 = _file->ReadUnsignedInt();
		int i2 = _file->ReadUnsignedInt();

		_indices.push_back(i0);
		_indices.push_back(i1);
		_indices.push_back(i2);
	}
}

void LModelLoaderB3D::ReadAnim(){
	/*int flags=*/_file->ReadInt();
	int frames = _file->ReadInt();
	/*float fps = */_file->ReadFloat();
	_model->SetNumFrames(frames);
}

void LModelLoaderB3D::ReadKey(LJoint* joint)
{
	int flags = _file->ReadInt();
	while( CheckSize() ){
		int frame = _file->ReadInt();
		if (flags & 1){
			PositionKey k;
			k.position = _file->ReadVec3();
			k.frame = frame;
			joint->positionKeys.push_back(k);
		}
		if( flags & 2 ){
			ScaleKey k;
			k.position = _file->ReadVec3();
			k.frame = frame;
			joint->scaleKeys.push_back(k);
		}
		if( flags & 4 ){
			Quaternion r = _file->ReadQuat();
			r.w = -r.w; // fix bug
			RotationKey k;
			k.rotation = r;
			k.frame = frame;
			joint->rotationKeys.push_back(k);
		}
	}
}

LModel* LModelLoaderB3D::GetModel()
{
	return _model;
}

NS_CC_END