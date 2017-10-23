#ifndef _SHADER_H
#define _SHADER_H
//着色器(顶点着色器+片元着色器)
#include <string>
#include "GL/glew.h"
#define GLM_ENABLE_EXPERIMENTAL
#include "Transform.h"
#include "Camera.h"

class Shader
{
public:
	Shader(const std::string& fileName);		//参数用于获取着色器的文本路径

	void Bind();		//绑定着色器

	void Update(const Transform &transform,const Camera& camera);			//将相机关联到着色器中

	~Shader();
private:
	static const unsigned int NUM_SHADERS = 2;		//初始化着色器数量

	//把转换传递到
	enum
	{
		TRANSFORM_U,
		NUM_UNIFORM
	};

	GLuint m_program;		//program用来管理着色器
	GLuint m_shaders[NUM_SHADERS];		//定义两个着色器，分别是顶点着色器和片元着色器
	GLuint m_uniforms[NUM_UNIFORM];		//可直接改变uniform的数量
};




#endif 

