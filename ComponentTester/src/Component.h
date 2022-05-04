#pragma once

#include "Button.h"
#include "USB.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

class Component
{
private:
	std::string m_name;
	sf::Vector2u m_size;

	sf::Texture m_texture;
	sf::Sprite m_sprite;

	sf::Font m_font;
	std::vector<Button> m_buttons;

	std::string m_idVendor;
	std::string m_idProduct;

	std::thread m_thread;
	unsigned int m_group;
	unsigned int m_byte;
	bool m_dataRecieved;

	bool m_editMode;

	bool m_reading;

	bool m_debugInfo;

	void loadButtons();
	void saveButtons();

public:
	Component(const std::string& name, const sf::Vector2u size, const std::string& idVendor, const std::string& idProduct, bool debugInfo);
	~Component();

	std::string getName() const;
	sf::Vector2u getSize() const;

	void start(USB* usb);
	void stop(USB* usb);

	void updateHardware();
	void update(const sf::RenderWindow& window, const sf::Event& event);
	void render(sf::RenderWindow& window) const;
};