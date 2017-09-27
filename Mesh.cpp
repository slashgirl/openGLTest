#include "Mesh.h"

Mesh::Mesh(Vertex* vertices, unsigned int numVertices)
{
	m_drawCount = numVertices;

	glGenVertexArrays(1, &m_vertexArrayObject);		//���䶥���������
	glBindVertexArray(m_vertexArrayObject);		//��������һ�������������

	glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers);	//���䶥�㻺�����
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_V0]);		//��������һ��������󣨻������͡�����������ƣ�
	glBufferData(GL_ARRAY_BUFFER, numVertices*sizeof(vertices[0]), vertices, GL_STATIC_DRAW);		//���䶥����������Ĵ洢�ռ䣬�����ݴ�Ӧ�ó�������鿽����openGL����˵��ڴ���

	//��ɫ����ʼ
	glEnableVertexAttribArray(0);		//��ɫ��������λ��������0��
	glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0);		//����ɫ��������һ���ֲ�������������һ����������

	glBindVertexArray(0);		//openGL������ʹ�ó������Ķ������
}

Mesh::~Mesh()
{
	glGenVertexArrays(1, &m_vertexArrayObject);		//�ͷŷ��䶥���������
}

void Mesh::Draw()
{
	glBindVertexArray(m_vertexArrayObject);		//ʹ�ö����������

	glDrawArrays(GL_TRIANGLES, 0, m_drawCount);		//���õ�ǰ�󶨵ļ������鴴��һϵ�м���ͼԴ

	glBindVertexArray(0);		//�԰���һ���ͷ�
}