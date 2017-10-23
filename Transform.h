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
			 )				//�������Ĺ��캯������ʼ��
	{
		//����������ֵ����Ա����
		this -> pos =pos;
		this -> rot =rot;
		this -> scale =scale;
	}			
	~Transform(){}

	//Ϊ������������get��set����.get����ָ�룬setΪ��Ա������ֵ
	inline glm::vec3* GetPos() { return &pos; }
	inline glm::vec3* GetRot() { return &rot; }
	inline glm::vec3* GetScale() { return &scale; }

	inline void SetPos(glm::vec3& pos) { this -> pos =pos; }
	inline void SetRot(glm::vec3& rot) { this -> rot =rot; }
	inline void SetScale(glm::vec3& scale) { this -> scale =scale; }

	inline glm::mat4 GetModel()const		//����һ�����󣬷��ؾ����任��Ĳ���
	{
		glm::mat4 posMat =glm::translate(pos);		//�ȵõ�ƽ�Ƶľ���
		glm::mat4 scaleMat =glm::scale(scale);		//�ȵõ����ŵľ���
		glm::mat4 rotX =glm::rotate(rot.x, glm::vec3(1.0, 0.0, 0.0));		//�ȵõ�X�������תָ��
		glm::mat4 rotY =glm::rotate(rot.y, glm::vec3(0.0, 1.0, 0.0));		//�ȵõ�Y�������תָ��
		glm::mat4 rotZ =glm::rotate(rot.z, glm::vec3(0.0, 0.0, 1.0));		//�ȵõ�Z�������תָ��
		glm::mat4 rotMat = rotX * rotY * rotZ;

		return posMat * rotMat * scaleMat;
	}

private:					//���еĶ���������������������ƽ�ơ���ת�����ţ�
	glm::vec3 pos;
	glm::vec3 rot;
	glm::vec3 scale;
};













#endif
