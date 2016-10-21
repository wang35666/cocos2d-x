#include "LSprite3D.h"
#include "LModel.h"
#include "LModelLoaderB3D.h"
#include "LSurface.h"

#include "renderer/CCTextureCache.h"
#include "renderer/CCRenderer.h"
#include "renderer/CCGLProgramState.h"

#include "platform/CCFileUtils.h"

#include "base/CCDirector.h"

#include "renderer/CCGLProgramCache.h"

#include "renderer/ccGLStateCache.h"

#include "2d/CCCamera.h"
#include "lcommon/LVarSystem.h"

NS_CC_BEGIN

static LVar use_debug_mvp("use_debug_mvp", "0", 1, "debug_mvp");
LSprite3D* LSprite3D::create()
{
	auto sprite = new (std::nothrow) LSprite3D();
	if (sprite && sprite->init())
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

LSprite3D* LSprite3D::create(const std::string &modelPath)
{
	CCASSERT(modelPath.length() >= 4, "invalid filename for LSprite3D");

	auto sprite = new (std::nothrow) LSprite3D();
	if (sprite && sprite->initWithFile(modelPath))
	{
		sprite->_contentSize = sprite->getBoundingBox().size;
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

LSprite3D* LSprite3D::create(const std::string &modelPath, const std::string &texturePath)
{
	auto sprite = create(modelPath);
	if (sprite)
	{
		sprite->setTexture(texturePath);
	}

	return sprite;
}

bool LSprite3D::init()
{
	if (Node::init())
	{
		return true;
	}

	return false;
}

void LSprite3D::setTexture(const std::string& texFile)
{
	auto tex = Director::getInstance()->getTextureCache()->addImage(texFile);
	setTexture(tex);
}

void LSprite3D::setTexture(Texture2D* texture)
{
	_texture = texture;
}

void LSprite3D::setBlendFunc(const BlendFunc &blendFunc)
{

}

const BlendFunc & LSprite3D::getBlendFunc() const
{
	return _blend;
}

//const AABB& LSprite3D::getAABB() const
//{
//
//}

Rect LSprite3D::getBoundingBox() const
{
	//AABB aabb = getAABB();
	//Rect ret(aabb._min.x, aabb._min.y, (aabb._max.x - aabb._min.x), (aabb._max.y - aabb._min.y));
	return Rect(0, 0, 1, 1);
}

Action* LSprite3D::runAction(Action* action)
{
	return Node::runAction(action);
}

void LSprite3D::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
	_customCommand.func = CC_CALLBACK_0(LSprite3D::onDraw, this, transform, flags);
	renderer->addCommand(&_customCommand);
}

LSprite3D::LSprite3D()
{
	_customCommand.setTransparent(false);
	_customCommand.set3D(true);
}

LSprite3D::~LSprite3D()
{

}

bool LSprite3D::initWithFile(const std::string &path)
{
	LModelLoaderB3D modelLoader;
	std::string& fullpath = FileUtils::getInstance()->fullPathForFilename(path);

	CC_ASSERT(FileUtils::getInstance()->isFileExist(fullpath));

	if (fullpath.size() == 0)
	{
		return false;
	}

	modelLoader.Load(fullpath.c_str());
	_model = modelLoader.GetModel();
	_model->BuildDeformInfo();

	GLProgram *glProgram = GLProgramCache::getInstance()->getGLProgram(GLProgram::SHADER_3D_POSITION_TEXTURE);
	if (glProgram)
		setGLProgram(glProgram);

	return true;
}

void LSprite3D::visit(Renderer *renderer, const Mat4& parentTransform, uint32_t parentFlags)
{
	// quick return if not visible. children won't be drawn.
	if (!_visible)
	{
		return;
	}

	uint32_t flags = processParentFlags(parentTransform, parentFlags);
	flags |= FLAGS_RENDER_AS_3D;

	//
	Director* director = Director::getInstance();
	director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
	director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, _modelViewTransform);

	bool visibleByCamera = isVisitableByVisitingCamera();

	int i = 0;

	if (!_children.empty())
	{
		sortAllChildren();
		// draw children zOrder < 0
		for (; i < _children.size(); i++)
		{
			auto node = _children.at(i);

			if (node && node->getLocalZOrder() < 0)
				node->visit(renderer, _modelViewTransform, flags);
			else
				break;
		}
		// self draw
		if (visibleByCamera)
			this->draw(renderer, _modelViewTransform, flags);

		for (auto it = _children.cbegin() + i; it != _children.cend(); ++it)
			(*it)->visit(renderer, _modelViewTransform, flags);
	}
	else if (visibleByCamera)
	{
		this->draw(renderer, _modelViewTransform, flags);
	}

	director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
}

void LSprite3D::onDraw(const Mat4 &transform, uint32_t flags)
{
	auto modelMatrix = getNodeToWorldTransform();

	auto glProgram = getGLProgram();
	glProgram->use();

	auto camera = Camera::getVisitingCamera();
	//const Mat4& camWorldMat = camera->getNodeToWorldTransform();
	
	if (!use_debug_mvp.getBool())
	{
		glProgram->setUniformsForBuiltins(transform);
	}
	else
	{
		float m[16]{ 1.299038, 0.000000, 0.000000, 0.000000, 0.000000, 1.244655, -0.695595, -0.695421,
		0.000000, -1.204505, -0.718782, -0.718602, 0.000000, 0.000000, 42.950069, 43.139309 };
		GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POSITION|GL::VERTEX_ATTRIB_FLAG_TEX_COORD);
		GLuint mvp = glProgram->getUniformLocation("CC_MVPMatrix");
		glProgram->setUniformLocationWithMatrix4fv(mvp, &m[0], 1);
	}

	GLuint colorLocation = glProgram->getUniformLocation("u_color");
	Color4F color(1, 1, 1, 1);
	glProgram->setUniformLocationWith4fv(colorLocation, (GLfloat*)&color.r, 1);

	GL::bindTexture2DN(0, _texture->getName());

	LSurface* surf = _model->GetSurfaces(0);

	glBindBuffer(GL_ARRAY_BUFFER, surf->vbo[0]);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, surf->vbo[1]);
	unsigned long offset = 0;
	//position
	glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(LDrawVert), (GLvoid *)offset);
	offset += sizeof(Vec3);
	//texcoord
	glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_TEX_COORD, 2, GL_FLOAT, GL_FALSE, sizeof(LDrawVert), (GLvoid *)offset);

	glDrawElements(GL_TRIANGLES, (GLsizei)surf->numIndices, GL_UNSIGNED_SHORT, 0);
}

void LSprite3D::setGLProgram(GLProgram *glprogram)
{
	Node::setGLProgram(glprogram);
}

NS_CC_END