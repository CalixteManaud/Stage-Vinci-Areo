#include "Button.h"

void Button::centerText()
{
	m_text.setPosition(
		std::roundf(m_shape.getPosition().x + m_shape.getSize().x * 0.5f - m_text.getGlobalBounds().width * 0.5f),
		std::roundf(m_shape.getPosition().y + m_shape.getSize().y * 0.5f - m_text.getGlobalBounds().height)
	);

	m_text.setCharacterSize(static_cast<int>(std::min(m_shape.getSize().x * 0.4f, m_shape.getSize().y * 0.4f)));
}

Button::Button(const sf::Font& font) :
	m_shape(sf::Vector2f(50.0f, 40.0f)),
	m_dragging(false),
	m_selected(false),
	m_modifyingValue(false),
	m_newValue(""),
	m_firstChar(false)
{
	m_shape.setOutlineColor(sf::Color::Blue);
	m_text.setFont(font);
	m_text.setString("0");
	m_text.setFillColor(sf::Color::Black);
	centerText();
}

sf::Vector2f Button::getPosition() const
{
	return m_shape.getPosition();
}
sf::Vector2f Button::getSize() const
{
	return m_shape.getSize();
}
std::string Button::getValue() const
{
	return m_text.getString();
}
sf::Color Button::getColor() const
{
	return m_shape.getFillColor();
}
bool Button::getModifyingValue() const
{
	return m_modifyingValue;
}
bool Button::getSelected() const
{
	return m_selected;
}

void Button::setPosition(const sf::Vector2f& position)
{
	m_shape.setPosition(position);
	centerText();
}
void Button::setSize(const sf::Vector2f& size)
{
	m_shape.setSize(size);
	centerText();
}
void Button::setValue(std::string value)
{
	m_text.setString(value);
	centerText();
}
void Button::setColor(const sf::Color& color)
{
	m_shape.setFillColor(color);
}
void Button::setSelected(bool selected)
{
	m_selected = selected;

	if(m_selected)
		m_shape.setOutlineThickness(2.0f);
	else
		m_shape.setOutlineThickness(0.0f);

	centerText();
}

bool Button::isPressed(const sf::RenderWindow& window, const sf::Event& event) const
{	
	return (m_shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window))) && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left);
}

void Button::update(const sf::RenderWindow& window, const sf::Event& event)
{
	if (isPressed(window, event))
	{
		m_dragging = true;
		m_dragOffset = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)) - m_shape.getPosition();
	}

	if (!m_selected)
		return;

	if (m_dragging)
	{
		m_shape.setPosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)) - m_dragOffset);
		centerText();
	}
	
	switch (event.type)
	{
	case sf::Event::MouseButtonReleased:
		if(event.mouseButton.button == sf::Mouse::Left)
			m_dragging = false;
		break;
	case sf::Event::KeyPressed:
		if (event.key.code == sf::Keyboard::Enter && m_modifyingValue)
		{
			setValue(m_newValue);
			m_modifyingValue = false;
		}
		else
		{
			switch (event.key.code)
			{
			case sf::Keyboard::X:
				setSize(sf::Vector2f(m_shape.getSize().x + 3.0f, m_shape.getSize().y));
				setPosition(sf::Vector2f(m_shape.getPosition().x - 1.5f, m_shape.getPosition().y));
				break;
			case sf::Keyboard::Y:
				setSize(sf::Vector2f(m_shape.getSize().x, m_shape.getSize().y + 3.0f));
				setPosition(sf::Vector2f(m_shape.getPosition().x, m_shape.getPosition().y - 1.5f));
				break;
			case sf::Keyboard::C:
				if (m_shape.getSize().x > 8.0f)
				{
					setSize(sf::Vector2f(m_shape.getSize().x - 3.0f, m_shape.getSize().y));
					setPosition(sf::Vector2f(m_shape.getPosition().x + 1.5f, m_shape.getPosition().y));
				}
				break;
			case sf::Keyboard::U:
				if (m_shape.getSize().y > 8.0f)
				{
					setSize(sf::Vector2f(m_shape.getSize().x, m_shape.getSize().y - 3.0f));
					setPosition(sf::Vector2f(m_shape.getPosition().x, m_shape.getPosition().y + 1.5f));
				}
				break;
			case sf::Keyboard::V:
				m_modifyingValue = true;
				m_newValue = "";
				m_firstChar = true;
				break;
			default:
				break;
			}
		}
		break;
	case sf::Event::TextEntered:
		if (m_modifyingValue)
		{
			if (m_firstChar)
				m_firstChar = false;
			else
				m_newValue += static_cast<char>(event.text.unicode);
		}
		break;
	default:
		break;
	}
}
void Button::render(sf::RenderWindow& window, bool renderText) const
{
	window.draw(m_shape);

	if(renderText)
		window.draw(m_text);
}
