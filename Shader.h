#ifndef _SHADER_H
#define _SHADER_H
//��ɫ��(������ɫ��+ƬԪ��ɫ��)
#include <string>
#include "GL/glew.h"
#define GLM_ENABLE_EXPERIMENTAL
#include "Transform.h"
#include "Camera.h"

class Shader
{
public:
	Shader(const std::string& fileName);		//�������ڻ�ȡ��ɫ�����ı�·��

	void Bind();		//����ɫ��

	void Update(const Transform &transform,const Camera& camera);			//�������������ɫ����

	~Shader();
private:
	static const unsigned int NUM_SHADERS = 2;		//��ʼ����ɫ������

	//��ת�����ݵ�
	enum
	{
		TRANSFORM_U,
		NUM_UNIFORM
	};

	GLuint m_program;		//program����������ɫ��
	GLuint m_shaders[NUM_SHADERS];		//����������ɫ�����ֱ��Ƕ�����ɫ����ƬԪ��ɫ��
	GLuint m_uniforms[NUM_UNIFORM];		//��ֱ�Ӹı�uniform������
};




#endif 

