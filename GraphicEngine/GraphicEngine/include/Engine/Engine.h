#ifndef _ENGINE_H_
#define _ENGINE_H_

#include <functional>

class Engine
{
public:

protected:

	std::function<void(float deltaTime)> mPrepareScene;
	float mEngineWidth;
	float mEngineHeight;

private:

};

#endif