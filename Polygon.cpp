#include "Polygon.h"



Ray Polygon::sample(Ray out, Ray reflect, Ray refract)
{
	Ray res(out.direction, out.position, 0, vec3(0, 0, 0), out.polygon);
	float cosa = dot(out.normal ,normalize(-out.direction));//��������Ǻ��淨������cosֵ
	//�������
	res.color += m.color * m.light * std::fmaxf(cosa,0);
	//������ɫ����
	res.color += reflect.color * m.specular;

	return res;
}

Polygon::Polygon()
{
}


Polygon::~Polygon()
{
}
