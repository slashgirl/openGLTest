#ifndef _MESH_H
#define _MESH_H

//��������

#include "glm/glm.hpp"
#include "GL/glew.h"
#include <string>
#include "ObjLoader/obj_loader.h"

class Vertex		//������Ϣ
{
public:
	Vertex(const glm::vec3& pos, const glm::vec2& texCoord, const glm::vec3& normal = glm::vec3(0,0,0))		//ʹ����λ���������嶥��λ����Ϣ
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
	glm::vec3 pos;		//��Ա�����������λ����Ϣ��
	glm::vec2 texCoord;
	glm::vec3 normal;		//��������
};

//��Χ��
class AABB3
{
public:
	//������С�������
	glm::vec3 minPos;
	glm::vec3 maxPos;

	AABB3();

	void empty();
	void add(const glm::vec3 &p);

	~AABB3();
};

class Mesh
{
public:
	//���ζ�������Ͷ�����������ӵ�ģ�����ڶ����������󣬲���ͨ�����������д��ݣ�ͨ���������ÿ������������Ϣ,����������ָ���������
	Mesh(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices); //�ڴ��е�����	

	Mesh(const std::string& filename);	//�����ϵ��ļ�

	void Draw();

	AABB3 GetAABB3(); //���ذ�Χ����Ϣ

	~Mesh();

private:
	void InitMesh(const IndexedModel& model);
	enum		//����һ��ö��
	{
		POSITION_VB,
		TEXCOORD_VB,
		NORMAL_VB,
		INDEX_VB,
		NUM_BUFFERS
	};
	GLuint m_vertexArrayObject;		//����������Ϣ
	GLuint m_vertexArrayBuffers[NUM_BUFFERS];		//���嶥�㻺��
	unsigned int m_drawCount;		//Ҫ���ƵĶ������
	AABB3 m_bbBV; //��Χ��
};











#endif 


