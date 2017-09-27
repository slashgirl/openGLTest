#ifndef _MESH_H
#define _MESH_H

//创建网格

#include "glm/glm.hpp"
#include "GL/glew.h"

class Vertex		//顶点信息
{
public:
	Vertex(const glm::vec3& pos)		//使用三位数组来定义顶点位置信息
	{
		this->pos = pos;
	}

protected:
private:
	glm::vec3 pos;		//成员变量（顶点的位置信息）
};

class Mesh
{
public:
	Mesh(Vertex* vertices, unsigned int numVertices);		//传参顶点数组和顶点个数

	void Draw();
	~Mesh();

private:
	enum		//定义一个枚举
	{
		POSITION_V0,
		NUM_BUFFERS
	};
	GLuint m_vertexArrayObject;		//顶点数组信息
	GLuint m_vertexArrayBuffers[NUM_BUFFERS];		//定义顶点缓存
	unsigned int m_drawCount;		//要绘制的顶点个数
};








#endif 


