#pragma once
#include<glm.hpp>
#include<cfloat>
#include "structs.h"
using namespace glm;
class Ray
{
public:
	//光线出发点
	void* polygon = nullptr;//出发元素指针
	float distance = FLT_MAX;//光线长度
	vec3 normal;//所在点法向量
	//光线起点(这里所说的光线是逆向的)
	vec3 position;
	vec5 end;
	//光线方向
	vec3 direction;
	//光线颜色
	vec3 color;
	//光的强度
	float intensity;
	//获取光线打到的位置
	vec3 getEndPoint(float distance);
	Ray();
	Ray(vec3 _direction, vec3 _position, float _intensity, vec3 _color,void * _polygon) :direction(_direction), position(_position), intensity(_intensity), color(_color),polygon(_polygon) {}
	~Ray();
};

