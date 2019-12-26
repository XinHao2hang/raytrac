#pragma once
#include "Polygon.h"
class Sphere : public Polygon
{
public:
	vec3 center;
	float radius = 0;
	Sphere(vec3 _center, float _radius) :center(_center), radius(_radius) {}
	Sphere();
	//��ȡ��Ӧ��ķ�����
	vec3 getNormal(vec3 _vector);
	virtual Ray intersect(Ray ray);
	~Sphere();
};

