#ifndef _CAMERA_H
#define _CAMERA_H
#define GLM_ENABLE_EXPERIMENTAL
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
		float fLength = glm::length(bbModel.maxPos - bbModel.minPos);
		m_vPos = centerPos + glm::vec3(-5.0f * fLength, 0.0f, 0.0f);

		this -> m_vForword =glm::vec3(1.0f, 0.0f, 0.0f);		//����x���������
		this -> m_vUp =glm::vec3(0.0f, 0.0f, 1.0f);		//����z������Ϸ�
		this -> m_qProjection =glm::perspective(fov, aspect, zNear, zFar);		//͸��ͶӰ����


	}

	void GetCameraLocation(glm::vec3 &pos, glm::vec3 &forword, glm::vec3 &up) //ͨ�����������ض��ֵ
	{
		pos = m_vPos; forword = m_vForword; up = m_vUp;
	}

	void SetCameraLocation(const glm::vec3 &pos, const glm::vec3 &forword, const glm::vec3 &up){
		m_vPos = pos; m_vForword = forword; m_vUp = up;
	}

	inline glm::mat4 GetViewProjection() const
	{
		return m_qProjection * glm::lookAt(m_vPos, m_vPos+m_vForword, m_vUp);		//����һ����������ϵ��ת������projection��˷��������������ϵ�ľ���
	}
	~Camera(){}

private:				//Ϊ����ӳ�Ա����
	glm::mat4 m_qProjection;		//����ͶӰ����
	glm::vec3 m_vPos;		//�������λ��
	glm::vec3 m_vForword;		//����ǰ���ӽ�
	glm::vec3 m_vUp;		//����������¿����ӽ�
};












#endif
