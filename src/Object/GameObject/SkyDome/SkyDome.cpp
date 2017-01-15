#include "SkyDome.h"

SkyDome::SkyDome() :
	GameObject(Transform(ci::Vec3f::zero(),
		ci::Vec3f::zero(),
		ci::Vec3f(1000.0f, 1000.0f, 1000.0f))),
	segments(100)
{

}

SkyDome::SkyDome(const ci::Vec3f &translate, const float &radius, const int &segments) :
	GameObject(Transform(translate,
		ci::Vec3f::zero(),
		ci::Vec3f(radius, radius,radius))),
	segments(segments)
{
	
}

SkyDome::~SkyDome()
{

}

void SkyDome::Setup()
{
	UpdateMatrix();
}

void SkyDome::Update()
{

}

void SkyDome::Draw()
{
	ci::gl::color(ci::Color::white());

	// “à‘¤‚ð•`ŽÊ
	glCullFace(GL_FRONT);

	TextureManager::Get().GetTexture("SkyDome").enableAndBind();

	ci::gl::pushModelView();

	ci::gl::multModelView(matrix);

	ci::gl::drawSphere(ci::Vec3f::zero(), 1.0f, segments);

	TextureManager::Get().GetTexture("SkyDome").unbind();

	ci::gl::popModelView();

	glCullFace(GL_BACK);
}
