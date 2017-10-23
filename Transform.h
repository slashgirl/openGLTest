#ifndef _TRANSFORM_H
#define _TRANSFORM_H
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>

class Transform
{
public:
	Transform(const glm::vec3 &pos =glm::vec3(),
			  const glm::vec3 &rot =glm::vec3(),
			  const glm::vec3 &scale =glm::vec3(1.0f, 1.0f, 1.0f)
			 )				//带参数的构造函数，初始化
	{
		//三个参数赋值给成员变量
		this -> pos =pos;
		this -> rot =rot;
		this -> scale =scale;
	}			
	~Transform(){}

	//为三个参数设置get和set方法.get返回指针，set为成员变量赋值
	inline glm::vec3* GetPos() { return &pos; }
	inline glm::vec3* GetRot() { return &rot; }
	inline glm::vec3* GetScale() { return &scale; }

	inline void SetPos(glm::vec3& pos) { this -> pos =pos; }
	inline void SetRot(glm::vec3& rot) { this -> rot =rot; }
	inline void SetScale(glm::vec3& scale) { this -> scale =scale; }

	inline glm::mat4 GetModel()const		//设置一个矩阵，返回经过变换后的参数
	{
		glm::mat4 posMat =glm::translate(pos);		//先得到平移的矩阵
		glm::mat4 scaleMat =glm::scale(scale);		//先得到缩放的矩阵
		glm::mat4 rotX =glm::rotate(rot.x, glm::vec3(1.0, 0.0, 0.0));		//先得到X方向的旋转指针
		glm::mat4 rotY =glm::rotate(rot.y, glm::vec3(0.0, 1.0, 0.0));		//先得到Y方向的旋转指针
		glm::mat4 rotZ =glm::rotate(rot.z, glm::vec3(0.0, 0.0, 1.0));		//先得到Z方向的旋转指针
		glm::mat4 rotMat = rotX * rotY * rotZ;

		return posMat * rotMat * scaleMat;
	}

private:					//所有的动画都可以由三个参数（平移、旋转、缩放）
	glm::vec3 pos;
	glm::vec3 rot;
	glm::vec3 scale;
};













#endif
