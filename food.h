#if !defined(__FOOD_H)
#define __FOOD_H

#include "Iw2DSceneGraph.h"
#include "destroyable.h"
#include "IwTween.h"

using namespace IwTween;
using namespace Iw2DSceneGraphCore;
using namespace Iw2DSceneGraph;


class Food : public CSprite
{
protected:
	int				endPos;
public:
	int			getEndPos() { return endPos; }
	void		setEndPos(int a) { endPos = a; }


public:
	Food()  {}
	~Food();


};

#endif  // __GEM_H
