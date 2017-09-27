#ifndef _SHADER_H
#define _SHADER_H
//��ɫ��(������ɫ��+ƬԪ��ɫ��)
#include <string>
#include "GL/glew.h"

class Shader
{
public:
	Shader(const std::string& fileName);

	void Bind();		//����ɫ��

	~Shader();
private:
	static const unsigned int NUM_SHADERS = 2;		//��ʼ����ɫ������
	GLuint m_program;		//program����������ɫ��
	GLuint m_shaders[NUM_SHADERS];		//����������ɫ��
};




#endif 

