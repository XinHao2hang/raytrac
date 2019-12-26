#include "Polygon.h"



Ray Polygon::sample(Ray out, Ray reflact, Ray refract)
{
	Ray res(out.direction, out.position, 0, vec3(0, 0, 0), out.polygon);
	//ԭʼ����
	float cosa = dot(out.normal ,normalize(out.direction));//��������Ǻ��淨������cosֵ
	res.color = m.color * m.light * abs(cosa) ;

	return res;
}

Polygon::Polygon()
{
}


Polygon::~Polygon()
{
}
