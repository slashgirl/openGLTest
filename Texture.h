#ifndef _TEXTURE_H
#define _TEXTURE_H

#include <string>
#include "GL/glew.h"

class Texture
{
public:
	Texture(const std::string& fileName);	//�������Ĺ��캯��
	void Bind();	//���ð󶨺���ʱ���Զ������������
	~Texture();

private:
	GLuint m_texture;	//����һ���������
};





#endif

