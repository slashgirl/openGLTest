#include "Display.h"
#include <iostream>

Display::Display(int width, int height, const std::string& title)
{
	SDL_Init(SDL_INIT_EVERYTHING);	//初始化所有SDL要初始化的内容

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);	//设置颜色通道集
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);	//色值总共占4x8=32
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);		//深度值(三维模型)
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);	//设置双重缓冲区，便于实现内存交换

	m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
	m_glContext = SDL_GL_CreateContext(m_window);	//通过此项实现GPU到窗口的显示
	//以上SDL配置完成

	GLenum status = glewInit();  //初始化Glew
	if(status != GLEW_OK){
		std::cerr << "Glew Init failure" << std::endl;
	}

	m_isClosed = false;		//初始化为false

	glEnable(GL_DEPTH_TEST);	//激活深度值

}
Display::~Display()
{
	SDL_GL_DeleteContext(m_glContext);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

void Display::Update()
{
	SDL_GL_SwapWindow(m_window);	//添加窗口

	SDL_Event e;

	while(SDL_PollEvent(&e))
	{
		if(e.type == SDL_QUIT){		//关闭SDL窗口的时候
			m_isClosed = true;
		}
	}
}

bool Display::IsClosed()
{
	return m_isClosed;
}

void Display::Clear(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		//窗口赋颜色初值
}