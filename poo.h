#if !defined(__POO_H)
#define __POO_H

#include "Iw2DSceneGraph.h"
#include "destroyable.h"
#include "IwTween.h"

using namespace IwTween;
using namespace Iw2DSceneGraphCore;
using namespace Iw2DSceneGraph;


class Poo : public CSprite
{
protected:
	int			endPos;
public:
	int			getEndPos() { return endPos; }
	void		setEndPos(int a) { endPos = a; }


public:
	Poo()  {}
	~Poo();


};

#endif  // __GEM_H
