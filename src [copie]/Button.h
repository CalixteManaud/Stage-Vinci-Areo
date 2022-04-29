#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

class Button
{
private:
	sf::RectangleShape m_shape;
	sf::Text m_text;

	bool m_dragging;
	sf::Vector2f m_dragOffset;

	bool m_modifyingValue;
	std::string m_newValue;
	bool m_firstChar;

	bool m_selected;

	void centerText();

public:
	Button(const sf::Font& font);

	sf::Vector2f getPosition() const;
	sf::Vector2f getSize() const;
	std::string getValue() const;
	sf::Color getColor() const;
	bool getModifyingValue() const;
	bool getSelected() const;
	
	void setPosition(const sf::Vector2f& position);
	void setSize(const sf::Vector2f& size);
	void setValue(std::string value);
	void setColor(const sf::Color& color);
	void setSelected(bool selected);

	bool isPressed(const sf::RenderWindow& window, const sf::Event& event) const;

	void update(const sf::RenderWindow& window, const sf::Event& event);
	void render(sf::RenderWindow& window, bool renderText) const;
};