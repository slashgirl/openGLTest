#include "Shader.h"
#include <fstream>
#include <iostream>


static GLuint CreateShader(const std::string& text, GLenum shaderType);
static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);	
//检测着色器是否存在错误，并且输出错误信息
static std::string LoadShader(const std::string& fileName);		
//加载着色器文件，并返回着色器的所有内容


Shader::Shader(const std::string& fileName)
{
	m_program = glCreateProgram();		//创建一个program
	//创建两个shader
	m_shaders[0] = CreateShader(LoadShader(fileName + ".vs"), GL_VERTEX_SHADER);	//读取着色器文件并且返回创建后的着色器(顶点着色器)
	m_shaders[1] = CreateShader(LoadShader(fileName + ".fs"), GL_FRAGMENT_SHADER);	//读取着色器文件并且返回创建后的着色器（片元着色器）

	//将创建成功的shader导入到program中
	for(unsigned int i =0; i <NUM_SHADERS; i++)
	{
		glAttachShader(m_program, m_shaders[i]);
	}

	//绑定位置、纹理、法线属性信息
	glBindAttribLocation(m_program, 0, "position");
	glBindAttribLocation(m_program, 1, "texCoord");
	glBindAttribLocation(m_program, 2, "normal");


	//导入shader到program中后，连接到program,并检查错误信息
	glLinkProgram(m_program);
	CheckShaderError(m_program, GL_LINK_STATUS, true, "Error:Program Linking invalid");

	//连接到program后，验证program
	glValidateProgram(m_program);
	CheckShaderError(m_program, GL_VALIDATE_STATUS, true, "Error:Program Validate invalid");

	m_uniforms[TRANSFORM_U] =glGetUniformLocation(m_program, "transform");
}

void Shader::Bind()
{
	glUseProgram(m_program);		//使用program
}

//变换矩阵传递给着色器
void Shader::Update(const Transform &transform, const Camera& camera)
{
	glm::mat4 model =camera.GetViewProjection() * transform.GetModel();		//将相机位置矩阵与转换矩阵相乘，传递到着色器中
	glUniformMatrix4fv(m_uniforms[TRANSFORM_U], 1, GL_FALSE, &model[0][0]);
}

Shader::~Shader()
{
	//将shader从program中卸载(对应构造函数加载)
	for(unsigned int i =0; i <NUM_SHADERS; i++)
	{
		glDetachShader(m_program, m_shaders[i]);
		glDeleteShader(m_shaders[i]);	//卸载完删除掉shader
	}
	glDeleteProgram(m_program);		//删除掉创建的program
}

//返回一个shader,第一个参数加载的着色器的所有字符串，第二个参数加载的着色器的类型
static GLuint CreateShader(const std::string& text, GLenum shaderType)
{
	//首先创建一个shader
	GLuint shader = glCreateShader(shaderType);
	//如果创建失败，则输出提示信息
	if(shader == 0)
	{
		std::cerr << "Error shader creation failure" << std::endl;
	}
	
	const GLchar* shaderSourceString[1];	//创建着色器字符串
	GLint shaderSourceStringLength[1];		//着色器字符串长度
	shaderSourceString[0] = text.c_str();
	shaderSourceStringLength[0] = text.length();

	glShaderSource(shader, 1, shaderSourceString, shaderSourceStringLength);	//向shader中导入写好的数据
	glCompileShader(shader);	//编译shader

	CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error:shader compilation failed");		//检查shader编译的状态

	return shader;		//返回创建成功的shader
}

//检测着色器是否存在错误，并且输出错误信息
static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
{
	GLint success =0;
	GLchar error[1024] ={0};

	if(isProgram)
	{
		glGetProgramiv(shader, flag, &success);
	}else
	{
		glGetShaderiv(shader, flag, &success);
	}

	if(success == GL_FALSE)
	{
		if(isProgram)
		{
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		}else
	    {
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);
		}
	}
}

//加载着色器文件，并返回着色器的所有内容
static std::string LoadShader(const std::string& fileName)
{
	std::ifstream file;
	file.open((fileName).c_str());		//打开文件路径

	std::string output;
	std::string line;

	if(file.is_open())
	{
		while (file.good())
		{
			getline(file, line);
			output.append(line + "\n");
		}
	}else
	{
		std::cerr << "Unable to load shader:" << fileName << std::endl;
	}

	return output;
}