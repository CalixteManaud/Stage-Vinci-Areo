#include "Component.h"

void Component::loadButtons()
{
	std::ifstream file("res/components/" + m_name + ".txt");

	if (!file.is_open())
	{
		if(m_debugInfo)
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
		if(m_debugInfo)
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

Component::Component(const std::string& name, const sf::Vector2u size, const std::string& idVendor, const std::string& idProduct, bool debugInfo) :
	m_name(name),
	m_size(size),
	m_texture(),
	m_sprite(),
	m_font(),
	m_buttons(),
	m_additionalInfo(),
	m_idVendor(idVendor),
	m_idProduct(idProduct),
	m_thread(),
	m_data(),
	m_dataRecieved(false),
	m_editMode(false),
	m_reading(false),
	m_debugInfo(debugInfo)
{
	m_texture.loadFromFile("res/textures/" + m_name + ".png");
	m_sprite.setTexture(m_texture);

	m_font.loadFromFile("res/fonts/arial.ttf");
	m_additionalInfo.setFont(m_font);
	m_additionalInfo.setString("__ __ __ __");
	m_additionalInfo.setPosition(std::roundf(320.0f - m_additionalInfo.getGlobalBounds().width * 0.5f), std::roundf(300.0f));

	if(m_name != "default" && m_name != "fcu" && m_name != "pedestal")
		loadButtons();
}
Component::~Component()
{
	m_reading = false;

	if(m_name != "default" && m_name != "fcu" && m_name != "pedestal")
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

void Component::start(USB* usb)
{
	m_reading = true;
	m_dataRecieved = false;
	m_thread = std::thread(&USB::readDevice, usb, usb->getDevice(m_idVendor, m_idProduct), &m_reading, &m_dataRecieved, std::ref(m_data));
	m_thread.detach();
}
void Component::stop(USB* usb)
{
	m_reading = false;
	usb->close();
}

void Component::updateHardware()
{
	if (m_dataRecieved)
	{
		if (m_name == "mcdu")
		{
			unsigned int group = std::bitset<32>((m_data[1] & ~(1 << 6)) >> 1).to_ulong();

			unsigned int byte = ~(m_data[2]) & 255;
			byte = (byte & -byte);
			if (byte != 0)
				byte = log2((byte & -byte)) + 1;

			std::string value;

			switch (group)
			{
			case 0:
				switch (byte)
				{
				case 1: value = "."; break;
				case 2: value = "0"; break;
				case 3: value = "+/-"; break;
				case 4: value = "z"; break;
				case 5: value = "/"; break;
				case 6: value = "sp"; break;
				case 7: value = "ovfy"; break;
				case 8: value = "clr"; break;
				default: value = "unknown"; break;
				}
				break;
			case 1:
				switch (byte)
				{
				case 1: value = "7"; break;
				case 2: value = "8"; break;
				case 3: value = "9"; break;
				case 4: value = "u"; break;
				case 5: value = "v"; break;
				case 6: value = "w"; break;
				case 7: value = "x"; break;
				case 8: value = "y"; break;
				default: value = "unknown"; break;
				}
				break;
			case 2:
				switch (byte)
				{
				case 1: value = "4"; break;
				case 2: value = "5"; break;
				case 3: value = "6"; break;
				case 4: value = "p"; break;
				case 5: value = "q"; break;
				case 6: value = "r"; break;
				case 7: value = "s"; break;
				case 8: value = "t"; break;
				default: value = "unknown"; break;
				}
				break;
			case 3:
				switch (byte)
				{
				case 1: value = "1"; break;
				case 2: value = "2"; break;
				case 3: value = "3"; break;
				case 4: value = "k"; break;
				case 5: value = "l"; break;
				case 6: value = "m"; break;
				case 7: value = "n"; break;
				case 8: value = "o"; break;
				default: value = "unknown"; break;
				}
				break;
			case 4:
				switch (byte)
				{
				case 1: value = "rarrow"; break;
				case 2: value = "darrow"; break;
				case 3: value = "lsk6"; break;
				case 4: value = "f"; break;
				case 5: value = "g"; break;
				case 6: value = "h"; break;
				case 7: value = "i"; break;
				case 8: value = "j"; break;
				default: value = "unknown"; break;
				}
				break;
			case 5:
				switch (byte)
				{
				case 1: value = "larrow"; break;
				case 2: value = "uarrow"; break;
				case 3: value = "lsk5"; break;
				case 4: value = "a"; break;
				case 5: value = "b"; break;
				case 6: value = "c"; break;
				case 7: value = "d"; break;
				case 8: value = "e"; break;
				default: value = "unknown"; break;
				}
				break;
			case 6:
				switch (byte)
				{
				case 1: value = "airport"; break;
				case 2: value = "blank2"; break;
				case 3: value = "lsk4"; break;
				case 4: value = "atccomm"; break;
				case 5: value = "mcdumenu"; break;
				case 6: value = "rsk2"; break;
				case 7: value = "rsk4"; break;
				case 8: value = "rsk6"; break;
				default: value = "unknown"; break;
				}
				break;
			case 7:
				switch (byte)
				{
				case 1: value = "radnav"; break;
				case 2: value = "f-pln"; break;
				case 3: value = "lsk3"; break;
				case 4: value = "data"; break;
				case 5: value = "blank1"; break;
				case 6: value = "rsk1"; break;
				case 7: value = "rsk3"; break;
				case 8: value = "rsk5"; break;
				default: value = "unknown"; break;
				}
				break;
			case 8:
				switch (byte)
				{
				case 1: value = "prog"; break;
				case 2: value = "dir"; break;
				case 3: value = "lsk2"; break;
				case 4: value = "lsk1"; break;
				case 5: value = "fuelpred"; break;
				case 6: value = "secf-pln"; break;
				case 7: value = "perf"; break;
				case 8: value = "init"; break;
				default: value = "unknown"; break;
				}
				break;
			case 9:
				switch(byte)
				{
					case 1: value = "dim"; break;
					case 2: value = "brt"; break;
					default: value = "unknown"; break;
				}
				break;
			default:
				value = "unknown";
				break;
			}

			for (unsigned int i = 0; i < m_buttons.size(); ++i)
			{
				if (m_buttons[i].getValue() == value)
				{
					m_buttons[i].setColor(sf::Color(180, 25, 15, 128));
					if(m_debugInfo)
						std::cout << "Button " << m_buttons[i].getValue() << " pressed" << std::endl;
				}
				else
				{
					m_buttons[i].setColor(sf::Color::Transparent);
				}
			}

			// Il y a une différence d'ordre entre secf-pln et fuelpred selon le mcdu
		}
		else if(m_name == "fcu" || m_name == "pedestal")
		{
			m_additionalInfo.setString(std::to_string(m_data[0]) + ' ' + std::to_string(m_data[1]) + ' ' + std::to_string(m_data[2]) + ' ' + std::to_string(m_data[3]));
			m_additionalInfo.setPosition(std::roundf(320.0f - m_additionalInfo.getGlobalBounds().width * 0.5f), std::roundf(300.0f));
		}

		m_dataRecieved = false;
	}
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
				if(m_debugInfo)
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
					break; // Un seul bouton peut �tre s�lectionn� � la fois
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

	if(m_name == "fcu" || m_name == "pedestal")
		window.draw(m_additionalInfo);

	for (unsigned int i = 0; i < m_buttons.size(); i++)
		m_buttons[i].render(window, m_editMode);
}
