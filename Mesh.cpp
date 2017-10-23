#include "Mesh.h"
#include <vector>


Mesh::Mesh(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices)
{
	IndexedModel model;


	for(unsigned int i =0; i <numVertices; i++)
	{
		model.positions.push_back(*vertices[i].GetPos());		//ģ�͵�λ����Ϣ��ֵ��positions
		model.texCoords.push_back(*vertices[i].GetTexCoord());	//ģ���������ϢҲ��ֵ
		model.normals.push_back(*vertices[i].GetNormal());		//ģ�ͷ�����������ϢҲ��ֵ
	}

	for(unsigned int i =0; i <numIndices; i++)
	{
		model.indices.push_back(indices[i]);		//ģ�Ͷ��������λ����Ϣ��ֵ
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

	glGenVertexArrays(1, &m_vertexArrayObject);		//���䶥���������
	glBindVertexArray(m_vertexArrayObject);		//��������һ�������������

	glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers);	//���䶥�㻺�����

	//���»�ȡλ�õ�������Ϣ
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]);		//��������һ��������󣨻������͡�����������ƣ�
	glBufferData(GL_ARRAY_BUFFER, model.positions.size()*sizeof(model.positions[0]), &model.positions[0], GL_STATIC_DRAW);		//���䶥����������Ĵ洢�ռ䣬�����ݴ�Ӧ�ó�������鿽����openGL����˵��ڴ���
	//������ɫ����ʼ
	glEnableVertexAttribArray(0);		//��ɫ��������λ��������0��
	glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0);		//����ɫ��������һ���ֲ�������������һ����������

	//���»�ȡ�����������Ϣ
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[TEXCOORD_VB]);		//��������һ��������󣨻������͡�����������ƣ�
	glBufferData(GL_ARRAY_BUFFER, model.positions.size()*sizeof(model.texCoords[0]), &model.texCoords[0], GL_STATIC_DRAW);		//����������������Ĵ洢�ռ䣬�����ݴ�Ӧ�ó�������鿽����openGL����˵��ڴ���
	//������ɫ����ʼ
	glEnableVertexAttribArray(1);		//��ɫ������������������1��
	glVertexAttribPointer(1, 2, GL_FLOAT, false, 0, 0);		//����ɫ��������һ���ֲ�������������һ����������

	//���»�ȡ����������������Ϣ
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[NORMAL_VB]);		//��������һ��������󣨻������͡�����������ƣ�
	glBufferData(GL_ARRAY_BUFFER, model.normals.size()*sizeof(model.normals[0]), &model.normals[0], GL_STATIC_DRAW);		//���䷨��������������Ĵ洢�ռ䣬�����ݴ�Ӧ�ó�������鿽����openGL����˵��ڴ���
	//����������ɫ����ʼ
	glEnableVertexAttribArray(2);		//��ɫ��������λ��������2��
	glVertexAttribPointer(2, 3, GL_FLOAT, false, 0, 0);		//����ɫ��������һ���ֲ�������������һ����������

	//�������������
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vertexArrayBuffers[INDEX_VB]);		//��������һ������������󣨻������͡�����������ƣ�
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.indices.size()*sizeof(model.indices[0]), &model.indices[0], GL_STATIC_DRAW);		//���䶥����������Ĵ洢�ռ䣬�����ݴ�Ӧ�ó�������鿽����openGL����˵��ڴ���

	glBindVertexArray(0);		//openGL������ʹ�ó������Ķ������
}

Mesh::~Mesh()
{
	glGenVertexArrays(1, &m_vertexArrayObject);		//�ͷŷ��䶥���������
}

void Mesh::Draw()
{
	glBindVertexArray(m_vertexArrayObject);		//ʹ�ö����������

	//glDrawArrays(GL_TRIANGLES, 0, m_drawCount);		//���õ�ǰ�󶨵ļ������鴴��һϵ�м���ͼԴ
	glDrawElements(GL_TRIANGLES, m_drawCount, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);		//�԰���һ���ͷ�
}