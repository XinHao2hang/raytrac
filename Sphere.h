#pragma once
#include "Polygon.h"
class Sphere : public Polygon
{
public:
	vec3 center;
	float radius = 0;
	Sphere(vec3 _center, float _radius, Material * _m) :center(_center), radius(_radius) { m = _m; }
	Sphere();
	//获取对应点的法向量
	vec3 getNormal(vec3 _vector);
	virtual Ray intersect(Ray ray);
	
	~Sphere();
};

