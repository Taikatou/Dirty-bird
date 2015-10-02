#if !defined(__RESOURCES_H__)
#define __RESOURCES_H__

#include "Iw2D.h"
#include "Iw2DSceneGraph.h"

using namespace Iw2DSceneGraph;

/**
* @class Resources
*
* @brief Resources class
*
* The that manages the lifetime of the following types of resources:
* - Images
* - Fonts
* - Atlases
*/
class Resources
{
protected:

	CIw2DImage*     MenuBG;
	CIw2DImage*     GameBG;
	CIw2DImage*     MenuButton;
	CIw2DImage*     PauseIcon;
	CIw2DImage*     PooImage;
	CIw2DImage**     cloudImage;
	CIw2DImage*     PlayButton;
	CIw2DFont*      Font;
	CIw2DImage*		NewGame;
	CIw2DImage*		ManImage;
	
	CIw2DImage*		settingsButtonImage;
	CIw2DImage*		seaImage;
	CIw2DImage*		recalibrateImage;
	CIw2DImage*		birdImage;
	CIw2DImage*		manHit;


	CIw2DImage*		highScoreImage;
	CIw2DImage*		hotDogImage;

	CAtlas*         SplashAtlas;
	CIw2DImage*		Splash;

	CIw2DImage*		Boat;

public:
	CIw2DImage*     getMenuBG()                 { return MenuBG; }
	CIw2DImage*     getCloudImage(int i)                 { return cloudImage[i]; }
	CIw2DImage*     getBoatImage()                 { return Boat; }
	CIw2DImage*     getHotDogImage()                 { return hotDogImage; }
	CIw2DImage*     getSeaImage()               { return seaImage; }
	CIw2DImage*     getBirdImage()              { return birdImage; }
	CIw2DImage*     getManImage()              { return ManImage; }
	CIw2DImage*     getManHitImage()              { return manHit; }
	CIw2DImage*     getGameBG()                 { return GameBG; }
	CIw2DImage*     getPooSprite()                 { return PooImage; }
	CIw2DImage*     getMenuButton()             { return MenuButton; }
	CIw2DImage*     getPlayButton()             { return PlayButton; }
	CIw2DImage*     getPauseIcon()              { return PauseIcon; }
	CIw2DFont*      getFont()                   { return Font; }
	CIw2DImage*     getNewButton()				{ return NewGame; }
	CIw2DImage*     getRecalImage()				{ return recalibrateImage; }
	CIw2DImage*     getHighScoreImage()				{ return highScoreImage; }
	CIw2DImage*     getSettingsButton()			{ return settingsButtonImage; }

	CAtlas*			getSplashAtlas()			{ return SplashAtlas; }

public:
	Resources();
	~Resources();
	void		LoadGame();
};

extern Resources* g_pResources;




#endif  // __RESOURCES_H__


