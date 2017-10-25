#ifndef _CAMERA_H
#define _CAMERA_H

#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"
#include "Mesh.h"

class Camera
{
public:
	Camera(const AABB3 &bbModel,	//ģ�͵İ�Χ����Ϣ
		   float fov,				//�ӽǵ�����
		   float aspect,			//�ۿ�������ݺ��
		   float zNear,				//�������Ȳü�ƽ��
		   float zFar			//����Զ��Ȳü�ƽ��
		  )
	{								//�Բ������и�ֵ
		glm::vec3 centerPos = (bbModel.maxPos + bbModel.minPos)/2.0f;
		float fLength = (bbModel.maxPos - bbModel.minPos).length();
		pos = centerPos + glm::vec3(-50.0f * fLength, 0.0f, 0.0f);

		this -> forword =glm::vec3(1.0f, 0.0f, 0.0f);		//����x���������
		this -> up =glm::vec3(0.0f, 0.0f, 1.0f);		//����z������Ϸ�
		this -> projection =glm::perspective(fov, aspect, zNear, zFar);		//͸��ͶӰ����


	}

	 inline glm::mat4 GetViewProjection() const
	 {
		return projection * glm::lookAt(pos, pos+forword, up);		//����һ����������ϵ��ת������projection��˷��������������ϵ�ľ���
	 }
	 ~Camera(){}

private:				//Ϊ����ӳ�Ա����
	glm::mat4 projection;		//����ͶӰ����
	glm::vec3 pos;		//�������λ��
	glm::vec3 forword;		//����ǰ���ӽ�
	glm::vec3 up;		//����������¿����ӽ�
};












#endif
