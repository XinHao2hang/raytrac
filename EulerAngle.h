#pragma once
#include <cmath>
#include<glm.hpp>
using namespace glm;
class EulerAngle
{
public:
	EulerAngle();
	mat3 operator()(vec3 angle);
	~EulerAngle();
};

