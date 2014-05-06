//
//  FlappingBird.h
//  FlappingBird
//
//  Created by C0deH4cker on 1/30/14.
//  Copyright (c) 2014 C0deH4cker. All rights reserved.
//

#ifndef _FB_FLAPPINGBIRD_H_
#define _FB_FLAPPINGBIRD_H_

#include <SFML/Window.hpp>
#include "Level.h"

class FlappingBird {
public:
	FlappingBird();
	~FlappingBird();
	
	void run();
	
private:
	sf::RenderWindow window;
	Level* level;
};


#endif /* _FB_FLAPPINGBIRD_H_ */
