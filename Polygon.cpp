#include "Polygon.h"

Ray Polygon::sample(Ray out, Ray reflect, Ray refract)
{
	Ray res(out.direction, out.position, 0, vec3(0, 0, 0), out.polygon);
	//out���ߴ����Ƕ�Ӧ����ķ�����ֵ
	float cosa = abs(dot(out.normal,-out.direction));//��������Ǻ��淨������cosֵ
	//�������
	res.color = m->getColor(out.end.textureUV) * m->light * std::fmaxf(cosa,0);
	//������ɫ����
	if(reflect.polygon)
		res.color += reflect.color * m->specular;
	return res;
}

Polygon::Polygon()
{
}


Polygon::~Polygon()
{
}