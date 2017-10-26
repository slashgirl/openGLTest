#ifndef _CAMERA_H
#define _CAMERA_H
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"
#include "Mesh.h"

class Camera
{
public:
	Camera(const AABB3 &bbModel,	//模型的包围盒信息
		   float fov,				//视角的区域
		   float aspect,			//观看区域的纵横比
		   float zNear,				//定义近深度裁剪平面
		   float zFar			//定义远深度裁剪平面
		  )
	{								//对参数进行赋值
		glm::vec3 centerPos = (bbModel.maxPos + bbModel.minPos)/2.0f;
		float fLength = glm::length(bbModel.maxPos - bbModel.minPos);
		m_vPos = centerPos + glm::vec3(-5.0f * fLength, 0.0f, 0.0f);

		this -> m_vForword =glm::vec3(1.0f, 0.0f, 0.0f);		//定义x轴的正方向
		this -> m_vUp =glm::vec3(0.0f, 0.0f, 1.0f);		//定义z轴的正上方
		this -> m_qProjection =glm::perspective(fov, aspect, zNear, zFar);		//透视投影矩阵


	}

	void GetCameraLocation(glm::vec3 &pos, glm::vec3 &forword, glm::vec3 &up) //通过引用来返回多个值
	{
		pos = m_vPos; forword = m_vForword; up = m_vUp;
	}

	void SetCameraLocation(const glm::vec3 &pos, const glm::vec3 &forword, const glm::vec3 &up){
		m_vPos = pos; m_vForword = forword; m_vUp = up;
	}

	inline glm::mat4 GetViewProjection() const
	{
		return m_qProjection * glm::lookAt(m_vPos, m_vPos+m_vForword, m_vUp);		//先做一个世界坐标系的转换，与projection相乘返回照相机的坐标系的矩阵
	}
	~Camera(){}

private:				//为类添加成员变量
	glm::mat4 m_qProjection;		//定义投影矩阵
	glm::vec3 m_vPos;		//定义相机位置
	glm::vec3 m_vForword;		//定义前景视角
	glm::vec3 m_vUp;		//定义从上往下看的视角
};












#endif
