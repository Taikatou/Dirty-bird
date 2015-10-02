/*
* (C) 2001-2012 Marmalade. All Rights Reserved.
*
* This document is protected by copyright, and contains information
* proprietary to Marmalade.
*
* This file consists of source code released by Marmalade under
* the terms of the accompanying End User License Agreement (EULA).
* Please do not use this program/source code before you have read the
* EULA and have agreed to be bound by its terms.
*/

#if !defined(__DESTROYABLE_H)
#define __DESTROYABLE_H

#include "Iw2DSceneGraph.h"

using namespace Iw2DSceneGraphCore;
using namespace Iw2DSceneGraph;


class Destroyable : public CSprite
{
protected:
	int         Life;
	int			divisions;
public:
	int         getLife() { return Life; }
	void		setLife(int l) { Life = l; }
	void		subtractFromLife(int a) { Life -= a; }


	int			getDivisions() { return divisions; }
	void		setDivisions(int a) { divisions = a; }
public:
	Destroyable()  {}
	~Destroyable();

	void init(int life);

};

#endif  // __GEM_H
