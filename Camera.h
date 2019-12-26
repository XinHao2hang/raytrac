#pragma once
#include<glm.hpp>
#include"Ray.h"
using namespace glm;
class Camera
{
public:
	Camera();
	Camera(vec3 _position,vec3 _front,vec3 _up,float fov/*field of view �ӳ�*/);
	//ǰ��
	vec3 front;
	//�Ϸ�
	vec3 up;
	//�ҷ�
	vec3 right;
	//���λ��
	vec3 position;
	//��Ӧ��������ű���
	float scale;
	//���ɹ���
	Ray generateRay(float x,float y);
	~Camera();
};

