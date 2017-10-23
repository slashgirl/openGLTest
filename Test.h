#ifndef _TEST_H
#define _TEST_H
#include "glm/glm.hpp"

class AABB3
{
public:
	AABB3();

	void empty();
	void add(const vec3 &p);

	~AABB3();
private:
	vec3 min;
	vec3 max;
};




#endif
