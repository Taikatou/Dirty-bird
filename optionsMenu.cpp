#include "OptionsMenu.h"
#include "IwGx.h"
#include "input.h"
#include "resources.h"
#include "game.h"
#include "scene.h"

#define FONT_DESIGN_WIDTH 320
#define FONT_HEIGHT 15

OptionsMenu::~OptionsMenu()
{
}

void OptionsMenu::Update(float deltaTime, float alphaMul)
{
	if (!m_IsActive)
		return;

	Scene::Update(deltaTime, alphaMul);

	// Detect screen tap
	if (m_IsInputActive && m_Manager->GetCurrent() == this && !g_pInput->m_Touched && g_pInput->m_PrevTouched)
	{
		g_pInput->Reset();

		if (newGameButton->HitTest(g_pInput->m_X, g_pInput->m_Y))
		{
			s3eFile* file = s3eFileOpen("highscores.txt", "wb");
			int highScore = 0;
			if (file != NULL)
			{
				s3eFileWrite(&highScore, sizeof(highScore), 1, file);
				s3eFileClose(file);
			}

			Game* game = (Game*)g_pSceneManager->Find("game");
			game->setHighScore(highScore);
		}
	}
}


void OptionsMenu::Render()
{
	Scene::Render();
}

void OptionsMenu::Init()
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


	newGameButton = new CSprite();
	newGameButton->SetImage(g_pResources->getNewButton());
	newGameButton->m_X = IwGxGetScreenWidth() / 2;
	newGameButton->m_Y = (float)IwGxGetScreenHeight() / 2;
	newGameButton->m_W = newGameButton->GetImage()->GetWidth();
	newGameButton->m_H = newGameButton->GetImage()->GetHeight();
	newGameButton->m_AnchorX = 0.5f;
	newGameButton->m_AnchorY = 0.5;
	newGameButton->m_ScaleX = (float)(IwGxGetScreenWidth() / 4) / newGameButton->GetImage()->GetWidth();
	newGameButton->m_ScaleY = newGameButton->m_ScaleX;
	AddChild(newGameButton);


	float fontScale = (float)IwGxGetScreenWidth() / FONT_DESIGN_WIDTH;

	float actualFontHeight = FONT_HEIGHT * fontScale;

	CLabel* newlabel = new CLabel();
	newlabel->m_X = newGameButton->m_Y - (IwGxGetDeviceHeight() * 0.07);;
	newlabel->m_Y = newGameButton->m_Y - (IwGxGetDeviceHeight() * 0.05);
	newlabel->m_W = FONT_DESIGN_WIDTH;
	newlabel->m_H = actualFontHeight;
	newlabel->m_Text = "Reset High Score";
	newlabel->m_AlignHor = IW_2D_FONT_ALIGN_LEFT;
	newlabel->m_AlignVer = IW_2D_FONT_ALIGN_TOP;
	newlabel->m_Font = g_pResources->getFont();
	newlabel->m_ScaleX = fontScale;
	newlabel->m_ScaleY = fontScale;
	newlabel->m_Color = CColor(0x00, 0x00, 0x00, 0xff);
	newlabel->m_Angle = 270;
	AddChild(newlabel);


}