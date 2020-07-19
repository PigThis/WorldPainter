#include "GameDirector.h"

Director* Director::_shareDirector = nullptr;

Director::Director(unsigned int width, unsigned int height, std::wstring title) :
	_width(width),
	_height(height),
	_title(title)
{
	if (!_shareDirector)
		_shareDirector = this;
}

Director::~Director()
{
	_shareDirector = nullptr;
}

Director* Director::getInstance()
{
	return _shareDirector;
}

void Director::initGameProcedure()
{

}

void Director::endGame()
{

}

void Director::onUpdate()
{

}

void Director::onRender()
{

}