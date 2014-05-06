//
//  helpers.cpp
//  FlappingBird
//
//  Created by C0deH4cker on 5/5/14.
//  Copyright (c) 2014 C0deH4cker. All rights reserved.
//

#include "helpers.h"

float right(const sf::Sprite& spr) {
	return spr.getPosition().x + spr.getScale().x * spr.getTextureRect().width;
}

float bottom(const sf::Sprite& spr) {
	return spr.getPosition().y + spr.getScale().y * spr.getTextureRect().height;
}

float midX(const sf::Sprite& spr) {
	return spr.getPosition().y + spriteWidth(spr) / 2.0f;
}

float midY(const sf::Sprite& spr) {
	return spr.getPosition().x + spriteHeight(spr) / 2.0f;
}

sf::Vector2f getCenter(const sf::Sprite& spr) {
	return spr.getPosition() + getSize(spr) / 2.0f;
}

sf::Vector2f getSize(const sf::Sprite& spr) {
	sf::Vector2f ret(getSize(spr.getTextureRect()));
	sf::Vector2f scale(spr.getScale());
	ret.x *= scale.x;
	ret.y *= scale.y;
	
	return ret;
}

float spriteWidth(const sf::Sprite& spr) {
	return spr.getTextureRect().width * spr.getScale().x;
}

float spriteHeight(const sf::Sprite& spr) {
	return spr.getTextureRect().height * spr.getScale().y;
}

void setSize(sf::Sprite& spr, sf::Vector2f size) {
	sf::Vector2f texSize(getSize(spr.getTextureRect()));
	size.x /= texSize.x;
	size.y /= texSize.y;
	
	spr.setScale(size);
}

