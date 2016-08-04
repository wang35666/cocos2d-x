#include "LJoint.h"

NS_CC_BEGIN

LJoint::LJoint() : parent(NULL)
{

}

LJoint::~LJoint()
{

}

void LJoint::GetPositionKeyFramesAtFrame(float frame, PositionKey* preKey, PositionKey* nextKey)
{
	unsigned int i = 0;
	for (; i < positionKeys.size(); ++i)
	{
		if (frame <= positionKeys[i].frame)
			break;
	}
	*preKey = positionKeys[i > 1 ? i - 1 : 0];
	*nextKey = positionKeys[i];
}

void LJoint::GetScaleKeyFramesAtFrame(float frame, ScaleKey* preKey, ScaleKey* nextKey)
{
	unsigned int i = 0;
	for (; i < scaleKeys.size() && frame <= scaleKeys[i].frame;)
	{
		if (frame <= scaleKeys[i].frame)
			break;
	}
	preKey = &scaleKeys[i > 1 ? i - 1 : 0];
	nextKey = &scaleKeys[i];
}

void LJoint::GetRotationKeyFramesAtFrame(float frame, RotationKey* preKey, RotationKey* nextKey)
{
	unsigned int i = 0;
	for (; i < rotationKeys.size(); ++i)
	{
		if (frame <= rotationKeys[i].frame)
			break;
	}
	*preKey = rotationKeys[i > 1 ? i - 1 : 0];
	*nextKey = rotationKeys[i];
}

void LJoint::GetFrame(float frame, Vec3& position, Quaternion& rotation)
{
	if (positionKeys.size() > 0)
	{
		PositionKey prePosition, nextPosition;
		GetPositionKeyFramesAtFrame(frame, &prePosition, &nextPosition);
		if (prePosition.frame != nextPosition.frame)
		{
			float t = (float)(frame - prePosition.frame) / (nextPosition.frame - prePosition.frame);
			position = prePosition.position + (nextPosition.position - prePosition.position)*t;
		}
		else
		{
			position = prePosition.position;
		}
	}

	if (rotationKeys.size() > 0)
	{
		RotationKey preRotation, nextRotation;
		GetRotationKeyFramesAtFrame(frame, &preRotation, &nextRotation);
		if (preRotation.frame != nextRotation.frame)
		{
			float t = (frame - preRotation.frame) / (nextRotation.frame - preRotation.frame);
			Quaternion::slerp(preRotation.rotation, nextRotation.rotation, t, &rotation);
			//rotation.sl(preRotation.rotation, nextRotation.rotation, t);
		}
		else
		{
			rotation = preRotation.rotation;
		}
	}
}


NS_CC_END