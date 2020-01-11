#include "Triangles.h"



Triangles::Triangles()
{
}

Ray Triangles::intersect(Ray ray)
{
	//һ������ֻ����ͬһʱ�������������һ��λ����
	for (int i = 0; i < triangles.size(); i++)
	{
		//���ߴ��������ϣ����ص��ǹ��ߵ��������Ϣ
		Ray r = triangles[i].intersect(ray);
		if (r.polygon != nullptr)
			return r;
	}
	return Ray(ray.direction, ray.position, ray.intensity, ray.color, nullptr);
}

Ray Triangles::sample(Ray out, Ray reflect, Ray refract)
{
	for (int i = 0; i < triangles.size(); i++)
	{
		//�ҵ����Ǵ����ĸ�����
		if (out.polygon == &triangles[i])
			return triangles[i].sample(out,reflect,refract);
	}
	//��������ʱ�������ǲ��ᱻִ�е�
	return Ray(out.direction, out.position, 0, vec3(0,0,0), nullptr);
}

void Triangles::setPosition(vec3 _pos)
{
	for (int i = 0; i < triangles.size(); i++)
		triangles[i].setPosition(_pos);
}

void Triangles::setTransform(mat3 _mat)
{
	for (int i=0;i<triangles.size(); i++)
		triangles[i].setTransform(_mat);
}


void Triangles::move()
{
	for (int i = 0; i < triangles.size(); i++)
	{
		triangles[i].move();
	}
}

Triangles::~Triangles()
{
}
