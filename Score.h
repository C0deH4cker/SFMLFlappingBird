//
//  Score.h
//  FlappingBird
//
//  Created by C0deH4cker on 2/8/14.
//  Copyright (c) 2014 C0deH4cker. All rights reserved.
//

#ifndef _FB_SCORE_H_
#define _FB_SCORE_H_

#include <SFML/Graphics.hpp>

class Score: public sf::Drawable {
public:
	Score();
	
	void setTexture(const sf::Texture& tex);
	
	void setValue(int points);
	Score& operator++();
	
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	
	const static float spacing, scale;
	int value;
	sf::Sprite digitSprites[10];
};


#endif /* _FB_SCORE_H_ */
