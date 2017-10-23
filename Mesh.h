#ifndef _MESH_H
#define _MESH_H

//创建网格

#include "glm/glm.hpp"
#include "GL/glew.h"
#include <string>
#include "ObjLoader/obj_loader.h"

class Vertex		//顶点信息
{
public:
	Vertex(const glm::vec3& pos, const glm::vec2& texCoord, const glm::vec3& normal = glm::vec3(0,0,0))		//使用三位数组来定义顶点位置信息
	{
		this->pos = pos;
		this->texCoord = texCoord;
		this->normal = normal;
	}

	inline glm::vec3* GetPos(){ return &pos; }
	inline glm::vec2* GetTexCoord(){ return &texCoord; }
	inline glm::vec3* GetNormal(){ return &normal; }

protected:
private:
	glm::vec3 pos;		//成员变量（顶点的位置信息）
	glm::vec2 texCoord;
	glm::vec3 normal;		//法线向量
};

class Mesh
{
public:
	//传参顶点数组和顶点个数（复杂的模型由于顶点数量过大，不能通过顶点来进行传递，通过索引获得每个顶点的组成信息,定义索引的指针和数量）
	Mesh(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices);	

	Mesh(const std::string& filename);	

	void Draw();
	~Mesh();

private:
	void InitMesh(const IndexedModel& model);
	enum		//定义一个枚举
	{
		POSITION_VB,
		TEXCOORD_VB,
		NORMAL_VB,
		INDEX_VB,
		NUM_BUFFERS
	};
	GLuint m_vertexArrayObject;		//顶点数组信息
	GLuint m_vertexArrayBuffers[NUM_BUFFERS];		//定义顶点缓存
	unsigned int m_drawCount;		//要绘制的顶点个数
};








#endif 


