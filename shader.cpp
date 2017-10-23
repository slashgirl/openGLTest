#include "Shader.h"
#include <fstream>
#include <iostream>


static GLuint CreateShader(const std::string& text, GLenum shaderType);
static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);	
//�����ɫ���Ƿ���ڴ��󣬲������������Ϣ
static std::string LoadShader(const std::string& fileName);		
//������ɫ���ļ�����������ɫ������������


Shader::Shader(const std::string& fileName)
{
	m_program = glCreateProgram();		//����һ��program
	//��������shader
	m_shaders[0] = CreateShader(LoadShader(fileName + ".vs"), GL_VERTEX_SHADER);	//��ȡ��ɫ���ļ����ҷ��ش��������ɫ��(������ɫ��)
	m_shaders[1] = CreateShader(LoadShader(fileName + ".fs"), GL_FRAGMENT_SHADER);	//��ȡ��ɫ���ļ����ҷ��ش��������ɫ����ƬԪ��ɫ����

	//�������ɹ���shader���뵽program��
	for(unsigned int i =0; i <NUM_SHADERS; i++)
	{
		glAttachShader(m_program, m_shaders[i]);
	}

	//��λ�á���������������Ϣ
	glBindAttribLocation(m_program, 0, "position");
	glBindAttribLocation(m_program, 1, "texCoord");
	glBindAttribLocation(m_program, 2, "normal");


	//����shader��program�к����ӵ�program,����������Ϣ
	glLinkProgram(m_program);
	CheckShaderError(m_program, GL_LINK_STATUS, true, "Error:Program Linking invalid");

	//���ӵ�program����֤program
	glValidateProgram(m_program);
	CheckShaderError(m_program, GL_VALIDATE_STATUS, true, "Error:Program Validate invalid");

	m_uniforms[TRANSFORM_U] =glGetUniformLocation(m_program, "transform");
}

void Shader::Bind()
{
	glUseProgram(m_program);		//ʹ��program
}

//�任���󴫵ݸ���ɫ��
void Shader::Update(const Transform &transform, const Camera& camera)
{
	glm::mat4 model =camera.GetViewProjection() * transform.GetModel();		//�����λ�þ�����ת��������ˣ����ݵ���ɫ����
	glUniformMatrix4fv(m_uniforms[TRANSFORM_U], 1, GL_FALSE, &model[0][0]);
}

Shader::~Shader()
{
	//��shader��program��ж��(��Ӧ���캯������)
	for(unsigned int i =0; i <NUM_SHADERS; i++)
	{
		glDetachShader(m_program, m_shaders[i]);
		glDeleteShader(m_shaders[i]);	//ж����ɾ����shader
	}
	glDeleteProgram(m_program);		//ɾ����������program
}

//����һ��shader,��һ���������ص���ɫ���������ַ������ڶ����������ص���ɫ��������
static GLuint CreateShader(const std::string& text, GLenum shaderType)
{
	//���ȴ���һ��shader
	GLuint shader = glCreateShader(shaderType);
	//�������ʧ�ܣ��������ʾ��Ϣ
	if(shader == 0)
	{
		std::cerr << "Error shader creation failure" << std::endl;
	}
	
	const GLchar* shaderSourceString[1];	//������ɫ���ַ���
	GLint shaderSourceStringLength[1];		//��ɫ���ַ�������
	shaderSourceString[0] = text.c_str();
	shaderSourceStringLength[0] = text.length();

	glShaderSource(shader, 1, shaderSourceString, shaderSourceStringLength);	//��shader�е���д�õ�����
	glCompileShader(shader);	//����shader

	CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error:shader compilation failed");		//���shader�����״̬

	return shader;		//���ش����ɹ���shader
}

//�����ɫ���Ƿ���ڴ��󣬲������������Ϣ
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

//������ɫ���ļ�����������ɫ������������
static std::string LoadShader(const std::string& fileName)
{
	std::ifstream file;
	file.open((fileName).c_str());		//���ļ�·��

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