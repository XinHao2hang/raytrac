#pragma once
#include<glm.hpp>
#include"Material.h"
#include "Ray.h"
using namespace glm;

class Polygon
{
public:
	//位置
	vec3 position;
	//世界坐标矩阵
	mat3 transforms;
	//材质
	Material m;
	virtual Ray intersect(Ray ray) { return Ray(vec3(0, 0, 0), vec3(0, 0, 0), 0, vec3(0, 0, 0), nullptr); }
	virtual Ray sample(Ray out, Ray reflect, Ray refract); 
	virtual vec3 getNormal(vec3 _vector) { return vec3(0, 0, 0); }
	Polygon();
	~Polygon();
};

