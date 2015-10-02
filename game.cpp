#include "IwGx.h"
#include "IwHashString.h"

#include "game.h"
#include "main.h"
#include "input.h"
#include "audio.h"
#include "resources.h"
#include "pauseMenu.h"
#include "s3eVibra.h"
#include "s3eAccelerometer.h"
#include "splash.h"
#include "poo.h"

#define MAN_LIMIT 4
#define FONT_DESIGN_WIDTH 320
#define FONT_HEIGHT 15
#define FILE_NAME "highscores.txt"

Game::~Game()
{
	delete g_pSplashManager;
}

// Pause game handler that is called when the user taps the pause sprite
void Game::pauseGame()
{
	// Pause timers
	m_Timers.Pause();

	// Store old game state and change to paused game state

	// Switch to pause menu scene
	g_pSceneManager->SwitchTo(g_pSceneManager->Find("pausemenu"));

	//  explosion.stopExplosions()
}
// Initialise a round

// Starts a new game - Called from the main and pause menus

void Game::Update(float deltaTime, float alphaMul)
{
	if (!m_IsActive)
		return;
	if (m_Manager->GetCurrent() == this)
	{
		// Update base scene
		Scene::Update(deltaTime, alphaMul);

		if (!gameOver)
		{
			if (!accelerometer)
			{
				s3eDebugOutputString("accelerometer start");
				s3eAccelerometerStart();
				accelerometer = true;
				if (s3eVibraGetInt(S3E_VIBRA_AVAILABLE) != 0)
				{

					s3eVibraSetInt(S3E_VIBRA_ENABLED, true);

				}

				CalibrateButton();

			}

			if (m_IsInputActive)
			{
				if (g_pInput->m_Touched && !g_pInput->m_PrevTouched)
				{
					g_pInput->Reset();
					if (pauseSprite->HitTest(g_pInput->m_X, g_pInput->m_Y))
					{
						pauseGame();
					}

					else if (pooArray.size() < 3)
					{
						Poop();
					}
				}
			}

			if (pooChecker < pooArray.size())
			{
				if (pooArray.at(pooChecker)->m_X <= pooArray.at(pooChecker)->getEndPos())
				{
					OutputLine((int)(pooArray.at(pooChecker)->m_W));
					RemoveChild(pooArray.at(pooChecker));
					g_pSplashManager->Create((float)(pooArray.at(pooChecker)->m_X + (pooArray.at(pooChecker)->m_W / 2)),
						(float)(pooArray.at(pooChecker)->m_Y),
						(float)(pooArray.at(pooChecker)->m_W));
					pooArray.erase(pooArray.begin() + pooChecker);
				}
				pooChecker++;
			}
			else
			{
				pooChecker = 0;
			}


			if (manChecker < manArray.size())
			{
				if (manArray.at(manChecker)->m_Y <= -edge)
				{
					RemoveChild(manArray.at(manChecker));
					manArray.erase(manArray.begin() + manChecker);

					RemoveChild(boatArray.at(manChecker));
					boatArray.erase(boatArray.begin() + manChecker);
				}
				else
				{
					CheckCollision(manArray.at(manChecker));


					if (!manArray.at(manChecker)->getShoot())
					{
						if (manArray.at(manChecker)->m_Y - bird->m_Y <= IwGxGetDeviceHeight() / 4 && manArray.at(manChecker)->m_Y > bird->m_Y)
						{
							Shoot(manArray.at(manChecker));
						}
					}
				}
				manChecker++;
			}
			else
			{
				manChecker = 0;
			}

			if (rand() % 1000 < 10 && manArray.size() < MAN_LIMIT)
			{
				if (manArray.size() == 0 || manArray.at(manArray.size() - 1)->m_Y <= manPosCheck)
				{
					AddMan();
				}
			}

			if (foodChecker < foodArray.size())
			{
				if ((int)foodArray.at(foodChecker)->m_Y == foodArray.at(foodChecker)->getEndPos())
				{
					RemoveChild(foodArray.at(foodChecker));
					g_pSplashManager->Create((float)(foodArray.at(foodChecker)->m_X),
						(float)(foodArray.at(foodChecker)->m_Y - (foodArray.at(foodChecker)->m_W / 2)),
						(float)(foodArray.at(foodChecker)->m_W));


					foodArray.erase(foodArray.begin() + foodChecker);
				}

				else if (bird->HitTest(foodArray.at(foodChecker)->m_X, foodArray.at(foodChecker)->m_Y))
				{
					RemoveChild(foodArray.at(foodChecker));
					foodArray.erase(foodArray.begin() + foodChecker);
					gameOver = true;


					m_Tweener.Tween(5.0f,
						FLOAT, &bird->m_X, (float)(-edge),
						END);

					m_Tweener.Tween(5.0f,
						FLOAT, &bird->m_Angle, 360.0f,
						REPEAT,
						END);

					endGame = new CSprite();
					endGame->SetImage(g_pResources->getNewButton());
					endGame->m_X = (int)IwGxGetDeviceWidth() / 2;
					endGame->m_Y = (int)IwGxGetDeviceHeight() / 2;
					endGame->m_AnchorX = 0.5;
					endGame->m_ScaleX = (float)(IwGxGetDeviceWidth() / 4) / endGame->GetImage()->GetWidth();
					endGame->m_ScaleY = endGame->m_ScaleX;
					AddChild(endGame);
					s3eVibraStop();


					if (counter > highScore)
					{
						highScore = counter;
						newHighScore = new CSprite();
						newHighScore->SetImage(g_pResources->getHighScoreImage());
						newHighScore->m_X = (int)(IwGxGetDeviceWidth() / 3) * 2;
						newHighScore->m_Y = (int)IwGxGetDeviceHeight() / 2;
						newHighScore->m_AnchorX = 0.5;
						newHighScore->m_ScaleX = (float)(IwGxGetDeviceWidth() / 4) / newHighScore->GetImage()->GetWidth();
						newHighScore->m_ScaleY = newHighScore->m_ScaleX;
						newHighScore->m_Angle = 270.0f;
						AddChild(newHighScore);

						s3eFile* file = s3eFileOpen("highscores.txt", "wb");
						if (file != NULL)
						{
							s3eFileWrite(&highScore, sizeof(highScore), 1, file);
							s3eFileClose(file);
						}
					}
				}
				else if (foodArray.at(foodChecker)->m_Y >= (IwGxGetDeviceWidth() / 4))
				{
					AddChild(foodArray.at(foodChecker));
				}

				foodChecker++;
			}
			else
			{
				foodChecker = 0;
			}

			MoveBird();
		}

		else
		{
			if (!g_pInput->m_Touched && g_pInput->m_PrevTouched)
			{
				g_pInput->Reset();
				if (endGame->HitTest(g_pInput->m_X, g_pInput->m_Y))
				{
					RemoveChild(endGame);
					RestartGame();
				}
			}
		}
	}
}


void Game::RestartGame()
{
	int i;
	for (i = 0; i < foodArray.size(); i++)
	{
		RemoveChild(foodArray.at(i));
	}

	for (i = 0; i < pooArray.size(); i++)
	{
		RemoveChild(pooArray.at(i));
	}

	for (i = 0; i < manArray.size(); i++)
	{
		RemoveChild(manArray.at(i));
		RemoveChild(boatArray.at(i));
	}

	manArray.clear();
	boatArray.clear();
	foodArray.clear();
	pooArray.clear();

	RemoveChild(bird);
	if (newHighScore != NULL)
	{
		RemoveChild(newHighScore);
		newHighScore = NULL;
	}
	endGame = NULL;

	NewGame();
}
void Game::CheckCollision(Man* m)
{
	int p;
	for (p = 0; p < pooArray.size(); p++)
	{
		if (m->HitTest(pooArray.at(p)->m_X, pooArray.at(p)->m_Y))
		{
			if (!manArray.at(manChecker)->getHit())
			{
				if (s3eVibraGetInt(S3E_VIBRA_AVAILABLE) != 0)
				{
					if (!s3eVibraGetInt(S3E_VIBRA_ENABLED))
					{
						s3eVibraSetInt(S3E_VIBRA_ENABLED, true);
					}

					s3eVibraVibrate(255, 1000);
				}
				m->setHit(true);
				m->setShoot(true);
				m->SetImage(g_pResources->getManHitImage());
				counter++;
				label->m_Text = "Hits: ";
				char str[16];
				snprintf(str, 16, "%d", counter);
				label->m_Text += str;
			}

			RemoveChild(pooArray.at(p));
			pooArray.erase(pooArray.begin() + p);
			break;
		}
	}
}

void Game::AddMan()
{

	CSprite* tempBoat = new CSprite();
	tempBoat->m_Y = IwGxGetDeviceHeight() * 1.1;
	tempBoat->m_X = (IwGxGetDeviceWidth() / 7);
	tempBoat->SetImage(g_pResources->getBoatImage());
	tempBoat->m_AnchorX = 0.5;
	tempBoat->m_AnchorY = 0.5;

	// Fit background to screen size

	tempBoat->m_ScaleX = (float)((IwGxGetDeviceWidth() / 7) / tempBoat->GetImage()->GetWidth());
	tempBoat->m_ScaleY = tempBoat->m_ScaleX;

	boatArray.push_back(tempBoat);
	AddChild(boatArray.back());


	Man* tempSprite = new Man();
	tempSprite->m_Y = tempBoat->m_Y;
	tempSprite->m_X = (IwGxGetDeviceWidth() / 4);
	tempSprite->SetImage(g_pResources->getManImage());
	tempSprite->m_AnchorX = 0.5;
	tempSprite->m_AnchorY = 0.5;
	tempSprite->setHit(false);
	tempSprite->setShoot(false);
	// Fit background to screen size

	tempSprite->m_ScaleX = tempBoat->m_ScaleX;
	tempSprite->m_ScaleY = tempSprite->m_ScaleX;

	manArray.push_back(tempSprite);
	AddChild(manArray.back());

	float timeTaken = IwGxGetDeviceWidth() / (IwGxGetDeviceWidth() / 20);
	m_Tweener.Tween(timeTaken,
		FLOAT, &manArray.back()->m_Y, (float)(-edge),
		FLOAT, &boatArray.back()->m_Y, (float)(-edge),
		END);
}

void Game::Shoot(Man* m)
{
	Food* tempSprite = new Food();
	tempSprite->m_Y = m->m_Y;
	tempSprite->m_X = 0;
	tempSprite->SetImage(g_pResources->getHotDogImage());
	tempSprite->m_AnchorX = 0.5;
	tempSprite->m_AnchorY = 0.5;
	// Fit background to screen size

	tempSprite->m_ScaleX = (IwGxGetDeviceWidth() / 9) / tempSprite->GetImage()->GetWidth();
	tempSprite->m_ScaleY = tempSprite->m_ScaleX;

	tempSprite->m_W = (IwGxGetDeviceWidth() / 9);
	tempSprite->m_H = tempSprite->m_ScaleX * tempSprite->GetImage()->GetHeight();



	foodArray.push_back(tempSprite);
	AddChild(foodArray.back());

	m_Tweener.Tween(2.5f,
		FLOAT, &foodArray.back()->m_X, (float)(bird->m_X),
		MIRROR,
		END);

	m_Tweener.Tween(5.0f,
		FLOAT, &foodArray.back()->m_Y, (float)(bird->m_Y - (m->m_Y - bird->m_Y)),
		END);


	m_Tweener.Tween(5.0f,
		FLOAT, &foodArray.back()->m_Angle, 120.0f,
		END);


	tempSprite->m_X += m->m_X;
	foodArray.back()->setEndPos((float)(bird->m_Y - (m->m_Y - bird->m_Y)));


	m->setShoot(true);
}

void Game::Poop()
{
	Poo* tempSprite = new Poo();
	tempSprite->m_Y = bird->m_Y;
	tempSprite->m_X = bird->m_X - edge;
	tempSprite->SetImage(g_pResources->getPooSprite());
	tempSprite->m_AnchorX = 0.5;
	tempSprite->m_AnchorY = 0.5;
	// Fit background to screen size
	tempSprite->setEndPos((float)(rand() % (IwGxGetDeviceWidth() / 4)));
	tempSprite->m_ScaleX = pauseSprite->m_ScaleX;
	tempSprite->m_ScaleY = pauseSprite->m_ScaleX;

	tempSprite->m_W = (tempSprite->GetImage()->GetWidth() * tempSprite->m_ScaleX);

	pooArray.push_back(tempSprite);
	AddChild(pooArray.back());

	float timeTaken = IwGxGetDeviceWidth() / (IwGxGetDeviceWidth() / 5);

	m_Tweener.Tween(timeTaken,
		FLOAT, &pooArray.back()->m_X, (float)pooArray.back()->getEndPos(),
		END);
}

void Game::MoveBird()
{

	int tempPosition = (s3eAccelerometerGetX() - DefaultX) / 20;
	if (tempPosition < 0)
	{
		tempPosition = tempPosition * 2;
	}
	bird->m_X += tempPosition;

	//check the bird is not going too high
	{
		if (bird->m_X > pauseSprite->m_X)
		{
			bird->m_X = pauseSprite->m_X;
		}
		else if (bird->m_X < up)
		{
			bird->m_X = up;
		}
	}

	bird->m_Y -= (s3eAccelerometerGetY() - DefaultY) / 20;
	//check the bird is still on screen
	{
		if (bird->m_Y > pauseSprite->m_Y - edge)
		{
			bird->m_Y = pauseSprite->m_Y - edge;
		}
		else if (bird->m_Y < edge)
		{
			bird->m_Y = edge;
		}
	}
}

void Game::Render()
{
    Scene::Render();
}

// Initialise the games user interface
void Game::initUI()
{
	float limit = IwGxGetDeviceHeight() / 2;
	float width = ceil(IwGxGetDeviceWidth() / 2);

	CSprite* background = new CSprite();
	background->m_X = (float)width;
	background->m_Y = (float)limit;
	background->SetImage(g_pResources->getGameBG());
	background->m_AnchorX = 0.5;
	background->m_AnchorY = 0.5;
	// Fit background to Device size
	background->m_ScaleX = (float)(IwGxGetDeviceWidth()) / background->GetImage()->GetWidth();
	background->m_ScaleY = (float)IwGxGetDeviceHeight() / background->GetImage()->GetHeight();
	AddChild(background);

	CSprite* backgroundTwo = new CSprite();
	backgroundTwo->m_X = (float)background->m_X;
	backgroundTwo->m_Y = (IwGxGetDeviceHeight() + (background->m_Y));
	backgroundTwo->SetImage(g_pResources->getGameBG());
	backgroundTwo->m_AnchorX = 0.5;
	backgroundTwo->m_AnchorY = 0.5;
	// Fit backgroundTwo to Device size
	backgroundTwo->m_ScaleX = background->m_ScaleX;
	backgroundTwo->m_ScaleY = background->m_ScaleY;
	AddChild(backgroundTwo);

	int i;
	CSprite** Cloud = new CSprite*[6];
	float minimium = (float)IwGxGetDeviceHeight() * 1.2;
	float cloudLimit = IwGxGetDeviceHeight() / 12;
	float scaleX = (float)(IwGxGetDeviceWidth() / 4) / g_pResources->getCloudImage(0)->GetWidth();
	cloudLimit /= 2;
	for (i = 0; i < 6; i++)
	{
		Cloud[i] = new CSprite();
		Cloud[i]->m_X = (float)(rand() % IwGxGetDeviceWidth());
		Cloud[i]->m_Y = (float)(minimium);


		Cloud[i]->SetImage(g_pResources->getCloudImage(i));
		Cloud[i]->m_AnchorX = 0.5;
		Cloud[i]->m_AnchorY = 0.5;
		Cloud[i]->m_Angle = 270.0f;
		Cloud[i]->m_ScaleX = scaleX;
		Cloud[i]->m_ScaleY = Cloud[i]->m_ScaleX;
		// Fit background to Device size
		AddChild(Cloud[i]);

		m_Tweener.Tween(45.0f,
			FLOAT, &Cloud[i]->m_Y, -(cloudLimit),
			DELAY, (float)(i * 20),
			END);
	}


	m_Tweener.Tween(30.0f,
		FLOAT, &background->m_Y, -(limit),
		FLOAT, &backgroundTwo->m_Y, limit,
		REPEAT,
		END);

	CSprite* SeaOne = new CSprite();
	SeaOne->m_X = (background->m_X / 4);
	SeaOne->m_Y = background->m_Y;
	SeaOne->SetImage(g_pResources->getSeaImage());
	SeaOne->m_AnchorX = 0.5;
	SeaOne->m_AnchorY = 0.5;
	// Fit SeaOne to Device size
	SeaOne->m_ScaleX = (float)(IwGxGetDeviceWidth() / 4) / SeaOne->GetImage()->GetWidth();
	SeaOne->m_ScaleY = (float)(IwGxGetDeviceHeight() / SeaOne->GetImage()->GetHeight());
	AddChild(SeaOne);

	CSprite* SeaTwo = new CSprite();
	SeaTwo->m_X = SeaOne->m_X;
	SeaTwo->m_Y = backgroundTwo->m_Y;
	SeaTwo->SetImage(g_pResources->getSeaImage());
	SeaTwo->m_AnchorX = 0.5;
	SeaTwo->m_AnchorY = 0.5;
	// Fit SeaTwo to Device size
	SeaTwo->m_ScaleX = (float)SeaOne->m_ScaleX;
	SeaTwo->m_ScaleY = (float)SeaOne->m_ScaleY;
	AddChild(SeaTwo);

	m_Tweener.Tween(10.0f,
		FLOAT, &SeaOne->m_Y, -(limit),
		FLOAT, &SeaTwo->m_Y, limit,
		REPEAT,
		END);

	pauseSprite = new CSprite();
	pauseSprite->SetImage(g_pResources->getPauseIcon());
	pauseSprite->m_X = ((float)IwGxGetDeviceWidth() * 0.9);
	pauseSprite->m_Y = ((float)IwGxGetDeviceHeight() * 0.9);
	pauseSprite->m_AnchorX = 0.5;
	pauseSprite->m_ScaleX = (IwGxGetDeviceWidth() / 12) / pauseSprite->GetImage()->GetWidth();

	pauseSprite->m_ScaleY = pauseSprite->m_ScaleX;
	AddChild(pauseSprite);

	up = IwGxGetDeviceWidth() - pauseSprite->m_X;

	float fontScale = (float)IwGxGetScreenWidth() / FONT_DESIGN_WIDTH;
	float actualFontHeight = FONT_HEIGHT * fontScale;

	label = new CLabel();
	label->m_X = pauseSprite->m_X + (IwGxGetDeviceWidth() * 0.1);
	label->m_Y = pauseSprite->m_Y * 0.85;
	label->m_W = FONT_DESIGN_WIDTH;
	label->m_H = actualFontHeight;
	label->m_Text = "Hits: 0";
	label->m_AlignHor = IW_2D_FONT_ALIGN_LEFT;
	label->m_AlignVer = IW_2D_FONT_ALIGN_TOP;
	label->m_Font = g_pResources->getFont();
	label->m_ScaleX = fontScale;
	label->m_ScaleY = fontScale;
	label->m_Color = CColor(0x00, 0x00, 0x00, 0xff);
	label->m_Angle = 270;
	AddChild(label);
}

void Game::Init()
{
	initUI();

	NewGame();

	g_pSplashManager = new SplashManager();
}

void Game::OutputLine(int i)
{
	char str[16];
	snprintf(str, 16, "%d", i);
	s3eDebugOutputString(str);
}

void Game::NewGame()
{
	s3eAccelerometerStart();
	accelerometer = false;
	manPosCheck = IwGxGetDeviceHeight() - (IwGxGetDeviceHeight() / 5);
	gameOver = false;

	bird = new CSprite();
	bird->m_X = (float)IwGxGetDeviceWidth() / 2;
	bird->m_Y = (float)IwGxGetDeviceHeight() / 8;
	bird->SetImage(g_pResources->getBirdImage());
	bird->m_AnchorX = 0.5;
	bird->m_AnchorY = 0.5;
	// Fit bird to Device size
	edge = (int)(IwGxGetDeviceWidth() / 8);
	bird->m_ScaleX = (float)(edge / bird->GetImage()->GetWidth());
	bird->m_ScaleY = (float)bird->m_ScaleX;
	AddChild(bird);

	counter = 0;
	newHighScore = NULL;
}