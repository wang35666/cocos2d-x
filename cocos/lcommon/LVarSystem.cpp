#include "LVarSystem.h"
#include <algorithm>

NS_CC_BEGIN

LVar::LVar(const char *name, const char *value, int flags, const char *description) : name(name)
{
	LVarSystem::getInstance().regsiter(this);
}

LVar::~LVar()
{
	LVarSystem::getInstance().unRegister(this);
}

int LVar::getInt()
{
	return integerValue;
}

bool LVar::getBool()
{
	return boolValue;
}

float LVar::getFloat()
{
	return floatValue;
}

void LVar::updateValue()
{
	if (flag == LVAR_INTEGER)
	{
		integerValue = atoi(value.c_str());
	}
	else if (flag == LVAR_FLOAT)
	{
		floatValue = (float)atof(value.c_str());
	}
	else if (flag == LVAR_BOOL)
	{
		boolValue = (atoi(value.c_str()) != 0);
	}
}

void LVar::set(const char* val)
{
	value = val;
	updateValue();
}

LVarSystem::LVarSystem()
{

}

LVarSystem::LVarSystem(const LVarSystem& system)
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

LVar* LVarSystem::find(const char* name)
{
	for (auto var : list)
	{
		if (var->name.compare(name) == 0)
			return var;
	}

	return nullptr;
}

LVarSystem& LVarSystem::getInstance()
{
	static LVarSystem varSystem;
	return varSystem;
}

bool LVarSystem::unRegister(LVar* var)
{
	auto varIter = std::find(list.begin(), list.end(), var);
	if (varIter != list.end())
		list.erase(varIter);

	return true;
}

NS_CC_END