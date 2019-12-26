#pragma once
#include<glm.hpp>
#include"Ray.h"
using namespace glm;
class Camera
{
public:
	Camera();
	Camera(vec3 _position,vec3 _front,vec3 _up,float fov/*field of view 视场*/);
	//前方
	vec3 front;
	//上方
	vec3 up;
	//右方
	vec3 right;
	//相机位置
	vec3 position;
	//对应长宽的缩放比例
	float scale;
	//生成光线
	Ray generateRay(float x,float y);
	~Camera();
};

