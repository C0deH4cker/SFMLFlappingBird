//
//  Score.cpp
//  FlappingBird
//
//  Created by C0deH4cker on 2/8/14.
//  Copyright (c) 2014 C0deH4cker. All rights reserved.
//

#include "Score.h"
#include <string>
#include <SFML/Graphics.hpp>

const float Score::spacing = 1.0f;
const float Score::scale = 3.0f;

const int w = 7, h = 10;

Score::Score()
: value(0) {}

void Score::setTexture(const sf::Texture& tex) {
	for(unsigned i = 0; i < 10; i++) {
		digitSprites[i].setTexture(tex);
	}
	
	digitSprites[0].setTextureRect({288, 100, w, h});
	digitSprites[1].setTextureRect({289, 118, w, h});
	digitSprites[2].setTextureRect({289, 134, w, h});
	digitSprites[3].setTextureRect({289, 150, w, h});
	digitSprites[4].setTextureRect({287, 173, w, h});
	digitSprites[5].setTextureRect({287, 185, w, h});
	digitSprites[6].setTextureRect({165, 245, w, h});
	digitSprites[7].setTextureRect({175, 245, w, h});
	digitSprites[8].setTextureRect({185, 245, w, h});
	digitSprites[9].setTextureRect({195, 245, w, h});
}

Score& Score::operator++() {
	++value;
	return *this;
}

void Score::setValue(int points) {
	value = points;
}

void Score::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	sf::Vector2f size(target.getSize());
	
	float midX = size.x / 2.0f;
	
	std::string disp = std::to_string(value);
	
	float total = scale * (w * disp.size() + spacing * (disp.size() - 1));
	float left = midX - total / 2.0f;
	float step = scale * (spacing + w);
	
	for(unsigned i = 0; i < disp.size(); i++) {
		int dig = disp[i] - '0';
		
		sf::Sprite cur(digitSprites[dig]);
		
		cur.setPosition(left + i * step, 0.02f * size.y);
		cur.setScale(scale, scale);
		
		target.draw(cur, states);
	}
}

