#include "Mesh.h"
#include <vector>


Mesh::Mesh(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices)
{
	IndexedModel model;


	for(unsigned int i =0; i <numVertices; i++)
	{
		model.positions.push_back(*vertices[i].GetPos());		//模型的位置信息赋值给positions
		model.texCoords.push_back(*vertices[i].GetTexCoord());	//模型纹理的信息也赋值
		model.normals.push_back(*vertices[i].GetNormal());		//模型法线向量的信息也赋值
	}

	for(unsigned int i =0; i <numIndices; i++)
	{
		model.indices.push_back(indices[i]);		//模型顶点的索引位置信息赋值
	}

	InitMesh(model);
}

Mesh::Mesh(const std::string& filename)
{
	IndexedModel model = OBJModel(filename).ToIndexedModel();

	InitMesh(model);
}

void Mesh::InitMesh(const IndexedModel& model)
{
	m_drawCount = model.indices.size();

	glGenVertexArrays(1, &m_vertexArrayObject);		//分配顶点数组对象
	glBindVertexArray(m_vertexArrayObject);		//创建并绑定一个顶点数组对象

	glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers);	//分配顶点缓存对象

	//以下获取位置的坐标信息
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]);		//创建并绑定一个缓存对象（缓存类型、缓存对象名称）
	glBufferData(GL_ARRAY_BUFFER, model.positions.size()*sizeof(model.positions[0]), &model.positions[0], GL_STATIC_DRAW);		//分配顶点数据所需的存储空间，将数据从应用程序的数组拷贝到openGL服务端的内存中
	//顶点着色器开始
	glEnableVertexAttribArray(0);		//着色器中属性位置索引（0）
	glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0);		//在着色器中声明一个局部变量，并关联一个属性数组

	//以下获取纹理的坐标信息
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[TEXCOORD_VB]);		//创建并绑定一个缓存对象（缓存类型、缓存对象名称）
	glBufferData(GL_ARRAY_BUFFER, model.positions.size()*sizeof(model.texCoords[0]), &model.texCoords[0], GL_STATIC_DRAW);		//分配纹理数据所需的存储空间，将数据从应用程序的数组拷贝到openGL服务端的内存中
	//纹理着色器开始
	glEnableVertexAttribArray(1);		//着色器中属性纹理索引（1）
	glVertexAttribPointer(1, 2, GL_FLOAT, false, 0, 0);		//在着色器中声明一个局部变量，并关联一个属性数组

	//以下获取法线向量的坐标信息
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[NORMAL_VB]);		//创建并绑定一个缓存对象（缓存类型、缓存对象名称）
	glBufferData(GL_ARRAY_BUFFER, model.normals.size()*sizeof(model.normals[0]), &model.normals[0], GL_STATIC_DRAW);		//分配法线向量数据所需的存储空间，将数据从应用程序的数组拷贝到openGL服务端的内存中
	//法线向量着色器开始
	glEnableVertexAttribArray(2);		//着色器中属性位置索引（2）
	glVertexAttribPointer(2, 3, GL_FLOAT, false, 0, 0);		//在着色器中声明一个局部变量，并关联一个属性数组

	//添加索引的数据
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vertexArrayBuffers[INDEX_VB]);		//创建并绑定一个索引缓存对象（缓存类型、缓存对象名称）
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.indices.size()*sizeof(model.indices[0]), &model.indices[0], GL_STATIC_DRAW);		//分配顶点数据所需的存储空间，将数据从应用程序的数组拷贝到openGL服务端的内存中

	glBindVertexArray(0);		//openGL将不再使用程序分配的顶点对象
}

Mesh::~Mesh()
{
	glGenVertexArrays(1, &m_vertexArrayObject);		//释放分配顶点数组对象
}

void Mesh::Draw()
{
	glBindVertexArray(m_vertexArrayObject);		//使用顶点数组对象

	//glDrawArrays(GL_TRIANGLES, 0, m_drawCount);		//利用当前绑定的几何数组创建一系列几何图源
	glDrawElements(GL_TRIANGLES, m_drawCount, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);		//对绑定做一个释放
}