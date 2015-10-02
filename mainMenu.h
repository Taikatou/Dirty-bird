#if !defined(__MAINEMENU_H__)
#define __MAINEMENU_H__

#include "scene.h"
#include "game.h"

class MainMenu : public Scene
{
protected:
	// UI components
	CSprite*    playButton;
	CSprite*    playText;
	CSprite*	optionsSprite;
	int			highScore;
	int count;


public:
	MainMenu() {}
	~MainMenu();

	// initialise the menu
	void            Init();

	// Update the menu
	void            Update(float deltaTime = 0.0f, float alphaMul = 1.0f);

	// Render the menu
	void            Render();
	static void     startGame(CTween* pTween);
	void			OutputLine(int i);
	void			setHighScore(int i)		{ highScore = i; }
};

#endif  // __MAINEMENU_H__


