#ifndef __LVARSYSTEM_H__
#define __LVARSYSTEM_H__

#include <string>
#include "base/ccCArray.h"

class Var
{
public:
	Var();
	~Var();

	int GetInt();
	bool GetBool();

private:
	std::string value;
};


class VarSystem
{
public:
	VarSystem();
	~VarSystem();

	bool Init();

	bool Regster(Var* var);

private:

	Array<Var*> list;
};

extern VarSystem* varSystem;

#endif // !__SCRIPTSYSTEM_H__



