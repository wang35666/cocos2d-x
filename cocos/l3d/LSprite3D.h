#ifndef __LSPRITE3D_H__
#define __LSPRITE3D_H__

#include <string>
#include <vector>

#include "base/CCProtocols.h"
#include "2d/CCNode.h"
#include "platform/CCPlatformMacros.h"

NS_CC_BEGIN

class LModel;
class Texture2D;
class GLProgram;
class GLProgramState;

class CC_DLL LSprite3D : public Node, public BlendProtocol
{
public:
	static LSprite3D* create();

	static LSprite3D* create(const std::string &modelPath);

	static LSprite3D* create(const std::string &modelPath, const std::string &texturePath);

	void setTexture(const std::string& texFile);
	void setTexture(Texture2D* texture);

	virtual void setBlendFunc(const BlendFunc &blendFunc) override;
	virtual const BlendFunc &getBlendFunc() const override;

	virtual void setGLProgramState(GLProgramState *glProgramState) override;
	virtual void setGLProgram(GLProgram *glprogram) override;

	//const AABB& getAABB() const;

	virtual Action* runAction(Action* action) override;

	virtual Rect getBoundingBox() const override;

	/**draw*/
	virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;

CC_CONSTRUCTOR_ACCESS:

	LSprite3D();
	virtual ~LSprite3D();

	virtual bool init() override;

	bool initWithFile(const std::string &path);

	virtual void visit(Renderer *renderer, const Mat4& parentTransform, uint32_t parentFlags) override;

	virtual void onDraw(const Mat4 &transform, uint32_t flags);

protected:
	LModel _model;

	BlendFunc                  _blend;

	std::vector<LModel*>       _meshes;

	Texture2D _texture;

	CustomCommand _customCommand;  

	MeshCommand _meshCommand;
};

NS_CC_END
#endif