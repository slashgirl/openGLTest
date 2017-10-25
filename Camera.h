#ifndef _CAMERA_H
#define _CAMERA_H

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
		float fLength = (bbModel.maxPos - bbModel.minPos).length();
		pos = centerPos + glm::vec3(-50.0f * fLength, 0.0f, 0.0f);

		this -> forword =glm::vec3(1.0f, 0.0f, 0.0f);		//定义x轴的正方向
		this -> up =glm::vec3(0.0f, 0.0f, 1.0f);		//定义z轴的正上方
		this -> projection =glm::perspective(fov, aspect, zNear, zFar);		//透视投影矩阵


	}

	 inline glm::mat4 GetViewProjection() const
	 {
		return projection * glm::lookAt(pos, pos+forword, up);		//先做一个世界坐标系的转换，与projection相乘返回照相机的坐标系的矩阵
	 }
	 ~Camera(){}

private:				//为类添加成员变量
	glm::mat4 projection;		//定义投影矩阵
	glm::vec3 pos;		//定义相机位置
	glm::vec3 forword;		//定义前景视角
	glm::vec3 up;		//定义从上往下看的视角
};












#endif
