#pragma once
#include<glm.hpp>
#include"Material.h"
#include "Ray.h"
using namespace glm;

class Polygon
{
public:
	//λ��
	vec3 position;
	//�����������
	mat3 transforms;
	//����
	Material m;
	virtual Ray intersect(Ray ray) { return Ray(vec3(0, 0, 0), vec3(0, 0, 0), 0, vec3(0, 0, 0), nullptr); }
	Polygon();
	~Polygon();
};

