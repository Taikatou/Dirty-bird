#include "splash.h"
#include "resources.h"
#include "game.h"
#include "IwGx.h"

#define SPLASH_ANIM_DURATION		1.0f

SplashManager* g_pSplashManager = 0;

Splash::Splash() : InUse(false)
{
	SetAtlas(g_pResources->getSplashAtlas());
	SetAnimDuration(SPLASH_ANIM_DURATION);
	SetAnimRepeat(1);
	m_AnchorX = 0.5;
	m_AnchorY = 0.5;
}

void Splash::Update(float deltaTime, float alphaMul)
{
	int repeat = m_AnimRepeat;
	CSprite::Update(deltaTime, alphaMul);

	// If animation has finished then disable explosion and return it back to pool
	if (repeat == 1 && m_AnimRepeat == 0)
	{
		InUse = false;
		m_IsVisible = false;
	}
}

SplashManager::~SplashManager()
{

}

Splash* SplashManager::Create(float x, float y, float scale)
{
	for (std::list<Splash*>::iterator it = Splashes.begin(); it != Splashes.end(); ++it)
	{
		// Found a free explosion so re-use it
		if (!(*it)->isInUse())
		{
			(*it)->m_X = x;
			(*it)->m_Y = y;
			(*it)->m_IsVisible = true;
			(*it)->setUsed(true);
			(*it)->SetAnimDuration(SPLASH_ANIM_DURATION);
			(*it)->SetAnimRepeat(1);
			return *it;
		}
	}

	// No explosion found so allocate a new one
	Game* game = (Game*)g_pSceneManager->Find("game");
	Splash* splash = new Splash();
	game->AddChild(splash);
	splash->m_X = x;
	splash->m_Y = y;
	splash->m_Angle = 270.0f;
	splash->m_IsVisible = true;
	splash->setUsed(true);
	splash->SetAnimDuration(SPLASH_ANIM_DURATION);
	splash->SetAnimRepeat(1);
	splash->m_AnchorX = 0.5f;
	splash->m_AnchorY = 0.5f;
	splash->m_ScaleX = (scale * 3) / splash->GetImage()->GetWidth();
	splash->m_ScaleY = splash->m_ScaleX;
	return splash;
}

void SplashManager::ReleaseAll()
{
	// Release all explosions
	for (std::list<Splash*>::iterator it = Splashes.begin(); it != Splashes.end(); ++it)
	{
		(*it)->setUsed(false);
		(*it)->m_IsVisible = false;
	}
}
