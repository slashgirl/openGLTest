#include "Test.h"
//测试程序

void AABB3::empty()
{
	const float kBigNumber = 1e37f;
	min.x = min.y = min.z = kBigNumber;
	max.x = max.y = max.z = -kBigNumber;
}

void AABB3::add(const vec3 &p)
{
	if(p.x < min.x) min.x = p.x;
	if(p.x > max.x) max.x = p.x;
	if(p.y < min.y) min.y = p.y;
	if(p.y > max.y) max.y = p.y;
	if(p.z < min.z) min.z = p.z;
	if(p.z > max.z) max.z = p.z;
}

//以下为主函数
const int n;
vec3 list(n);
//创建一个包围盒
AABB3 box;
//先清空包围盒
box.empty();
//将点添加到矩形包围盒中
for(int i = 0; i < n; i++)
{
	box.add(list[i]);
}
