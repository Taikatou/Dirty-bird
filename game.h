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

#if !defined(__GAME_H__)
#define __GAME_H__

#include "scene.h"
#include "man.h"
#include "food.h"
#include "poo.h"
#include "s3eAccelerometer.h"


// Constants that are used to fit the game to different screen sizes

typedef std::vector<CSprite*> csprite_vec;

typedef std::vector<Man*> man_vec;

typedef std::vector<Food*> food_vec;

typedef std::vector<Poo*> poo_vec;

/**
 * @enum  eGameState
 *
 * @brief List of game states.
 */
class Game : public Scene
{
protected:
	CSprite*	bird;
	CSprite*	pauseSprite;
	CSprite*	endGame;
	CSprite*	newHighScore;
	CLabel*		label;

	int			edge;
	int			up;
	int			counter;
	int			highScore;
	void		MoveBird();
	bool		accelerometer;
	int			DefaultX;
	int			DefaultY;
	int			pooChecker;
	int			manChecker;
	int			manPosCheck;
	int			foodChecker;
	bool		gameOver;
	poo_vec pooArray;

	csprite_vec splashArray;
	man_vec		manArray;
	csprite_vec boatArray;

	food_vec foodArray;

public:

private:
	void            initUI();
	void			AddMan();
	void			CheckCollision(Man* m);
	void			Shoot(Man* m);
public:
    Game() {}
    ~Game();

    // initialise the game
    void            Init();

	void			Poop();

    // Update the game
    void            Update(float deltaTime = 0.0f, float alphaMul = 1.0f);

	void			pauseGame();
    // Render the game
	void            Render();
	void			NewGame();
	void			OutputLine(int i);

	void			setHighScore(int i)		{ highScore = i; }
	
	void			CalibrateButton()
	{
		DefaultX = s3eAccelerometerGetX();
		DefaultY = s3eAccelerometerGetY();
	}
	void			RestartGame();
};


#endif  // __GAME_H__


