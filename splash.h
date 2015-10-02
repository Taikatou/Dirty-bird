#if !defined(__SPLASH_H__)
#define __SPLASH_H__

#include <list>
#include "Iw2DSceneGraph.h"

using namespace Iw2DSceneGraphCore;
using namespace Iw2DSceneGraph;


class Splash : public CSprite
{

protected:
	bool InUse;

public:
	bool isInUse() const { return InUse; }
	void setUsed(bool used) { InUse = used; }
public:
	Splash();
	~Splash()	{}

	void Update(float deltaTime, float alphaMul);
};


class SplashManager
{
protected: std::list<Splash*>		Splashes;

public:
	Splash*		Create(float x, float y, float scale);
	void ReleaseAll();
	~SplashManager();
};

extern SplashManager*    g_pSplashManager;
#endif