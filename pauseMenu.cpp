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

#include "PauseMenu.h"
#include "IwGx.h"
#include "input.h"
#include "resources.h"
#include "game.h"
#include "scene.h"
#define FONT_DESIGN_WIDTH 320
#define FONT_HEIGHT 15


#define GRAPHIC_DESIGN_WIDTH    768

PauseMenu::~PauseMenu()
{
}

void PauseMenu::Update(float deltaTime, float alphaMul)
{
	if (!m_IsActive)
		return;

	Scene::Update(deltaTime, alphaMul);

	// Detect screen tap
	if (m_IsInputActive && m_Manager->GetCurrent() == this && !g_pInput->m_Touched && g_pInput->m_PrevTouched)
	{
		g_pInput->Reset();

		if (continueGameButton->HitTest(g_pInput->m_X, g_pInput->m_Y))
		{
			// Switch to game scene
			Game* game = (Game*)g_pSceneManager->Find("game");
			g_pSceneManager->SwitchTo(game);

			// Restore button alpha state
			/*PauseMenu* menu = (PauseMenu*)g_pSceneManager->Find("pausemenu");
			menu->getContinueGameButton()->m_Alpha = 1.0f;*/
		}
		else if (newGameButton->HitTest(g_pInput->m_X, g_pInput->m_Y))
		{
			// Switch to game scene
			Game* game = (Game*)g_pSceneManager->Find("game");
			game->RestartGame();
			g_pSceneManager->SwitchTo(game);
		}
		else if (calibrateButton->HitTest(g_pInput->m_X, g_pInput->m_Y))
		{
			Game* game = (Game*)g_pSceneManager->Find("game");
			game->CalibrateButton();
			g_pSceneManager->SwitchTo(game);
		}
	}
}


void PauseMenu::Render()
{
	Scene::Render();
}

void PauseMenu::Init()
{

	// Create menu background
	CSprite* background = new CSprite();
	background->m_X = (float)IwGxGetScreenWidth() / 2;
	background->m_Y = (float)IwGxGetScreenHeight() / 2;
	background->SetImage(g_pResources->getMenuBG());
	background->m_AnchorX = 0.5;
	background->m_AnchorY = 0.5;
	// Fit background to screen size
	background->m_ScaleX = (float)IwGxGetScreenWidth() / background->GetImage()->GetWidth();
	background->m_ScaleY = (float)IwGxGetScreenHeight() / background->GetImage()->GetHeight();
	AddChild(background);

	// Create Continue Game button


	continueGameButton = new CSprite();
	continueGameButton->m_X = (float)IwGxGetScreenWidth() * 0.66;
	continueGameButton->m_Y = (float)IwGxGetScreenHeight() / 3;
	continueGameButton->m_AnchorX = 0.5f;
	continueGameButton->m_AnchorY = 0.5f;
	continueGameButton->SetImage(g_pResources->getMenuButton());

	continueGameButton->m_ScaleX = (float)(IwGxGetScreenWidth() / 4) / continueGameButton->GetImage()->GetWidth();
	continueGameButton->m_ScaleY = continueGameButton->m_ScaleX;
	continueGameButton->m_Angle = 270.0f;
	AddChild(continueGameButton);


	float fontScale = (float)IwGxGetScreenWidth() / FONT_DESIGN_WIDTH;

	float actualFontHeight = FONT_HEIGHT * fontScale;
	CLabel* label = new CLabel();
	label->m_X = (IwGxGetScreenWidth() / 2);
	label->m_Y = continueGameButton->m_Y - (IwGxGetDeviceHeight() * 0.07);
	label->m_W = FONT_DESIGN_WIDTH;
	label->m_H = actualFontHeight;
	label->m_Text = "Continue Game";
	label->m_AlignHor = IW_2D_FONT_ALIGN_LEFT;
	label->m_AlignVer = IW_2D_FONT_ALIGN_TOP;
	label->m_Font = g_pResources->getFont();
	label->m_ScaleX = fontScale;
	label->m_ScaleY = fontScale;
	label->m_Color = CColor(0x00, 0x00, 0x00, 0xff);
	label->m_Angle = 270;
	AddChild(label);

	// Create New  Game button
	newGameButton = new CSprite();
	newGameButton->SetImage(g_pResources->getNewButton());
	newGameButton->m_X = continueGameButton->m_X;
	newGameButton->m_Y = (float)IwGxGetScreenHeight() - continueGameButton->m_Y;
	newGameButton->m_W = newGameButton->GetImage()->GetWidth();
	newGameButton->m_H = newGameButton->GetImage()->GetHeight();
	newGameButton->m_AnchorX = 0.5f;
	newGameButton->m_AnchorY = 0.5;
	newGameButton->m_ScaleX = (float)(IwGxGetScreenWidth() / 4) / newGameButton->GetImage()->GetWidth();
	newGameButton->m_ScaleY = newGameButton->m_ScaleX;
	AddChild(newGameButton);

	CLabel* newlabel = new CLabel();
	newlabel->m_X = label->m_X;
	newlabel->m_Y = newGameButton->m_Y - (IwGxGetDeviceHeight() * 0.05);
	newlabel->m_W = FONT_DESIGN_WIDTH;
	newlabel->m_H = actualFontHeight;
	newlabel->m_Text = "New Game";
	newlabel->m_AlignHor = IW_2D_FONT_ALIGN_LEFT;
	newlabel->m_AlignVer = IW_2D_FONT_ALIGN_TOP;
	newlabel->m_Font = g_pResources->getFont();
	newlabel->m_ScaleX = fontScale;
	newlabel->m_ScaleY = fontScale;
	newlabel->m_Color = CColor(0x00, 0x00, 0x00, 0xff);
	newlabel->m_Angle = 270;
	AddChild(newlabel);

	// Create New  Game button
	calibrateButton = new CSprite();
	calibrateButton->SetImage(g_pResources->getRecalImage());
	calibrateButton->m_X = (float)IwGxGetScreenWidth() / 4;
	calibrateButton->m_Y = (float)IwGxGetScreenHeight() / 2;
	calibrateButton->m_W = calibrateButton->GetImage()->GetWidth();
	calibrateButton->m_H = calibrateButton->GetImage()->GetHeight();
	calibrateButton->m_AnchorX = 0.5f;
	calibrateButton->m_AnchorY = 0.5;
	calibrateButton->m_ScaleX = newGameButton->m_ScaleX;
	calibrateButton->m_ScaleY = calibrateButton->m_ScaleX;
	AddChild(calibrateButton);

	CLabel* calibrateLabel = new CLabel();
	calibrateLabel->m_X = calibrateButton->m_X - (IwGxGetDeviceWidth() * 0.1);
	calibrateLabel->m_Y = calibrateButton->m_Y - (IwGxGetDeviceHeight() * 0.1);
	calibrateLabel->m_W = FONT_DESIGN_WIDTH;
	calibrateLabel->m_H = actualFontHeight;
	calibrateLabel->m_Text = "Re-Calibrate controls";
	calibrateLabel->m_AlignHor = IW_2D_FONT_ALIGN_LEFT;
	calibrateLabel->m_AlignVer = IW_2D_FONT_ALIGN_TOP;
	calibrateLabel->m_Font = g_pResources->getFont();
	calibrateLabel->m_ScaleX = fontScale;
	calibrateLabel->m_ScaleY = fontScale;
	calibrateLabel->m_Color = CColor(0x00, 0x00, 0x00, 0xff);
	calibrateLabel->m_Angle = 270;
	AddChild(calibrateLabel);

}

