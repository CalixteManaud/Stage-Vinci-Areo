#include "Component.h"

void Component::loadButtons()
{
	std::ifstream file("res/components/" + m_name + ".txt");

	if (!file.is_open())
	{
		std::cout << "Failed to load component at res/components/" << m_name << ".txt" << std::endl;
		return;
	}

	std::string line;
	while (std::getline(file, line))
	{
		size_t strPos;
		std::vector<std::string> content;
		while ((strPos = line.find(", ")) != std::string::npos)
		{
			// Source
			content.push_back(line.substr(0, strPos));
			line.erase(0, strPos + 2);
		}

		content.push_back(line);

		Button button(m_font);
		button.setPosition(sf::Vector2f(std::stof(content[0]), std::stof(content[1])));
		button.setSize(sf::Vector2f(std::stof(content[2]), std::stof(content[3])));
		button.setValue(content[4]);

		m_buttons.push_back(button);
	}

	file.close();
}
void Component::saveButtons()
{
	std::ofstream file("res/components/" + m_name + ".txt");

	if (!file.is_open())
	{
		std::cout << "Failed to save component at res/components/" << m_name << ".txt" << std::endl;
		return;
	}

	for (unsigned int i = 0; i < m_buttons.size(); i++)
	{
		file << static_cast<int>(m_buttons[i].getPosition().x) << ", " << static_cast<int>(m_buttons[i].getPosition().y) << ", "
			<< static_cast<int>(m_buttons[i].getSize().x) << ", " << static_cast<int>(m_buttons[i].getSize().y) << ", "
			<< m_buttons[i].getValue();

		if (i != m_buttons.size() - 1)
			file << '\n';
	}

	file.close();
}

Component::Component(const std::string& name, const sf::Vector2u size) :
	m_name(name),
	m_size(size),
	m_texture(),
	m_sprite(),
	m_font(),
	m_buttons(),
	m_editMode(false)
{
	m_texture.loadFromFile("res/textures/" + m_name + ".png");
	m_sprite.setTexture(m_texture);

	m_font.loadFromFile("res/fonts/arial.ttf");
	loadButtons();
}
Component::~Component()
{
	saveButtons();
}

std::string Component::getName() const
{
	return m_name;
}
sf::Vector2u Component::getSize() const
{
	return m_size;
}

void Component::update(const sf::RenderWindow& window, const sf::Event& event)
{
	for (unsigned int i = 0; i < m_buttons.size(); i++)
	{
		if (m_editMode)
		{
			m_buttons[i].update(window, event);
			m_buttons[i].setColor(sf::Color::White);
		}
		else
		{
			if (m_buttons[i].isPressed(window, event))
			{
				m_buttons[i].setColor(sf::Color(180, 25, 15, 128));
				std::cout << "Button " << m_buttons[i].getValue() << " pressed" << std::endl;
			}
			else
			{
				m_buttons[i].setColor(sf::Color::Transparent);
			}
		}
	}

	bool anySelected = false;

	for (unsigned int i = 0; i < m_buttons.size(); i++)
	{
		if (m_buttons[i].isPressed(window, event))
		{
			anySelected = true;
			break;
		}
	}

	bool anyModifyingValue = false;

	for (unsigned int i = 0; i < m_buttons.size(); i++)
	{
		if (m_buttons[i].getModifyingValue())
		{
			anyModifyingValue = true;
			break;
		}
	}
	
	switch (event.type)
	{
	case sf::Event::MouseButtonPressed:
		if (event.mouseButton.button == sf::Mouse::Left && m_editMode)
		{
			for (unsigned int i = 0; i < m_buttons.size(); i++)
			{
				if (m_buttons[i].isPressed(window, event))
				{
					for (unsigned int j = 0; j < m_buttons.size(); j++)
						m_buttons[j].setSelected(false);

					m_buttons[i].setSelected(true);
					break; // Un seul bouton peut être sélectionné à la fois
				}
			}

			if (!anySelected)
			{
				for (unsigned int i = 0; i < m_buttons.size(); i++)
					m_buttons[i].setSelected(false);
			}
		}
		break;
	case sf::Event::KeyPressed:
		if (event.key.code == sf::Keyboard::E)
		{
			if (!anyModifyingValue)
				m_editMode = !m_editMode;

			if (!m_editMode)
			{
				for (unsigned int i = 0; i < m_buttons.size(); i++)
					m_buttons[i].setSelected(false);
			}
		}

		if (m_editMode && !anyModifyingValue)
		{
			switch (event.key.code)
			{
			case sf::Keyboard::A:
				for (unsigned int i = 0; i < m_buttons.size(); i++)
					m_buttons[i].setSelected(false);

				m_buttons.push_back(Button(m_font));
				m_buttons.back().setSelected(true);
				break;
			case sf::Keyboard::R:
				for (unsigned int i = 0; i < m_buttons.size(); i++)
				{
					if (m_buttons[i].getSelected())
					{
						m_buttons.erase(m_buttons.begin() + i);
						break;
					}
				}
				break;
			default:
				break;
			}
		}

		break;
	}
}

void Component::render(sf::RenderWindow& window) const
{
	window.draw(m_sprite);

	for (unsigned int i = 0; i < m_buttons.size(); i++)
		m_buttons[i].render(window, m_editMode);
}
