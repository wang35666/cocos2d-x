#ifndef __LVARSYSTEM_H__
#define __LVARSYSTEM_H__

#include <string>
#include <vector>
#include "base/ccCArray.h"

NS_CC_BEGIN

typedef enum {
	LVAR_BOOL		= 0,	
	LVAR_INTEGER	= 1,	
	LVAR_FLOAT		= 2,	
	LVAR_STRING		= 4,
} lvarFlags_t;

class CC_DLL LVar
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
	float getFloat();
	void updateValue();

	void set(const char* val);

	friend class LVarSystem;
private:
	int integerValue;
	bool boolValue;
	float floatValue;

	int flag;

	std::string name;
	std::string value;
};

class CC_DLL LVarSystem
{
private:
	LVarSystem();
	LVarSystem(const LVarSystem& system);
	LVarSystem & operator = (const LVarSystem &);

public:
	static LVarSystem& getInstance();

	~LVarSystem();

	bool init();

	bool regsiter(LVar* var);
	bool unRegister(LVar* var);
	LVar* find(const char* name);

private:

	std::vector<LVar*> list;
};

NS_CC_END

#endif // !__SCRIPTSYSTEM_H__



