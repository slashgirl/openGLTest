#ifndef _TEST_H
#define _TEST_H
#include "glm/glm.hpp"

//����һ��4x3����
class Matrix4_3;

class AABB3
{
public:
	//������С�������
	glm::vec3 min;
	glm::vec3 max;

	AABB3();

	void empty();
	void add(const glm::vec3 &p);

	~AABB3();
};




#endif

