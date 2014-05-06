//
//  Pipe.cpp
//  FlappingBird
//
//  Created by C0deH4cker on 1/30/14.
//  Copyright (c) 2014 C0deH4cker. All rights reserved.
//

#include "Pipe.h"
#include "Level.h"
#include "helpers.h"

const float Pipe::scale = 3.0f;

Pipe::Pipe(sf::Vector2f pos, const sf::Sprite* topImage, const sf::Sprite* bottomImage)
: topSpr(topImage), bottomSpr(bottomImage), scored(false) {
	sf::Vector2f topSize = getSize(*topImage);
	sf::Vector2f bottomSize = getSize(*bottomImage);
	
	sf::Vector2f topPos = sf::Vector2f(pos.x, pos.y - Level::pipeSpread - topSize.y);
	sf::Vector2f bottomPos = sf::Vector2f(pos.x, pos.y + Level::pipeSpread);
	
	topRect = {topPos.x, topPos.y, topSize.x, topSize.y};
	bottomRect = {bottomPos.x, bottomPos.y, bottomSize.x, bottomSize.y};
}

void Pipe::scroll(float x) {
	topRect.left -= x;
	bottomRect.left = topRect.left;
}

void Pipe::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	sf::Sprite topCopy(*topSpr);
	sf::Sprite bottomCopy(*bottomSpr);
	
	topCopy.setPosition(topRect.left, topRect.top);
	bottomCopy.setPosition(bottomRect.left, bottomRect.top);
	
	target.draw(topCopy, states);
	target.draw(bottomCopy, states);
}

bool Pipe::collides(const Bird* bird) const {
	const sf::FloatRect& rect(bird->getBBox());
	
	// Perform bounding box collision detection
	if(!rect.intersects(topRect) && !rect.intersects(bottomRect))
		return false;
	
	// Do more accurate circle-box collision detection
	sf::Vector2f center(getCenter(rect));
	
	// Hit the side of a pipe
	if(center.y <= bottom(topRect) || center.y >= bottomRect.top)
		return true;
	
	// X is between the pipes
	if(center.x >= topRect.left && center.x <= right(topRect)) {
		if(rect.top <= bottom(topRect) || bottom(rect) >= bottomRect.top) {
			return true;
		}
	}
	
	// Bird hit corner of a pipe?
	float radius = rect.width / 2.0f;
	float r2 = radius*radius;
	
	return (sqrdistance(center, bottomLeft(topRect))  < r2 ||
			sqrdistance(center, topLeft(bottomRect))  < r2 ||
			sqrdistance(center, bottomRight(topRect)) < r2 ||
			sqrdistance(center, topRight(bottomRect)) < r2);
}

bool Pipe::didScore(const Bird* bird) {
	if(scored) return false;
	
	bool inside = midX(bird->getBBox()) >= midX(topRect);
	if(inside) {
		scored = true;
	}
	
	return inside;
}

bool Pipe::offScreen() const {
	return right(topRect) <= 0.0f;
}

