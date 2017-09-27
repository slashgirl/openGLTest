#ifndef _SHADER_H
#define _SHADER_H
//着色器(顶点着色器+片元着色器)
#include <string>
#include "GL/glew.h"

class Shader
{
public:
	Shader(const std::string& fileName);

	void Bind();		//绑定着色器

	~Shader();
private:
	static const unsigned int NUM_SHADERS = 2;		//初始化着色器数量
	GLuint m_program;		//program用来管理着色器
	GLuint m_shaders[NUM_SHADERS];		//定义两个着色器
};




#endif 

