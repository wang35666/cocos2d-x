#ifndef __LMATERIAL_H__
#define __LMATERIAL_H__

#include <string>

#include "platform/CCPlatformMacros.h"

NS_CC_BEGIN

class CC_DLL LMaterial
{
private:
	LMaterial();
	~LMaterial();

	void initWithFile(const std::string& filePath);

public:
	std::string _name;
};

NS_CC_END

#endif

