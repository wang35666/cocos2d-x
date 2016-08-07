#include "LSprite3D.h"
#include "LModel.h"
#include "LModelLoaderB3D.h"

#include "renderer/CCTextureCache.h"
#include "renderer/CCRenderer.h"
#include "renderer/CCGLProgramState.h"

#include "platform/CCFileUtils.h"

#include "base/CCDirector.h"


NS_CC_BEGIN

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

}

void LSprite3D::setTexture(Texture2D* texture)
{

}

void LSprite3D::setBlendFunc(const BlendFunc &blendFunc)
{

}

const BlendFunc & LSprite3D::getBlendFunc() const
{
	return _blend;
}

void LSprite3D::setGLProgramState(GLProgramState *glProgramState)
{

}

void LSprite3D::setGLProgram(GLProgram *glprogram)
{

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
#if CC_USE_CULLING
	// camera clipping
	//if (_children.size() == 0 && Camera::getVisitingCamera() && !Camera::getVisitingCamera()->isVisibleInFrustum(&getAABB()))
	//	return;
#endif

	Color4F color(getDisplayedColor());
	color.a = getDisplayedOpacity() / 255.0f;

	////check light and determine the shader used
	//const auto& scene = Director::getInstance()->getRunningScene();

	//_customCommand.init(_globalZOrder, transform, flags);
	//_customCommand.func = CC_CALLBACK_0(LSprite3D::onDraw, this, transform, flags);

	//renderer->addCommand(&_customCommand)

	// Don't override GLProgramState if using manually set Material
	/*	if (_usingAutogeneratedGLProgram && scene)
		{
		const auto lights = scene->getLights();
		bool usingLight = false;
		for (const auto light : lights) {
		usingLight = light->isEnabled() && ((static_cast<unsigned int>(light->getLightFlag()) & _lightMask) > 0);
		if (usingLight)
		break;
		}
		if (usingLight != _shaderUsingLight)
		{
		genMaterial(usingLight);
		}
		*/

	/*for (auto mesh : _meshes)
	{
	mesh->draw(renderer,
	_globalZOrder,
	transform,
	flags,
	_lightMask,
	Vec4(color.r, color.g, color.b, color.a),
	_forceDepthWrite);

	}*/

	/*LSurface* surf = _model->GetSurfaces(0);
	_meshCommand.init(getLocalZOrder(),
		_material,
		&surf->verts[0];
	&surf->indices[0],
	,
	,
	surf->numIndices,
	transform,
	flags);*/


	//    if (isTransparent && !forceDepthWrite)
	//        _material->getStateBlock()->setDepthWrite(false);
	//    else
	_material->getStateBlock()->setDepthWrite(true);


	_meshCommand.setSkipBatching(isTransparent);
	_meshCommand.setTransparent(isTransparent);
	_meshCommand.set3D(!_force2DQueue);
	_material->getStateBlock()->setBlend(_force2DQueue || isTransparent);

	// set default uniforms for Mesh
	// 'u_color' and others
	const auto scene = Director::getInstance()->getRunningScene();
	auto technique = _material->_currentTechnique;
	for (const auto pass : technique->_passes)
	{
		auto programState = pass->getGLProgramState();
		programState->setUniformVec4("u_color", color);

		if (_skin)
			programState->setUniformVec4v("u_matrixPalette", (GLsizei)_skin->getMatrixPaletteSize(), _skin->getMatrixPalette());

		if (scene && scene->getLights().size() > 0)
			setLightUniforms(pass, scene, color, lightMask);
	}

	renderer->addCommand(&_meshCommand)
}

LSprite3D::LSprite3D()
{

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
	
}

NS_CC_END