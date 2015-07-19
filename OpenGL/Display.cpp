#include "display.h"

Display::Display(const unsigned width, const unsigned height, const std::string& title)
{
	this->width = width;
	this->height = height;
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

static float speed = 1;				// camera movement speed

void Display::handleEvents(Camera* camera, float deltaTime)
{
	//SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_MOUSEMOTION:
			{
				SDL_GetMouseState(&Mouse::x, &Mouse::y);

				Mouse::angleX = &camera->getAngle().x;	// get the address of the x and y components of the camera rotation
				Mouse::angleY = &camera->getAngle().y;

				*Mouse::angleX += Mouse::speed * deltaTime * ((float)width / 2 - (float)Mouse::x);		// update the camera rotation
				*Mouse::angleY += Mouse::speed * deltaTime * ((float)height / 2 - (float)Mouse::y);
				
				camera->getForward() = glm::normalize(glm::vec3(cos(*Mouse::angleY) * sin(*Mouse::angleX),			// update the forward vector of the camera
					sin(*Mouse::angleY),
					cos(*Mouse::angleY) * cos(*Mouse::angleX)));

				camera->getRight() = glm::normalize(glm::vec3(sin(*Mouse::angleX - glm::half_pi<float>()),		// calculate the mouse's new relative right direction vector
					0,
					cos(*Mouse::angleX - glm::half_pi<float>())));
				
				camera->getUp() = glm::cross(camera->getRight(), camera->getForward());
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
					camera->getPos() += camera->getForward() * speed * deltaTime;
				}
				if (event.key.keysym.sym == SDLK_s)
				{
					camera->getPos() -= camera->getForward() * speed * deltaTime;
				}
				if (event.key.keysym.sym == SDLK_a)
				{
					camera->getPos() -= camera->getRight() * speed * deltaTime;
				}
				if (event.key.keysym.sym == SDLK_d)
				{
					camera->getPos() += camera->getRight() * speed * deltaTime;
				}
				if (event.key.keysym.sym == SDLK_SPACE)
				{
					camera->getPos() += camera->getUp() * speed * deltaTime;
				}
				if (event.key.keysym.sym == SDLK_LCTRL)
				{
					camera->getPos() -= camera->getUp() * speed * deltaTime;
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
