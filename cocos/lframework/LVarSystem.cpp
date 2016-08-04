#include "LVarSystem.h"

NS_CC_BEGIN

static LVarSystem local;
LVarSystem* varSystem = &local;

LVar::LVar()
{
	varSystem->regsiter(this);
}

LVar::~LVar()
{
	varSystem->unRegister(this);
}

int LVar::getInt()
{
	return 0;
}

bool LVar::getBool()
{
	return 1;
}

LVarSystem::LVarSystem()
{

}

LVarSystem::~LVarSystem()
{

}

bool LVarSystem::init()
{
	return false;
}

bool LVarSystem::regsiter(LVar* var)
{
	list.push_back(var);
	return true;
}

bool cocos2d::LVarSystem::unRegister(LVar* var)
{
	auto varIter = std::find(list.begin(), list.end(), var);
	if (varIter != list.end())
		list.erase(varIter);

	return true;
}

NS_CC_END