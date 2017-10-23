#ifndef _CAMERA_H
#define _CAMERA_H

#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"

class Camera
{
public:
	Camera(const glm::vec3& pos,		
		   float fov,				//视角的区域
		   float aspect,			//观看区域的纵横比
		   float zNear,				//定义近深度裁剪平面
		   float zFar			//定义远深度裁剪平面
		  )
	{								//对参数进行赋值
		this -> pos =pos;
		this -> forword =glm::vec3(0.0f, 0.0f, 1.0f);		//定义z轴的正上方
		this -> up =glm::vec3(0.0f, 1.0f, 0.0f);		//定义y轴的正上方
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
