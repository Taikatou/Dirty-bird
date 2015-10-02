#include "resources.h"
#include "Iw2D.h"


Resources::Resources()
{
	MenuBG = Iw2DCreateImage("textures/menu_bkg.jpg");
	PlayButton		=		Iw2DCreateImage("textures/play.png");
	// Load fonts
	settingsButtonImage = Iw2DCreateImage("textures/settings-button.png");
	Font			=		Iw2DCreateFont("fonts/arial8.gxfont");
}

void Resources::LoadGame()
{
	manHit = Iw2DCreateImage("textures/manHit.png");
	GameBG = Iw2DCreateImage("textures/bkg.png");
	PauseIcon = Iw2DCreateImage("textures/pause_icon.png");
	NewGame = Iw2DCreateImage("textures/new_game.png");
	MenuButton = Iw2DCreateImage("textures/button_bg.png");
	seaImage = Iw2DCreateImage("textures/sea.png");
	birdImage = Iw2DCreateImage("textures/bird.png");
	PooImage = Iw2DCreateImage("textures/poo.png");
	ManImage = Iw2DCreateImage("textures/man.png");
	highScoreImage = Iw2DCreateImage("textures/highscore.png");
	hotDogImage = Iw2DCreateImage("textures/hotdog.png");

	Boat = Iw2DCreateImage("textures/boat.png");
	Splash = Iw2DCreateImage("textures/sprite-splash.png");
	int frame_third = (int)(Splash->GetWidth() / 3);
	SplashAtlas = new CAtlas(frame_third, frame_third, 9, Splash);

	recalibrateImage = Iw2DCreateImage("textures/recal.png");

	cloudImage = new CIw2DImage*[6];

	int i;
	for (i = 0; i < 6; i++)
	{

		char str[16];

		strcpy(str, "textures/cloud");

		char strB[16];
		snprintf(strB, 16, "%d", (i + 1));

		strcat(str, strB);
		strcat(str, ".png");

		cloudImage[i] = Iw2DCreateImage(str);
	}
}
Resources::~Resources()
{

	delete MenuBG;
	delete GameBG;
	delete MenuButton;
	delete PauseIcon;
	delete PlayButton;
	delete Font;
	delete seaImage;
	delete NewGame;
	delete settingsButtonImage;
	delete birdImage;
	delete PooImage;
	delete ManImage;
	delete highScoreImage;
	delete hotDogImage;
	delete SplashAtlas;
	delete Splash;
	delete Boat;
	delete manHit;
	delete recalibrateImage;
	int i;
	for (i = 0; i < 6; i++)
	{
		delete cloudImage[i];
	}
}

// Global resources
Resources* g_pResources = 0;



