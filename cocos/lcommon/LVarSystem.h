#ifndef __LVARSYSTEM_H__
#define __LVARSYSTEM_H__

#include <string>
#include <vector>
#include "base/ccCArray.h"

NS_CC_BEGIN

class LVar
{
public:
	LVar() = delete;

	//// Always use one of the following constructors.
	LVar(const char *name, const char *value, int flags, const char *description);
	//idCVar(const char *name, const char *value, int flags, const char *description,
	//	float valueMin, float valueMax, argCompletion_t valueCompletion = NULL);
	//idCVar(const char *name, const char *value, int flags, const char *description,
	//	const char **valueStrings, argCompletion_t valueCompletion = NULL)

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



