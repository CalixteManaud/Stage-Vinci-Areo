#include "ComponentTester.h"

void ComponentTester::update()
{
	while (m_window.pollEvent(m_event))
	{
		if (m_event.type == sf::Event::Closed || m_event.type == sf::Event::KeyPressed && m_event.key.code == sf::Keyboard::Escape)
			m_window.close();

		if (m_event.type == sf::Event::KeyPressed)
		{
			unsigned int newActiveComponent = m_activeComponent;

			switch (m_event.key.code)
			{
			case sf::Keyboard::Num0: newActiveComponent = 0; break;
			case sf::Keyboard::Num1: newActiveComponent = 1; break;
			case sf::Keyboard::Num2: newActiveComponent = 2; break;
			case sf::Keyboard::Num3: newActiveComponent = 3; break;
			case sf::Keyboard::Num4: newActiveComponent = 4; break;
			case sf::Keyboard::Num5: newActiveComponent = 5; break;
			case sf::Keyboard::Num6: newActiveComponent = 6; break;
			case sf::Keyboard::Num7: newActiveComponent = 7; break;
			case sf::Keyboard::Num8: newActiveComponent = 8; break;
			case sf::Keyboard::Num9: newActiveComponent = 9; break;
			default: break;
			}

			if (newActiveComponent != m_activeComponent && newActiveComponent < m_components.size())
			{
				m_components[m_activeComponent]->stop(&m_usb);

				m_activeComponent = newActiveComponent;
				m_window.setSize(m_components[m_activeComponent]->getSize());
				m_window.setView(sf::View(sf::FloatRect(sf::Vector2f(0.0f, 0.0f), static_cast<sf::Vector2f>(m_components[m_activeComponent]->getSize()))));

				if(m_activeComponent != 0)
					m_components[m_activeComponent]->start(&m_usb);

				if(m_debugInfo)
					std::cout << m_components[m_activeComponent]->getName() << " component selected" << std::endl;
			}
		}

		m_components[m_activeComponent]->update(m_window, m_event);
	}

	m_components[m_activeComponent]->updateHardware();
}
void ComponentTester::render()
{
	m_window.clear(sf::Color(25, 25, 25));

	m_components[m_activeComponent]->render(m_window);

	m_window.display();
}

ComponentTester::ComponentTester(bool debugInfo) :
	m_window(sf::VideoMode(640, 480), "ComponentTester", sf::Style::Close),
	m_event(),
	m_clock(),
	m_deltaTime(0.0f),
	m_usb(debugInfo),
	m_components(),
	m_activeComponent(0),
	m_debugInfo(debugInfo)
{
	m_window.setFramerateLimit(60);

	m_components.push_back(new Component("default", sf::Vector2u(640, 480), "", "", debugInfo));
	m_components.push_back(new Component("mcdu", sf::Vector2u(395, 640), "4d8", "71", debugInfo));
	m_components.push_back(new Component("fcu", sf::Vector2u(640, 480), "4d8", "50", debugInfo));
}
ComponentTester::~ComponentTester()
{
	for (unsigned int i = 0; i < m_components.size(); i++)
		delete m_components[i];
}

void ComponentTester::run()
{
	while (m_window.isOpen())
	{
		m_deltaTime = m_clock.restart().asSeconds();
		//std::cout << static_cast<int>(1.0f / m_deltaTime) << std::endl;

		update();
		render();
	}
}
