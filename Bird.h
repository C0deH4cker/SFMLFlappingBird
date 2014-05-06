//
//  Bird.h
//  FlappingBird
//
//  Created by C0deH4cker on 1/30/14.
//  Copyright (c) 2014 C0deH4cker. All rights reserved.
//

#ifndef _FB_BIRD_H_
#define _FB_BIRD_H_

#include <SFML/Graphics.hpp>

class Bird: public virtual sf::Drawable {
public:
	Bird(const sf::Texture& sprites, float groundHeight, const sf::Vector2f& size);
	
	void update(float deltaTime);
	void animate();
	
	void flap();
	void die();
	void reset();
	void pause();
	void resume();
	
	bool isDead() const;
	
	sf::FloatRect getBBox() const;
	
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	
	const static float scale, flapSpeed, maxSpeed, gravity;
	const static double defaultFps;
	const static int POSCOUNT = 10;
	const static int positions[POSCOUNT];
	
	double fps, extra;
	bool dead, started, paused, onGround;
	sf::Vector2f startingPos;
	float pos, groundTop;
	float speed;
	int curFrameIndex, curFrame;
	sf::Clock timer, wingTimer;
	sf::Time pausedTime, skippedTime, wingPausedTime, wingSkippedTime;
	sf::Sprite frames[3];
	
	float getRotation() const;
	void setFlapsPerSec(double fps);
	int getFrame();
};


#endif /* _FB_BIRD_H_ */
