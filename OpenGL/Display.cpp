#include "display.h"

#ifdef USE_SDL
Display::Display(const unsigned width, const unsigned height, const std::string& title)
{
	this->width = width;
	this->height = height;
	std::cout << "Rendering using SDL" << std::endl;
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, GL_TRUE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, GL_TRUE);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);

	window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
	glContext = SDL_GL_CreateContext(window);

	GLenum status = glewInit();
	if (status != GLEW_OK)
	{
		std::cerr << "Glew failed to initialize" << std::endl;
	}
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_PROGRAM_POINT_SIZE);
	SDL_SetRelativeMouseMode(SDL_TRUE);
}

Display::~Display()
{
	SDL_GL_DeleteContext(glContext);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Display::setClearColor(const glm::vec3 newColor)
{
	glClearColor(newColor.r, newColor.g, newColor.b, 1.0);
}

void Display::clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Display::display()
{
	SDL_GL_SwapWindow(window);
}

static float speed = 500;				// camera movement speed
static const double mouseSpeed = .02;	// camera mouse movement speed

void Display::handleEvents(Camera& camera, float deltaTime, Shader& shader, Shader& instancedShader)
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_MOUSEMOTION:
			{
				int mousePosX, mousePosY;
				SDL_GetMouseState(&mousePosX, &mousePosY);

				float* angleX = &camera.getAngle().x;	// get the address of the x and y components of the camera rotation
				float* angleY = &camera.getAngle().y;

				*angleX += mouseSpeed * deltaTime * ((float)width / 2 - (float)mousePosX);		// update the camera rotation
				*angleY += mouseSpeed * deltaTime * ((float)height / 2 - (float)mousePosY);
				
				camera.getForward() = glm::normalize(glm::vec3(cos(*angleY) * sin(*angleX),			// update the forward vector of the camera
					sin(*angleY),
					cos(*angleY) * cos(*angleX)));

				camera.getRight() = glm::normalize(glm::vec3(sin(*angleX - glm::half_pi<float>()),		// calculate the mouse's new relative right direction vector
					0,
					cos(*angleX - glm::half_pi<float>())));

				camera.getUp() = glm::cross(camera.getRight(), camera.getForward());
				//std::cout << glm::to_string(camera.getUp()) << std::endl;
			}
			break;
			case SDL_KEYDOWN:
			{
				if (event.key.keysym.sym == SDLK_ESCAPE)
				{
					windowOpen = false;
				}
				if (event.key.keysym.sym == SDLK_w)
				{
					camera.getPos() += camera.getForward() * speed * deltaTime;
				}
				if (event.key.keysym.sym == SDLK_s)
				{
					camera.getPos() -= camera.getForward() * speed * deltaTime;
				}
				if (event.key.keysym.sym == SDLK_a)
				{
					camera.getPos() -= camera.getRight() * speed * deltaTime;
				}
				if (event.key.keysym.sym == SDLK_d)
				{
					camera.getPos() += camera.getRight() * speed * deltaTime;
				}
				if (event.key.keysym.sym == SDLK_SPACE)
				{
					camera.getPos() += camera.getUp() * speed * deltaTime;
				}
				if (event.key.keysym.sym == SDLK_LCTRL)
				{
					camera.getPos() -= camera.getUp() * speed * deltaTime;
				}
				if (event.key.keysym.sym == SDLK_LSHIFT)
				{
					speed = 2000;
				}
			
				break;
			}
			case SDL_KEYUP:
			{
				if (event.key.keysym.sym == SDLK_LSHIFT)
				{
					speed = 500;
				}
				if (event.key.keysym.sym == SDLK_e)
				{
					//shader.pushLight(glm::vec3(2.f, 1.f, -1.f));
					//instancedShader.pushLight(glm::vec3(2.f, 1.f, -1.f));
				}
				break;
			}
			case SDL_QUIT:
			{
				windowOpen = false;
				break;
			}
		}
	}
}

void Display::handleEvents(Camera& camera, BasicMesh& mesh, float deltaTime)
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_MOUSEMOTION:
		{
			int mousePosX, mousePosY;
			SDL_GetMouseState(&mousePosX, &mousePosY);

			float* angleX = &camera.getAngle().x;	// get the address of the x and y components of the camera rotation
			float* angleY = &camera.getAngle().y;

			*angleX += mouseSpeed * deltaTime * ((float)width / 2 - (float)mousePosX);		// update the camera rotation
			*angleY += mouseSpeed * deltaTime * ((float)height / 2 - (float)mousePosY);

			camera.getForward() = glm::normalize(glm::vec3(cos(*angleY) * sin(*angleX),			// update the forward vector of the camera
				sin(*angleY),
				cos(*angleY) * cos(*angleX)));

			camera.getRight() = glm::normalize(glm::vec3(sin(*angleX - glm::half_pi<float>()),		// calculate the mouse's new relative right direction vector
				0,
				cos(*angleX - glm::half_pi<float>())));

			camera.getUp() = glm::cross(camera.getRight(), camera.getForward());
			//std::cout << glm::to_string(camera.getUp()) << std::endl;
		}
		break;
		case SDL_KEYDOWN:
		{
			if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				windowOpen = false;
			}
			if (event.key.keysym.sym == SDLK_w)
			{
				camera.getPos() += camera.getForward() * speed * deltaTime;
			}
			if (event.key.keysym.sym == SDLK_s)
			{
				camera.getPos() -= camera.getForward() * speed * deltaTime;
			}
			if (event.key.keysym.sym == SDLK_a)
			{
				camera.getPos() -= camera.getRight() * speed * deltaTime;
			}
			if (event.key.keysym.sym == SDLK_d)
			{
				camera.getPos() += camera.getRight() * speed * deltaTime;
			}
			if (event.key.keysym.sym == SDLK_SPACE)
			{
				camera.getPos() += camera.getUp() * speed * deltaTime;
			}
			if (event.key.keysym.sym == SDLK_LCTRL)
			{
				camera.getPos() -= camera.getUp() * speed * deltaTime;
			}
			if (event.key.keysym.sym == SDLK_LSHIFT)
			{
				speed = 2000;
			}

			if (event.key.keysym.sym == SDLK_RIGHT)
			{
				mesh.getPosition().x -= speed * deltaTime;
			}
			if (event.key.keysym.sym == SDLK_LEFT)
			{
				mesh.getPosition().x += speed * deltaTime;
			}

			if (event.key.keysym.sym == SDLK_UP)
			{
				mesh.getPosition().z += speed * deltaTime;
			}
			if (event.key.keysym.sym == SDLK_DOWN)
			{
				mesh.getPosition().z -= speed * deltaTime;
			}

			if (event.key.keysym.sym == SDLK_o)
			{
				mesh.getPosition().y -= speed * deltaTime;
			}
			if (event.key.keysym.sym == SDLK_p)
			{
				mesh.getPosition().y += speed * deltaTime;
			}

			break;
		}
		case SDL_KEYUP:
		{
			if (event.key.keysym.sym == SDLK_LSHIFT)
			{
				speed = 500;
			}
			break;
		}
		case SDL_QUIT:
		{
			windowOpen = false;
			break;
		}
		}
	}
}

#else
Display::Display(const unsigned width, const unsigned height, const std::string& title) :
window(sf::VideoMode(width, height), title.c_str(), sf::Style::Default, sf::ContextSettings(24, 0, 0, 3, 3))
{
	std::cout << "Rendering using SFML" << std::endl;
	this->width = width;
	this->height = height;
	//sf::Mouse::setPosition(sf::Vector2i(width / 2, height / 2), window);

	GLenum status = glewInit();

	if (status != GLEW_OK)
	{
		std::cerr << "Error: glew failed to initialize" << std::endl;
	}

	glEnable(GL_TEXTURE_2D);
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);
	//glFrontFace(GL_CW);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glDepthMask(GL_TRUE);
	glDepthRange(0.0, 1.0);

	window.setFramerateLimit(120);
	window.setMouseCursorVisible(false);
	//window.setVerticalSyncEnabled(true);
	glViewport(0, 0, width, height);
}

Display::~Display()
{
	window.close();
}

void Display::display()
{
	window.display();
}

void Display::setClearColor(glm::vec3 color)
{
	glClearColor(color.r, color.g, color.b, 1.0);
}

void Display::clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Display::clear(float r, float g, float b)
{
	glClearColor(r, g, b, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
}

static const float speed = 10;
static const float mouseSpeed = .01;

void Display::handleEvents(Camera& camera, float deltaTime)
{
	sf::Event event;
	glm::vec3 cameraPos = camera.getPos();
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
			case sf::Event::Closed:
			{
				window.close();
				break;
			}

			case sf::Event::MouseMoved:
			{
				sf::Vector2i mousePos = sf::Mouse::getPosition(window);
				//std::cout << mousePos.x << ", " << mousePos.y << std::endl;
				//sf::Mouse::setPosition(sf::Vector2i(window.getPosition().x + width / 2, window.getPosition().y + height / 2));

				float* angleX = &camera.getAngle().x;	// get the address of the x and y components of the camera rotation
				float* angleY = &camera.getAngle().y;
				//std::cout << *angleX << ", " << *angleY << std::endl;
				//std::cout << float(width / 2 - mousePos.x) << std::endl;
				*angleX += mouseSpeed * deltaTime * float(width / 2 - mousePos.x);		// update the camera rotation
				*angleY += mouseSpeed * deltaTime * float(height / 2 - mousePos.y);
				//std::cout << *angleX << ", " << *angleY << std::endl;
				camera.getForward() = glm::vec3(cos(*angleY) * sin(*angleX),			// update the forward vector of the camera
					sin(*angleY),
					cos(*angleY) * cos(*angleX));

				camera.getRight() = glm::vec3(sin(*angleX - glm::half_pi<float>()),
					0,
					cos(*angleX - glm::half_pi<float>()));

				camera.getUp() = glm::cross(camera.getRight(), camera.getForward());
				break;
			}

			case sf::Event::KeyPressed:
			{
				if (event.key.code == sf::Keyboard::W)
				{
					camera.getPos() += camera.getForward() * speed * deltaTime;
					std::cout << camera.getPos().x << std::endl;
				}
				if (event.key.code == sf::Keyboard::S)
				{
					camera.getPos() -= camera.getForward() * speed * deltaTime;
				}
				if (event.key.code == sf::Keyboard::A)
				{
					camera.getPos() -= camera.getRight() * speed * deltaTime;
				}
				if (event.key.code == sf::Keyboard::D)
				{
					camera.getPos() += camera.getRight() * speed * deltaTime;
				}
				if (event.key.code == sf::Keyboard::Space)
				{
					camera.move(glm::vec3(cameraPos.x, cameraPos.y + speed * deltaTime, cameraPos.z));
				}
				if (event.key.code == sf::Keyboard::LControl)
				{
					camera.move(glm::vec3(cameraPos.x, cameraPos.y - speed * deltaTime, cameraPos.z));
				}
				if (event.key.code == sf::Keyboard::Escape)
				{
					window.close();
				}
				break;
			}

			default:
			{
				//sf::Mouse::setPosition(sf::Vector2i(width / 2, height / 2), window);
				break;
			}
		}
	}
}

#endif // USE_SDL