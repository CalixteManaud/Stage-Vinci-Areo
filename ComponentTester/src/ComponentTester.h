#pragma once

#include "Component.h"
#include "USB.h"

class ComponentTester
{
private:
	sf::RenderWindow m_window;
	sf::Event m_event;

	sf::Clock m_clock;
	float m_deltaTime;

	USB m_usb;

	std::vector<Component*> m_components;
	unsigned int m_activeComponent;

	void update();
	void render();

public:
	ComponentTester();
	~ComponentTester();

	void run();
};