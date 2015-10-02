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

#include "MainMenu.h"
#include "IwGx.h"
#include "input.h"
#include "audio.h"
#include "resources.h"
#include "game.h"
#include "pauseMenu.h"
#include "s3eAudio.h"
#include "optionsMenu.h"
#define FILENAME "highscores.txt"
#define FONT_DESIGN_WIDTH 320
#define FONT_HEIGHT 15

MainMenu::~MainMenu()
{
}


void MainMenu::startGame(CTween* pTween)
{

	s3eAudioPlay("audio/Mahooka.wav", 0);

	Game* game = (Game*)g_pSceneManager->Find("game");
	g_pSceneManager->SwitchTo(game);

	// Start game music

	// Create new game
}


void MainMenu::Update(float deltaTime, float alphaMul)
{
    if (!m_IsActive)
        return;
	if (m_Manager->GetCurrent() == this)
	{

		Scene::Update(deltaTime, alphaMul);

		// Detect screen tap
		if (m_IsInputActive && m_Manager->GetCurrent() == this && !g_pInput->m_Touched && g_pInput->m_PrevTouched)
		{
			g_pInput->Reset();
			if (playButton->HitTest(g_pInput->m_X, g_pInput->m_Y))
			{
				// Animate the play button
				m_Tweener.Tween(0.5f,
					FLOAT, &playButton->m_Angle, 360.0f,
					FLOAT, &playButton->m_Alpha, 0.0f,
					ONCOMPLETE, startGame,
					END);
			}
			else if (optionsSprite->HitTest(g_pInput->m_X, g_pInput->m_Y))
			{
				OptionsMenu* options = (OptionsMenu*)g_pSceneManager->Find("options");
				if (options == NULL)
				{
					options = new OptionsMenu();
					options->SetName("options");
					options->Init();
					g_pSceneManager->Add(options);
				}
				g_pSceneManager->SwitchTo(options);
			}
		}

		if (count == 1)
		{
			// Switch to game scene
			g_pResources->LoadGame();
			Game* game = new Game();
			game->SetName("game");
			game->Init();
			g_pSceneManager->Add(game);
			game->setHighScore(highScore);
			// Init the pause menu
			PauseMenu* pause_menu = new PauseMenu();
			pause_menu->SetName("pausemenu");
			pause_menu->Init();
			g_pSceneManager->Add(pause_menu);
			count++;
		}
		else if (count < 2)
		{ 
			count++;
		}
	}
}

void MainMenu::Render()
{
    Scene::Render();
}

void MainMenu::Init()
{
    Scene::Init();
	// Create menu background
	int w = IwGxGetScreenWidth();
	int h = IwGxGetScreenHeight();

	if (w > h)
	{
		int temp = w;
		w = h;
		h = temp;
	}

	CSprite* background = new CSprite();
	background->m_X = (float)w / 2;
	background->m_Y = (float)h / 2;
	background->SetImage(g_pResources->getMenuBG());
	background->m_W = background->GetImage()->GetWidth();
	background->m_H = background->GetImage()->GetHeight();
	background->m_AnchorX = 0.5;
	background->m_AnchorY = 0.5;
	// Fit background to screen size
	background->m_ScaleX = (float)w / background->GetImage()->GetWidth();
	background->m_ScaleY = (float)h / background->GetImage()->GetHeight();
	AddChild(background);



	// Create pause menu sprite (docked to top of screen)
	optionsSprite = new CSprite();
	optionsSprite->SetImage(g_pResources->getSettingsButton());
	optionsSprite->m_X = (int)IwGxGetDeviceWidth() * 0.9;
	optionsSprite->m_Y = (int)IwGxGetDeviceHeight() * 0.9;
	optionsSprite->m_W = optionsSprite->GetImage()->GetWidth();
	optionsSprite->m_H = optionsSprite->GetImage()->GetHeight();
	optionsSprite->m_AnchorX = 0.5;
	optionsSprite->m_ScaleX = (float)(IwGxGetDeviceWidth() * 0.13) / optionsSprite->GetImage()->GetWidth();
	optionsSprite->m_ScaleY = optionsSprite->m_ScaleX;
	AddChild(optionsSprite);

	float fontScale = (float)IwGxGetScreenWidth() / FONT_DESIGN_WIDTH;
	float actualFontHeight = FONT_HEIGHT * fontScale;

	CLabel* label = new CLabel();
	label->m_X = IwGxGetDeviceWidth() * 0.8;
	label->m_Y = IwGxGetDeviceHeight() / 2 - (IwGxGetDeviceHeight() * 0.1);
	label->m_W = FONT_DESIGN_WIDTH;
	label->m_H = actualFontHeight;
	label->m_Text = "Highscore: ";
	label->m_AlignHor = IW_2D_FONT_ALIGN_LEFT;
	label->m_AlignVer = IW_2D_FONT_ALIGN_TOP;
	label->m_Font = g_pResources->getFont();
	label->m_ScaleX = fontScale;
	label->m_ScaleY = fontScale;
	label->m_Color = CColor(0x00, 0x00, 0x00, 0xff);
	label->m_Angle = 270;
	AddChild(label);

	playButton = new CSprite();
	playButton->SetImage(g_pResources->getPlayButton());
	playButton->m_X = w / 2.0f;
	playButton->m_Y = h / 2.0f;
	playButton->m_W = playButton->GetImage()->GetWidth();
	playButton->m_H = playButton->GetImage()->GetHeight();
	playButton->m_AnchorX = 0.5f;
	playButton->m_AnchorY = 0.5f;
	playButton->m_ScaleX = (float)(w * 0.4) / playButton->GetImage()->GetWidth();
	playButton->m_ScaleY = playButton->m_ScaleX;
	AddChild(playButton);
	// Start menu music
	//Audio::PlayMusic("audio/frontend.mp3");
	count = 0;

	
	s3eFile* fh = s3eFileOpen("highscores.txt", "rb");
	if (fh != NULL)
	{
		s3eFileRead(&highScore, sizeof(highScore), 1, fh);
		s3eFileClose(fh);

		if (highScore < 0)
		{
			highScore = 0;
		}
	}
	char str[16];
	snprintf(str, 16, "%d", highScore);

	label->m_Text += str;
}

void MainMenu::OutputLine(int i)
{
	char str[16];
	snprintf(str, 16, "%d", i);
	s3eDebugOutputString(str);
}

