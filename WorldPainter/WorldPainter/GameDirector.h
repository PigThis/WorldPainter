#pragma once
#include <string>
#include <wrl.h>

class Director
{
public:
	Director(unsigned int width, unsigned int height, std::wstring title);
	virtual ~Director();

	unsigned int getWidth() const { return _width; }
	unsigned int getHeight() const { return _height; }
	const WCHAR* getTitle() const { return _title.c_str(); }

	static Director* getInstance();

	virtual void initGameProcedure();
	virtual void endGame();

	virtual void onUpdate();
	virtual void onRender();

	//void onKeyDown(UINT8 key);
	//void onKeyUp(UINT8 key);
protected:
	std::wstring _title;
	unsigned int _width;
	unsigned int _height;

	static Director* _shareDirector;
};

