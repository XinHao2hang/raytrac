#pragma once
#include<glm.hpp>
using namespace glm;
class Material
{
public:
	//�����ʣ���������Ƕȵ�
	float refract;
	//͸���,����͸�����壬Ӱ�������������Ч����
	float transparent;
	//����������,Ӱ�쾵�淴�������Ч��
	float specular;
	//����������,Ӱ������������Ч����
	float diffuse;
	//��Դǿ��
	float light;
	//��ɫ
	vec3 color;
	Material();
	Material(float _light, float _specular, float _diffuse, float _refract, float _transparent,vec3 _color) :
		light(_light), specular(_specular), transparent(_transparent), diffuse(_diffuse), refract(_refract),color(_color) {}

	virtual vec3 getColor(vec2 uv) { return color; }
	~Material();
};

