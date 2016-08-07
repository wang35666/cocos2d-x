#include "L3DTest.h"

#include "../../cocos/l3d/LModelLoaderB3D.h"

USING_NS_CC;

class B3DLoaderTest : public TestCase
{
public:
	CREATE_FUNC(B3DLoaderTest);

	virtual void onEnter() override;
	virtual std::string title() const override;
	virtual std::string subtitle() const override;

protected:
	B3DLoaderTest();
	virtual ~B3DLoaderTest();
};

B3DLoaderTest::B3DLoaderTest()
{
}

B3DLoaderTest::~B3DLoaderTest()
{
}

void B3DLoaderTest::onEnter()
{
	LModelLoaderB3D modelLoader;
	modelLoader.Load("C:/program1/LightWorld/media/ninja.b3d");
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

