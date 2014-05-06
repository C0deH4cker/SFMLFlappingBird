//
//  Level.h
//  FlappingBird
//
//  Created by C0deH4cker on 1/30/14.
//  Copyright (c) 2014 C0deH4cker. All rights reserved.
//

#ifndef _FB_LEVEL_H_
#define _FB_LEVEL_H_

#include <list>
#include <random>
#include <SFML/Graphics.hpp>
#include "Pipe.h"
#include "Score.h"

class Level {
public:
	const static int scrollSpeed;
	const static float pipeDistance;
	const static float pipeSpread;
	const static sf::Vector2f groundScale;
	
	Level(sf::RenderTarget* target);
	~Level();
	
	void update(float deltaTime);
	void draw();
	void keyPressed(sf::Keyboard::Key key);
	
	void pause();
	void resume();
	bool isPaused() const;
	void restart();
	
private:
	Bird* bird;
	bool paused;
	bool started;
	
	sf::RenderTarget* canvas;
	sf::Texture tex;
	Score score;
	sf::Sprite background;
	sf::Sprite pipeTop;
	sf::Sprite pipeBottom;
	sf::Sprite ground;
	
	float distance;
	std::list<Pipe> pipes;
	std::mt19937 rng;
	std::uniform_real_distribution<float> distribution;
	
	void addPipe(float scrolled);
	void showScore();
};


#endif /* _FB_LEVEL_H_ */
