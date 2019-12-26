#pragma once
#include<glm.hpp>
#include<cfloat>
using namespace glm;
class Ray
{
public:
	//���߳�����
	void* polygon = nullptr;//����Ԫ��ָ��
	float distance = FLT_MAX;//���߳���
	vec3 normal;//���ڵ㷨����
	//�������
	vec3 position;
	//���߷���
	vec3 direction;
	//������ɫ
	vec3 color;
	//���ǿ��
	float intensity;
	//��ȡ���ߴ򵽵�λ��
	vec3 getEndPoint(float distance);
	Ray();
	Ray(vec3 _direction, vec3 _position, float _intensity, vec3 _color,void * _polygon) :direction(_direction), position(_position), intensity(_intensity), color(_color),polygon(_polygon) {}
	~Ray();
};

