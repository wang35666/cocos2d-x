#ifndef __LVARSYSTEM_H__
#define __LVARSYSTEM_H__

#include <string>
#include <vector>
#include "base/ccCArray.h"

NS_CC_BEGIN

class LVar
{
public:
	LVar();
	~LVar();

	int getInt();
	bool getBool();

private:
	std::string value;
};



class LVarSystem
{
public:
	LVarSystem();
	~LVarSystem();

	bool init();

	bool regsiter(LVar* var);
	bool unRegister(LVar* var);

private:

	std::vector<LVar*> list;
};

extern LVarSystem* varSystem;

NS_CC_END

#endif // !__SCRIPTSYSTEM_H__



