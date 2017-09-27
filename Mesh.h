#ifndef _MESH_H
#define _MESH_H

//��������

#include "glm/glm.hpp"
#include "GL/glew.h"

class Vertex		//������Ϣ
{
public:
	Vertex(const glm::vec3& pos)		//ʹ����λ���������嶥��λ����Ϣ
	{
		this->pos = pos;
	}

protected:
private:
	glm::vec3 pos;		//��Ա�����������λ����Ϣ��
};

class Mesh
{
public:
	Mesh(Vertex* vertices, unsigned int numVertices);		//���ζ�������Ͷ������

	void Draw();
	~Mesh();

private:
	enum		//����һ��ö��
	{
		POSITION_V0,
		NUM_BUFFERS
	};
	GLuint m_vertexArrayObject;		//����������Ϣ
	GLuint m_vertexArrayBuffers[NUM_BUFFERS];		//���嶥�㻺��
	unsigned int m_drawCount;		//Ҫ���ƵĶ������
};








#endif 


