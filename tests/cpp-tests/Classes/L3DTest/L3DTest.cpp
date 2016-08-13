#include "L3DTest.h"

#include "../../cocos/l3d/LModelLoaderB3D.h"

#include "../../cocos/l3d/LSprite3D.h"

USING_NS_CC;

class B3DLoaderTest : public TestCase
{
public:
	CREATE_FUNC(B3DLoaderTest);

	virtual std::string title() const override;
	virtual std::string subtitle() const override;

protected:
	B3DLoaderTest();
	virtual ~B3DLoaderTest();
};

B3DLoaderTest::B3DLoaderTest()
{
	auto orc = cocos2d::Sprite3D::create("Sprite3DTest/orc.c3b");
	orc->setScale(5);
	orc->setNormalizedPosition(Vec2(.5f, .3f));
	orc->setPositionZ(40);
	orc->setRotation3D(Vec3(0, 180, 0));
	orc->setGlobalZOrder(-1);

	//addChild(orc);

	LSprite3D* sprite = LSprite3D::create("C:/program1/LightWorld/media/ninja.b3d");
	sprite->setTexture("C:/program1/LightWorld/media/nskinbl.jpg");

	addChild(sprite);
}

B3DLoaderTest::~B3DLoaderTest()
{
}

std::string B3DLoaderTest::title() const
{
	return "B3D loader test";
}

std::string B3DLoaderTest::subtitle() const
{
	return "B3D loader tes1t";
}

L3DTest::L3DTest()
{
	ADD_TEST_CASE(B3DLoaderTest)
}

