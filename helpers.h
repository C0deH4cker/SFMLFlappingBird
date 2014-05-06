//
//  helpers.h
//  FlappingBird
//
//  Created by C0deH4cker on 5/5/14.
//  Copyright (c) 2014 C0deH4cker. All rights reserved.
//

#ifndef _FB_HELPERS_H_
#define _FB_HELPERS_H_

#include <string>
#include <SFML/Graphics.hpp>
#include <cmath>

#define ABS(x) ({ \
	__typeof__(x) _x = (x); \
	_x < 0 ? -_x : _x; \
})

#define CMP(op, a, b) ({ \
	__typeof__(a) _a = (a); \
	__typeof__(b) _b = (b); \
	(_a op _b) ? _a : _b; \
})
#define MIN(a, b) CMP(<, a, b)
#define MAX(a, b) CMP(>, a, b)

#define CLAMP(x, lo, hi) MAX(lo, MIN(x, hi))

#define ARRSIZE(arr) (sizeof(arr) / sizeof(arr[0]))

#define RAD2DEG (180.0 / M_PI)


std::string resourcePath();
float right(const sf::Sprite& spr);
float bottom(const sf::Sprite& spr);
float midX(const sf::Sprite& spr);
float midY(const sf::Sprite& spr);
sf::Vector2f getCenter(const sf::Sprite& spr);
sf::Vector2f getSize(const sf::Sprite& spr);
float spriteWidth(const sf::Sprite& spr);
float spriteHeight(const sf::Sprite& spr);
void setSize(sf::Sprite& spr, sf::Vector2f size);

template <typename T>
T sqrdistance(const sf::Vector2<T>& a, const sf::Vector2<T> b) {
	T dx = a.x - b.x;
	T dy = a.y - b.y;
	
	return dx*dx + dy*dy;
}

template <typename T>
T distance(const sf::Vector2<T>& a, const sf::Vector2<T> b) {
	return sqrt(sqrdistance(a, b));
}

template <typename T>
T sqrdistance(const sf::Vector3<T>& a, const sf::Vector3<T> b) {
	T dx = a.x - b.x;
	T dy = a.y - b.y;
	T dz = a.z - b.z;
	
	return dx*dx + dy*dy + dz*dz;
}

template <typename T>
T distance(const sf::Vector3<T>& a, const sf::Vector3<T> b) {
	return sqrt(sqrdistance(a, b));
}

template <typename T>
sf::Vector2<T> topLeft(const sf::Rect<T>& rect) {
	return {rect.left, rect.top};
}

template <typename T>
sf::Vector2<T> topRight(const sf::Rect<T>& rect) {
	return {rect.left + rect.width, rect.top};
}

template <typename T>
sf::Vector2<T> bottomLeft(const sf::Rect<T>& rect) {
	return {rect.left, rect.top + rect.height};
}

template <typename T>
sf::Vector2<T> bottomRight(const sf::Rect<T>& rect) {
	return {rect.left + rect.width, rect.top + rect.height};
}

template <typename T>
T right(const sf::Rect<T>& rect) {
	return rect.left + rect.width;
}

template <typename T>
T bottom(const sf::Rect<T>& rect) {
	return rect.top + rect.height;
}

template <typename T>
T midX(const sf::Rect<T>& rect) {
	return rect.left + rect.width / 2;
}

template <typename T>
T midY(const sf::Rect<T>& rect) {
	return rect.top + rect.height / 2;
}

template <typename T>
sf::Vector2<T> getCenter(const sf::Rect<T>& rect) {
	return {rect.left + rect.width / 2, rect.top + rect.height / 2};
}

template <typename T>
sf::Vector2<T> getSize(const sf::Rect<T>& rect) {
	return {rect.width, rect.height};
}

template <typename T>
void setSize(sf::Rect<T>& rect, const sf::Vector2<T>& size) {
	rect.width = size.x;
	rect.height = size.y;
}

#endif /* _FB_HELPERS_H_ */
