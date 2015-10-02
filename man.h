#if !defined(__MAN_H)
#define __MAN_H

#include "Iw2DSceneGraph.h"
#include "destroyable.h"
#include "IwTween.h"

using namespace IwTween;
using namespace Iw2DSceneGraphCore;
using namespace Iw2DSceneGraph;


class Man : public CSprite
{
protected:
	bool			hit;
	bool			shoot;
public:
	bool			getHit() { return hit; }
	void			setHit(bool a) { hit = a; }

	bool			getShoot() { return shoot; }
	void			setShoot(bool a) { shoot = a; }

public:
	Man()  {}
	~Man();


};

#endif  // __GEM_H
