#include "Display.h"
#include <iostream>

Display::Display(int width, int height, const std::string& title)
{
	SDL_Init(SDL_INIT_EVERYTHING);	//��ʼ������SDLҪ��ʼ��������

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);	//������ɫͨ����
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);	//ɫֵ�ܹ�ռ4x8=32
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);		//���ֵ(��άģ��)
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);	//����˫�ػ�����������ʵ���ڴ潻��

	m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
	m_glContext = SDL_GL_CreateContext(m_window);	//ͨ������ʵ��GPU�����ڵ���ʾ
	//����SDL�������

	GLenum status = glewInit();  //��ʼ��Glew
	if(status != GLEW_OK){
		std::cerr << "Glew Init failure" << std::endl;
	}

	m_isClosed = false;		//��ʼ��Ϊfalse

	glEnable(GL_DEPTH_TEST);	//�������ֵ

}
Display::~Display()
{
	SDL_GL_DeleteContext(m_glContext);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

void Display::Update()
{
	SDL_GL_SwapWindow(m_window);	//��Ӵ���

	SDL_Event e;

	while(SDL_PollEvent(&e))
	{
		if(e.type == SDL_QUIT){		//�ر�SDL���ڵ�ʱ��
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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		//���ڸ���ɫ��ֵ
}