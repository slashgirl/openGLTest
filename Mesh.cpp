#include "Mesh.h"

Mesh::Mesh(Vertex* vertices, unsigned int numVertices)
{
	m_drawCount = numVertices;

	glGenVertexArrays(1, &m_vertexArrayObject);		//分配顶点数组对象
	glBindVertexArray(m_vertexArrayObject);		//创建并绑定一个顶点数组对象

	glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers);	//分配顶点缓存对象
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_V0]);		//创建并绑定一个缓存对象（缓存类型、缓存对象名称）
	glBufferData(GL_ARRAY_BUFFER, numVertices*sizeof(vertices[0]), vertices, GL_STATIC_DRAW);		//分配顶点数据所需的存储空间，将数据从应用程序的数组拷贝到openGL服务端的内存中

	//着色器开始
	glEnableVertexAttribArray(0);		//着色器中属性位置索引（0）
	glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0);		//在着色器中声明一个局部变量，并关联一个属性数组

	glBindVertexArray(0);		//openGL将不再使用程序分配的顶点对象
}

Mesh::~Mesh()
{
	glGenVertexArrays(1, &m_vertexArrayObject);		//释放分配顶点数组对象
}

void Mesh::Draw()
{
	glBindVertexArray(m_vertexArrayObject);		//使用顶点数组对象

	glDrawArrays(GL_TRIANGLES, 0, m_drawCount);		//利用当前绑定的几何数组创建一系列几何图源

	glBindVertexArray(0);		//对绑定做一个释放
}