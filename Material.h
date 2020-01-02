#pragma once
#include<glm.hpp>
using namespace glm;
class Material
{
public:
	//折射率，控制折射角度的
	float refract;
	//透光度,对于透明物体，影响折射光线作用效果的
	float transparent;
	//正反射亮度,影响镜面反射的作用效果
	float specular;
	//漫反射亮度,影响漫反射作用效果的
	float diffuse;
	//光源强度
	float light;
	//颜色
	vec3 color;
	Material();
	Material(float _light, float _specular, float _diffuse, float _refract, float _transparent,vec3 _color) :
		light(_light), specular(_specular), transparent(_transparent), diffuse(_diffuse), refract(_refract),color(_color) {}

	virtual vec3 getColor(vec2 uv) { return color; }
	~Material();
};

