#pragma once
#include "Polygon.h"

class Plane : public Polygon
{
public:
	Plane();
	Plane(vec3 _normal, float _normal_distance, Material * _m) :normal(_normal), normal_distance(_normal_distance) { m = _m; }
	//ƽ�淨����
	vec3 normal;
	//�������ϳ���
	float normal_distance;
	//���������ײ
	virtual Ray intersect(Ray ray);
	vec3 getNormal(vec3 _vector) { return normal; };
	~Plane();
};

