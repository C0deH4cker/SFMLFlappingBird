//
//  Pipe.h
//  FlappingBird
//
//  Created by C0deH4cker on 1/30/14.
//  Copyright (c) 2014 C0deH4cker. All rights reserved.
//

#ifndef _FB_PIPE_H_
#define _FB_PIPE_H_

#include <SFML/Graphics.hpp>
#include "Bird.h"

class Pipe: public virtual sf::Drawable {
public:
	const static float scale;
	
	Pipe(sf::Vector2f pos, const sf::Sprite* topImage, const sf::Sprite* bottomImage);
	
	void scroll(float x);
	bool collides(const Bird* bird) const;
	bool didScore(const Bird* bird);
	bool offScreen() const;
	
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	
	bool scored;
	const sf::Sprite* topSpr;
	sf::FloatRect topRect;
	const sf::Sprite* bottomSpr;
	sf::FloatRect bottomRect;
};


#endif /* _FB_PIPE_H_ */
