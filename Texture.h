#ifndef _TEXTURE_H
#define _TEXTURE_H

#include <string>
#include "GL/glew.h"

class Texture
{
public:
	Texture(const std::string& fileName);	//带参数的构造函数
	void Bind();	//调用绑定函数时，自动调用纹理变量
	~Texture();

private:
	GLuint m_texture;	//创建一个纹理变量
};





#endif

