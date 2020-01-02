#pragma once
#include "Polygon.h"

class Plane : public Polygon
{
public:
	Plane();
	Plane(vec3 _normal, float _normal_distance, Material * _m) :normal(_normal), normal_distance(_normal_distance) { m = _m; }
	//平面法向量
	vec3 normal;
	//法向量上长度
	float normal_distance;
	//计算光线碰撞
	virtual Ray intersect(Ray ray);
	vec3 getNormal(vec3 _vector) { return normal; };
	~Plane();
};

