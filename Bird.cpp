//
//  Bird.cpp
//  FlappingBird
//
//  Created by C0deH4cker on 1/30/14.
//  Copyright (c) 2014 C0deH4cker. All rights reserved.
//

#include "Bird.h"
#include <cmath>
#include "helpers.h"

const float Bird::scale = 2.5f;
const float Bird::flapSpeed = -515.0f;
const float Bird::maxSpeed = 680.0f;
const float Bird::gravity = 2000.0f;
const double Bird::defaultFps = 2.0;
const int Bird::positions[POSCOUNT] = {1,0,0,0,1,1,2,2,2,1};

const int w = 17, h = 12;

Bird::Bird(const sf::Texture& sprites, float groundTop,
           const sf::Vector2f& size)
: speed(0.0f), groundTop(groundTop), dead(false), started(false), paused(false),
curFrameIndex(0), fps(POSCOUNT * defaultFps), extra(0.0), onGround(false),
startingPos(0.2f * size.x, 0.5f * size.y), pos(startingPos.y) {
	for(unsigned i = 0; i < 3; i++) {
		frames[i].setTexture(sprites);
		frames[i].setScale(scale, scale);
		frames[i].setOrigin(0.5f * w, 0.5f * h);
		frames[i].setPosition(startingPos);
	}
	
	frames[0].setTextureRect({223, 124, w, h});
	frames[1].setTextureRect({264,  90, w, h});
	frames[2].setTextureRect({264,  64, w, h});
}

void Bird::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	sf::Sprite cur(frames[curFrame]);
	
	float elapsed = ((paused ? pausedTime : timer.getElapsedTime()) -
	                 skippedTime).asSeconds();
	
	float dy = started ? 0.0f : 6.0f * sinf(8.0f * elapsed);
	
	cur.setPosition(startingPos.x, pos + dy);
	cur.setRotation(-getRotation() * RAD2DEG);
	
	target.draw(cur, states);
}

void Bird::update(float deltaTime) {
	if(onGround) return;
	
	speed += gravity * deltaTime / 2.0f;
	if(speed > maxSpeed) {
		speed = maxSpeed;
	}
	
	pos += speed * deltaTime;
	speed += gravity * deltaTime / 2.0f;
	if(speed > maxSpeed) {
		speed = maxSpeed;
	}
	
	if(pos + scale * h / 2.0f >= groundTop) {
		die();
		onGround = true;
		
		// Down one pixel
		pos = groundTop + scale * (1.0f - w / 2.0f);
	}
}

void Bird::animate() {
	const float maxFps = 3.5f;
	const float endtime = 1.2f;
	const float coef = maxFps / (endtime*endtime);
	
	if(started) {
		float val = (timer.getElapsedTime() - skippedTime).asSeconds();
		double freq = CLAMP(maxFps - coef * val*val, 0.0f, maxFps);
		
		setFlapsPerSec(freq);
	}
	
	curFrame = getFrame();
}

void Bird::flap() {
	if(dead) return;
	started = true;
	timer.restart();
	skippedTime = sf::microseconds(0);
	wingTimer.restart();
	wingSkippedTime = sf::microseconds(0);
	if(pos < 0.0f) return;
	speed = flapSpeed;
}

void Bird::die() {
	dead = true;
}

void Bird::reset() {
	pos = startingPos.y;
	speed = 0.0f;
	timer.restart();
	skippedTime = sf::microseconds(0);
	wingTimer.restart();
	wingSkippedTime = sf::microseconds(0);
	setFlapsPerSec(defaultFps);
	curFrameIndex = 0;
	dead = false;
	started = false;
	paused = false;
	onGround = false;
}

void Bird::pause() {
	if(paused) return;
	
	pausedTime = timer.getElapsedTime();
	wingPausedTime = wingTimer.getElapsedTime();
	paused = true;
}

void Bird::resume() {
	if(!paused) return;
	
	skippedTime += timer.getElapsedTime() - pausedTime;
	wingSkippedTime += wingTimer.getElapsedTime() - wingPausedTime;
	paused = false;
}

bool Bird::isDead() const {
	return dead;
}

sf::FloatRect Bird::getBBox() const {
	// Bounding box is a square of dimensions height X height.
	// Makes it easier to work with in terms of rotation, and
	// still quite accurate.
	float offset = (w - h) / 2.0f;
	float halfHeight = scale * h / 2.0f;
	return sf::FloatRect(startingPos.x + scale * (offset - w / 2.0f),
	                     pos - halfHeight,
	                     scale * h, scale * h);
}


float Bird::getRotation() const {
	const float maxrot = M_PI / 10.0f;
	const float minrot = -M_PI_2;
	const float endtime = 0.4f;
	const float offset = 0.5f * endtime;
	const float coef = (maxrot - minrot) / (endtime*endtime);
	
	if(!started) return 0.0f;
	if(onGround) return minrot;
	
	float val = MAX((timer.getElapsedTime() - skippedTime).asSeconds() - offset,
	                0.0f);
	
	return CLAMP(maxrot - coef * val*val, minrot, maxrot);
}

void Bird::setFlapsPerSec(double flaps) {
	fps = POSCOUNT * flaps;
}

int Bird::getFrame() {
	if(paused)
		return curFrame;
	
	if(fps <= 0.0 || onGround)
		return positions[0];
	
	double elapsed = (wingTimer.getElapsedTime() -
	                  wingSkippedTime).asSeconds() + extra;
	double freq = 1.0 / fps;
	
	if(elapsed > freq) {
		curFrameIndex = (int)(curFrameIndex + elapsed / freq) % POSCOUNT;
		extra = fmod(elapsed, freq);
		wingTimer.restart();
		wingSkippedTime = sf::microseconds(0);
	}
	
	return positions[curFrameIndex];
}

