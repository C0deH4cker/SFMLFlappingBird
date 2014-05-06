//
//  Level.cpp
//  FlappingBird
//
//  Created by C0deH4cker on 1/30/14.
//  Copyright (c) 2014 C0deH4cker. All rights reserved.
//

#include "Level.h"
#include <iostream>
#include <math.h>
#include <time.h>
#include "helpers.h"

const int Level::scrollSpeed = 230;
const float Level::pipeDistance = 240.0f;
const float Level::pipeSpread = 65.0f;
const sf::Vector2f Level::groundScale(4.0f, 3.0f);

Level::Level(sf::RenderTarget* target)
: distance(0.0f), rng((unsigned)time(NULL)), paused(false), started(false),
distribution(0.1f, 0.7f), canvas(target) {
	sf::Vector2f size(canvas->getSize());
	
	tex.loadFromFile(resourcePath() + "spritesheet.png");
	
	score.setTexture(tex);
	
	sf::Vector2i bgTexSize(144, 256);
	background.setTexture(tex);
	background.setTextureRect({0, 0, bgTexSize.x, bgTexSize.y});
	setSize(background, size);
	
	sf::Vector2i groundSize(154, 54);
	ground.setTexture(tex);
	ground.setTextureRect({146, 0, groundSize.x, groundSize.y});
	
	float groundTop = size.y - groundSize.y * groundScale.y / 1.5f;
	ground.setPosition(0.0f, groundTop);
	ground.setScale(groundScale);
	
	pipeTop.setTexture(tex);
	pipeTop.setTextureRect({302, 0, 26, 135});
	pipeTop.setScale(Pipe::scale, Pipe::scale);
	
	pipeBottom.setTexture(tex);
	pipeBottom.setTextureRect({330, 0, 26, 121});
	pipeBottom.setScale(Pipe::scale, Pipe::scale);
	
	bird = new Bird(tex, groundTop, size);
}

Level::~Level() {
	delete bird;
}

void Level::update(float deltaTime) {
	if(paused) return;
	
	float dx = scrollSpeed * deltaTime;
	
	if(!bird->isDead()) {
		ground.move(-dx, 0.0f);
		float overlap = canvas->getSize().x - right(ground);
		sf::Vector2f groundPos(ground.getPosition());
		
		if(overlap > 0.0f) {
			ground.setPosition(fmodf(groundPos.x, 28.0f), groundPos.y);
		}
	}
	
	if(!started) return;
	
	bird->update(deltaTime);
	
	if(bird->isDead()) return;
	
	auto it = pipes.begin();
	while(it != pipes.end()) {
		it->scroll(dx);
		
		if(it->didScore(bird))
			++score;
		
		if(it->collides(bird)) {
			bird->die();
			showScore();
		}
		
		if(it->offScreen()) {
			it = pipes.erase(it);
		}
		else ++it;
	}
	
	float fromEdge = fmodf(distance, pipeDistance) + dx - pipeDistance;
	
	// Should only execute once at max unless FPS < 1
	while(fromEdge > 0.0f) {
		addPipe(fromEdge);
		fromEdge -= pipeDistance;
	}
	
	distance += dx;
}

void Level::draw() {
	canvas->draw(background);
	
	for(auto it = pipes.begin(); it != pipes.end(); ++it) {
		canvas->draw(*it);
	}
	
	bird->animate();
	canvas->draw(*bird);
	canvas->draw(ground);
	canvas->draw(score);
}

void Level::keyPressed(sf::Keyboard::Key key) {
	switch(key) {
		case sf::Keyboard::Space:
			if(paused)
				resume();
			if(!started)
				started = true;
			bird->flap();
			break;
		
		case sf::Keyboard::P:
			if(paused)
				resume();
			else
				pause();
			break;
		
		case sf::Keyboard::R:
			restart();
			break;
		
		default:
			break;
	}
}

void Level::pause() {
	paused = true;
	bird->pause();
}

void Level::resume() {
	paused = false;
	bird->resume();
}

bool Level::isPaused() const {
	return paused;
}

void Level::restart() {
	bird->reset();
	
	distance = 0.0f;
	pipes.clear();
	score.setValue(0);
	paused = false;
	started = false;
}

void Level::addPipe(float scrolled) {
	float x, y;
	
	sf::Vector2f size(canvas->getSize());
	
	x = size.x - scrolled;
	
	/* arcsin(2x-1)/pi+0.5 */
	y = size.y * (asinf(2.0f * distribution(rng) - 1.0f) / M_PI + 0.5f);
	
	Pipe pipe(sf::Vector2f(x, y), &pipeTop, &pipeBottom);
	pipes.push_back(pipe);
}

void Level::showScore() {
	// TODO: implement final score display
}

