#ifndef __LJOINT_H__
#define __LJOINT_H__

#include <string>
#include <vector>

#include "math/Mat4.h"
#include "math/Vec3.h"
#include "math/Quaternion.h"

NS_CC_BEGIN

struct PositionKey
{
	Vec3 position;
	float frame;
};

struct ScaleKey
{
	Vec3 position;
	float frame;
};

struct RotationKey
{
	Quaternion rotation;
	float frame;
};

class LJoint
{
public:
	LJoint();
	~LJoint();

	std::string name;
	Vec3 position;
	Vec3 scale;
	Quaternion rotation;
	std::vector<LJoint*> children;
	LJoint* parent;

	std::vector<PositionKey> positionKeys;
	std::vector<RotationKey> rotationKeys;
	std::vector<ScaleKey>    scaleKeys;
	std::vector<int>         vertexIndices;
	std::vector<float>       vertexWeights;

	Mat4 globalAnimatedMatrix;
	Mat4 globalInvMatrix;

	Mat4 globalPosition;

	void GetPositionKeyFramesAtFrame(float frame, PositionKey* preKey, PositionKey* nextKey);
	void GetScaleKeyFramesAtFrame(float frame, ScaleKey* preKey, ScaleKey* nextKey);
	void GetRotationKeyFramesAtFrame(float frame, RotationKey* preKey, RotationKey* nextKey);
	void GetFrame(float frame, Vec3& position, Quaternion& rotation);
}; 

NS_CC_END

#endif