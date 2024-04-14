#include "game.h"


Game::Game()
{

}

void Game::Run(sf::RenderWindow &window)
{
	sf::View view;
	view.reset(sf::FloatRect(0, 0, 1920, 1080));
	int w = 1920;
	int h = 1080;
	int mouseX = w / 2 + 64;
	int mouseY = h / 2;
	srand(time(NULL));
	int seed = 1 + std::rand() % 1000;
	Enemy enemy;
	enemy.Initialization(32, 0);
	sf::RectangleShape rectangle(sf::Vector2f(32, 32));
	bool isMouseButtonPresed = false;

	window.setFramerateLimit(144);

	
	sf::Clock clock;
	int AttackFrames = 0;
	int frames = 0;
	while (window.isOpen())
	{
		if(pl.isAlive())
		{
			if(frames > 144)
			{
				pl.removeImmunity();
				frames = 0;
			}
			float time = clock.getElapsedTime().asMicroseconds();
			time /= 1300;
	/*		std::cout << time << "\t" << clock.getElapsedTime().asMicroseconds() << std::endl;
			int tmp1 = 540 / 32;*/
			//std::cout << tmp1 << std::endl;
			
			clock.restart();

			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
				if(event.type == sf::Event::MouseButtonPressed)
					if (event.key.code == sf::Mouse::Left)
						isMouseButtonPresed = true;
					
			}
			
			if (pl.isImmunity())
				frames++;
		
			if(!pl.dashing)
			{
				//pl.satDown = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
				if (!pl.satDown)
				{

					if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
					{
						pl.setDx(0.25);
						pl.setDirection(1);
						if(pl.getCamera().getCenterX() >= (location.getWidth() - 15) * 32)
							pl.getCamera().setCenterX((location.getWidth() - 15) * 32);
					}
					else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
					{
						pl.setDx(0.25);
						pl.setDirection(-1);
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
					{
						if (pl.isOnGround())
							pl.setDy(-0.65);
					}
					if (pl.dashColdown > 77)
					{
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
							pl.dashing = true;
					
					}
				}
			}
			

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				window.close();
		
			for (int i = pl.getCamera().getCenterY() / 32 - 9; i < pl.getCamera().getCenterY() / 32 + 10; i++)
				for (int j = pl.getCamera().getCenterX() / 32 - 15; j < pl.getCamera().getCenterX() / 32 + 17; j++)
					window.draw(location.TileMap[i][j].getSprite());
				
			pl.update(time,location.TileMap);
			if(isMouseButtonPresed)
			{
				window.draw(pl.getWeapon()->getRectangle());
				AttackFrames++;
			}
			
			for (int i = 0; i < Enemys.size(); i++)
			{
				if(Enemys[i].isAlive())
				{
					if(Enemys[i].getRect().left > pl.getCamera().getCenterX() - 512 && Enemys[i].getRect().left < pl.getCamera().getCenterX() + 576)
					{
						Enemys[i].setPlayerPosition(pl.getRect());
						if (!pl.isImmunity())
							if(pl.getRect().intersects(Enemys[i].getRect()))
								pl.TakeDamage(Enemys[i].getDamageValue());
						if (AttackFrames > 5)
							if(pl.getWeapon()->getRect().intersects(Enemys[i].getRect()))
								Enemys[i].TakeDamage(pl.getWeapon()->getDamageValue());
							
						Enemys[i].update(time,location.TileMap);
						window.draw(Enemys[i].getRectangle());
					}
				}
				else
					Enemys.erase(Enemys.begin() + i);
			}
			if (AttackFrames > 5)
			{
				AttackFrames = 0;
				isMouseButtonPresed = false;
			}
			weapon* Sword = pl.getWeapon();
			sf::RectangleShape tmp = Sword->getRectangle();

			//window.draw(pl.getWeapon()->getRectangle());
			
			window.draw(pl.getRectangle());
			window.display();
			window.setView(pl.getCamera().getView());
			window.clear(sf::Color::White);
		}
		else
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				window.close();
			window.display();
			window.setView(pl.getCamera().getView());
			window.clear(sf::Color::White);
		}
	}
}

void Game::Pause()
{
}

void Game::Menu()
{
}

void Game::Initialization()
{
	hlth::Health health;
	health.setHealthPoints(100);
   location.setHeight(70);
   location.setWidth(250);
   location.setPersistence(3);
   location.setCountNoiseFunction(10);
   location.GenerateMap();
	sword Sword;

	pl.setCharacterHeight(50);
	pl.setCharacterWidth(32);
	pl.Initialization(0,location.getStartPlayerPosition() * 32);
	Sword.setRect(sf::FloatRect(pl.getRect().left + pl.getRect().width, pl.getRect().top,35,10));
	Sword.setRectangle(sf::RectangleShape(sf::Vector2f(35,10)));
	sf::RectangleShape tmp = Sword.getRectangle();
	tmp.setFillColor(sf::Color::Blue);
	tmp.setPosition(Sword.getRect().left, Sword.getRect().top);
	Sword.setRectangle(tmp);
	Sword.setDamageValue(34);
	pl.setWeapon(&Sword);
	pl.setHealth(health);

	sf::RenderWindow window(sf::VideoMode(w, h), "Ray tracing", sf::Style::Fullscreen);
	Camera camera;
	sf::View view;
	
	camera.setView(view);

	camera.setWindowHeight(h);
	camera.setWindowWidth(w);
	camera.setViewMode(sf::Vector2u(w/2,h/2));
	camera.setCenterX(w / 4);
	camera.setCenterY(h / 4 + 32);
	Enemys = location.getEnemys();
	if(Enemys.size() > location.currentEnemy)
		Enemys.resize(location.currentEnemy);
	std::cout << location.tryRnd << std::endl;
	std::cout << location.countCaves << std::endl;
	
	pl.setCamera(camera);
	Run(window);

}
