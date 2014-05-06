//
//  FlappingBird.cpp
//  FlappingBird
//
//  Created by C0deH4cker on 1/30/14.
//  Copyright (c) 2014 C0deH4cker. All rights reserved.
//

#include "FlappingBird.h"

FlappingBird::FlappingBird()
: window(sf::VideoMode(480, 640), "FlappingBird",
         sf::Style::Titlebar | sf::Style::Close) {
	window.setVerticalSyncEnabled(true);
	level = new Level(&window);
	
	// Only display the mouse if it's outside of the window
	sf::Vector2i mouse(sf::Mouse::getPosition(window));
	sf::Vector2u size(window.getSize());
	bool mouseInWindow(mouse.x >= 0 && mouse.y >= 0 &&
	                   mouse.x < size.x && mouse.y < size.y);
	window.setMouseCursorVisible(!mouseInWindow);
}

FlappingBird::~FlappingBird() {
	delete level;
}

void FlappingBird::run() {
	sf::Clock timer;
	
	while(window.isOpen()) {
		sf::Event event;
		window.pollEvent(event);
		
		switch(event.type) {
			case sf::Event::Closed:
				window.close();
				break;
			
			case sf::Event::KeyPressed:
				if(event.key.code == sf::Keyboard::Escape) {
					window.close();
					break;
				}
				
				level->keyPressed(event.key.code);
				break;
			
			case sf::Event::MouseEntered:
				window.setMouseCursorVisible(false);
				break;
			
			case sf::Event::MouseLeft:
				window.setMouseCursorVisible(true);
				break;
			
			default:
				break;
		}
		
		level->update(timer.restart().asSeconds());
		level->draw();
		
		window.display();
	}
}

