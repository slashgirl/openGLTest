#ifndef _TEST_H
#define _TEST_H
#include "glm/glm.hpp"

//定义一个4x3矩阵
class Matrix4_3;

class AABB3
{
public:
	//定义最小点和最大点
	glm::vec3 min;
	glm::vec3 max;

	AABB3();

	void empty();
	void add(const glm::vec3 &p);

	~AABB3();
};




#endif

