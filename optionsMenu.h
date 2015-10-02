#if !defined(__OPTIONSMENU_H__)
#define __OPTIONSMENU_H__

#include "scene.h"

class OptionsMenu : public Scene
{
protected:
	CSprite* newGameButton;
public:

public:
	OptionsMenu() {}
	~OptionsMenu();

	// initialise the menu
	void            Init();

	// Update the menu
	void            Update(float deltaTime = 0.0f, float alphaMul = 1.0f);

	// Render the menu
	void            Render();
};
#endif