#include "graphics/Window.h"

Window::Window(const char* title, int width, int height)
: TITLE(title), WIDTH(width), HEIGHT(height)
{
	init();
}

Window::~Window()
{

}

void Window::init()
{
	//Start SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL Error");
	}

	// Set OpenGL Version Here
	// WARNING: Setting the version above 3 will disable Imgui as it is immediate mode
	//SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	//SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

	// Double Buffering and Z Depth
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

	SDL_DisplayMode current;
	SDL_GetCurrentDisplayMode(0, &current);

	// Start a Window
	m_Window = SDL_CreateWindow(TITLE,
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		WIDTH, HEIGHT,
		SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

	if (!m_Window) {
		printf("Window Error");
	}

	// Start OpenGL Context
	m_Context = SDL_GL_CreateContext(m_Window);
	if (!m_Context) {
		printf("Context Error");
	}

	SDL_GL_SetSwapInterval(1);

	// Start GLEW
	glewExperimental = GL_TRUE;
	if (glewInit() < 0) {
		printf("GLEW Error");
	}

	// Print Info
	printf("GL_VERSION: %s \n", glGetString(GL_VERSION));
	printf("GL_VENDOR: %s \n", glGetString(GL_VENDOR));
	printf("GL_SHADING_LANGUAGE_VERSION: %s \n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	printf("GLEW_VERSION: %s \n", glewGetString(GLEW_VERSION));

	isRunning = true;
}

void Window::cleanUp() 
{
	SDL_GL_DeleteContext(m_Context);
	SDL_DestroyWindow(m_Window);
	SDL_Quit();
}

SDL_Window* Window::getWindow() 
{
	return m_Window;
}

SDL_GLContext Window::getContext() 
{
	return m_Context;
}

void Window::clear() 
{
	// Clear
	glViewport(0, 0, WIDTH, HEIGHT);
	glClearColor(0.2, 0.2, 0.2, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Window::swap()
{
	SDL_GL_SwapWindow(m_Window);
}

bool Window::isCloseRequested()
{
	return !isRunning;
}

void Window::requestClose()
{
	isRunning = false;
}