#include <iostream>
#include <opencv2/opencv.hpp>
#include <glm.hpp>
#include <vector>
#include <ctime>
#include <thread>
#include "Polygon.h"
#include "Ray.h"
#include "Sphere.h"
#include "Camera.h"
#include "Material.h"
#include "Plane.h"
#include "Triangle.h"
#include "HighMaterial.h"
#include "Triangles.h"
#include "EulerAngle.h"
using namespace std;
using namespace cv;
using namespace glm;
Ray rayTrac(Ray ray, vector<Polygon*> s, int times)
{
	Ray r(vec3(0, 0, 0), vec3(0, 0, 0), 0, vec3(0, 0, 0), nullptr);
	if (times <= 0)
		return r;
	float minDistance = FLT_MAX;
	for (auto obj : s)
	{
		//找到最近的物体
		Ray rayTemp = obj->intersect(ray);
		if (rayTemp.polygon && rayTemp.distance < minDistance)
		{
			minDistance = rayTemp.distance;
			r = rayTemp;
		}
	}
	if (r.polygon == nullptr)
		return Ray(vec3(0, 0, 0), vec3(0, 0, 0), 0, vec3(0, 0, 0), nullptr);
	//计算反射光线
	vec3 reflectRayNormal = r.normal;
	if (dot(r.direction , reflectRayNormal) > 0)
		reflectRayNormal = -reflectRayNormal;

		//构造折射光线
	float itea = ((Polygon*)(r.polygon))->m->refract;
	float cosa1 = abs(dot(r.direction, reflectRayNormal));
	float cosa2 = sqrt(1 - (1 / (itea * itea) * (1 - cosa1 * cosa1)));
	Ray refractRay = Ray(normalize((1 / itea) * r.direction + (cosa1 / itea - cosa2) * reflectRayNormal), r.end.position, 0, vec3(0, 0, 0), nullptr);

	//构造反射光线
	Ray reflectRay = Ray(normalize(r.direction - (2 * dot(r.direction, reflectRayNormal)) * reflectRayNormal), r.end.position, 0, vec3(0, 0, 0), nullptr);
	//获得反射光线方向
	refractRay = rayTrac(refractRay, s, times - 1);
	reflectRay = rayTrac(reflectRay, s, times - 1);

	//计算物体返回的颜色
	r = ((Polygon*)(r.polygon))->sample(r, reflectRay, refractRay);
	return r;
}
Ray render(int i, int j, int rows, int cols, vector<Polygon*> s, Camera cam)
{
	float sy = 1.0 - (i * 1.0) / rows;
	float sx = (j * 1.0) / cols;
	Ray r = rayTrac(cam.generateRay(sx, sy), s, 5);
	if (r.polygon == nullptr)
		return Ray(r.direction, r.position, 0, vec3(0, 0, 0), nullptr);
	return Ray(r.direction, r.position, 0, vec3(r.color.x, r.color.y, r.color.z), nullptr);

}

int main()
{
	EulerAngle angle;
	vector<Polygon*> s;
	Camera camera(vec3(0, 10,15), vec3(0, 0, -1), vec3(0, 1, 0), 90);
	Mat img = Mat::zeros(Size(1024, 1024), CV_8UC3);
	Material m0(0.1, 0.0, 0.0, 1.2, 0.8, vec3(255, 255, 0));
	Material m1(0.8, 0.5, 0.5, 0, 0, vec3(0, 0, 255));
	Material m2(0.9, 0.5, 0.5, 0, 0, vec3(255, 255, 255));
	Material m3(0.1, 0.0, 0.0, 1.1, 0.8, vec3(255, 255, 255));
	HighMaterial hM0(0.8, 0.5, 0.0, 0, 0, vec3(0, 0, 0));


	hM0.setTexture(imread("tp07f_DIFF.jpg"));
	hM0.setNormalTexture(imread("tp07b_NORM.jpg"));
	hM0.setSpecularTexture(imread("tp07d_DIFF.jpg"));
	hM0.hasNormalTexture = true;

	HighMaterial hM1(0.8, 0.5, 0.0, 0, 0, vec3(0, 0, 0));
	hM1.setTexture(imread("1.png"));
	hM1.setNormalTexture(imread("1a.jpg"));
	hM1.setSpecularTexture(imread("11b.jpg"));
	hM1.hasNormalTexture = true;


	Sphere s0(vec3(12, 15, -30), 10, &m0);
	Sphere s1(vec3(-12, 15, -30), 10, &m1);
	Plane p0(vec3(0, 1, 0), 4, &m2);
	s.push_back(&s0);
	s.push_back(&s1);
	//s.push_back(&p0);

	//Triangle triangle0(vec5(vec3(15, 15, -15),vec2(1,1)), vec5(vec3(-15, -15, -15),vec2(0,0)), vec5(vec3(15, -15, -15),vec2(1,0)), &hM0);
	//Triangle triangle1(vec5(vec3(15, 15, -15), vec2(1, 1)), vec5(vec3(-15, 15, -15), vec2(0, 1)), vec5(vec3(-15, -15, -15), vec2(0, 0)), &hM0);
	////triangle0.setPosition(vec3(0, 10, -10));
	////triangle0.setTransform(mat3(vec3(1, 0, 0), vec3(0, 1, 0), vec3(0, 0, 1)));
	////triangle0.move();
	//Triangles wall({ triangle0,triangle1 });
	//wall.setPosition(vec3(0, 20, -20));
	//wall.setTransform(mat3(vec3(1, 0, 0), vec3(0, 1, 0), vec3(0, 0, 1)));
	//wall.move();
	//s.push_back(&wall);

	Triangle triangle0(vec5(vec3(15, 15, -0), vec2(1, 1)), vec5(vec3(15, -15, -0), vec2(1, 0)), vec5(vec3(-15, -15, -0), vec2(0, 0)), &hM0);
	Triangle triangle1(vec5(vec3(15, 15, -0), vec2(1, 1)), vec5(vec3(-15, -15, -0), vec2(0, 0)), vec5(vec3(-15, 15, -0), vec2(0, 1)), &hM0);
	Triangles wall[10][10];
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			wall[i][j].triangles = { triangle0 ,triangle1 };
			wall[i][j].setPosition(vec3(-50 + i * 30, 0 + j * 30, -50));
			wall[i][j].setTransform(angle(vec3(0, 0, 0)));
			wall[i][j].move();
			s.push_back(&wall[i][j]);
		}
	}

	Triangle triangle2(vec5(vec3(15, 0, 15), vec2(1, 1)), vec5(vec3(-15, 0, -15), vec2(0, 0)), vec5(vec3(15, 0, -15), vec2(1, 0)), &hM0);
	Triangle triangle3(vec5(vec3(-15, 0, 15), vec2(0, 1)), vec5(vec3(-15, 0, -15), vec2(0, 0)), vec5(vec3(15, 0, 15), vec2(1, 1)), &hM0);
	Triangles ground[10][10];
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			ground[i][j].triangles = { triangle2 ,triangle3 };
			ground[i][j].setPosition(vec3(-50 + i * 30, 0, 0 + j * 30 - 40));
			ground[i][j].setTransform(mat3(vec3(1, 0, 0), vec3(0, 1, 0), vec3(0, 0, 1)));
			ground[i][j].move();
			s.push_back(&ground[i][j]);
		}

	}
	Triangle tr0 = Triangle(vec5(vec3(-5, 5, 5), vec2(0, 1)), vec5(vec3(-5, -5, 5), vec2(0, 0)), vec5(vec3(5, -5, 5), vec2(1, 0)), &m3);
	Triangle tr1 = Triangle(vec5(vec3(5, -5, 5), vec2(1, 0)), vec5(vec3(5, 5, 5), vec2(1, 1)), vec5(vec3(-5, 5, 5), vec2(0, 1)), &m3);
	Triangle tr2 = Triangle(vec5(vec3(-5, -5, 5), vec2(1, 0)), vec5(vec3(-5, 5, 5), vec2(1, 1)), vec5(vec3(-5, -5, -5), vec2(0, 0)), &m3);
	Triangle tr3 = Triangle(vec5(vec3(-5, -5, -5), vec2(0, 0)), vec5(vec3(-5, 5, 5), vec2(1, 1)), vec5(vec3(-5, 5, -5), vec2(0, 1)), &m3);
	Triangle tr4 = Triangle(vec5(vec3(5, 5, 5), vec2(0, 1)), vec5(vec3(5, -5, 5), vec2(0, 0)), vec5(vec3(5, -5, -5), vec2(1, 0)), &m3);
	Triangle tr5 = Triangle(vec5(vec3(5, 5, 5), vec2(0, 1)), vec5(vec3(5, -5, -5), vec2(1, 0)), vec5(vec3(5, 5, -5), vec2(1, 1)), &m3);
	Triangle tr6 = Triangle(vec5(vec3(5, 5, -5), vec2(0, 1)), vec5(vec3(5, -5, -5), vec2(0, 0)), vec5(vec3(-5, 5, -5), vec2(1, 1)), &m3);
	Triangle tr7 = Triangle(vec5(vec3(-5, 5, -5), vec2(1, 1)), vec5(vec3(5, -5, -5), vec2(0, 0)), vec5(vec3(-5, -5, -5), vec2(1, 0)), &m3);
	Triangle tr8 = Triangle(vec5(vec3(5, 5, 5), vec2(1, 1)), vec5(vec3(5, 5, -5), vec2(1, 0)), vec5(vec3(-5, 5, 5), vec2(0, 1)), &m3);
	Triangle tr9 = Triangle(vec5(vec3(-5, 5, 5), vec2(0, 1)), vec5(vec3(5, 5, -5), vec2(1, 0)), vec5(vec3(-5, 5, -5), vec2(0, 0)), &m3);
	Triangle tr10 = Triangle(vec5(vec3(5, -5, 5), vec2(0, 0)), vec5(vec3(-5, -5, 5), vec2(1, 0)), vec5(vec3(5, -5, -5), vec2(0, 1)), &m3);
	Triangle tr11 = Triangle(vec5(vec3(-5, -5, 5), vec2(1, 0)), vec5(vec3(-5, -5, -5), vec2(1, 1)), vec5(vec3(5, -5, -5), vec2(0, 1)), &m3);


	Triangles box({ tr0,tr1,tr2,tr3,tr4,tr5,tr6,tr7,tr8,tr9,tr10,tr11 });
	box.setPosition(vec3(-10, 8, -10));
	box.setTransform(angle(vec3(0, 45, 0)));
	box.move();
	s.push_back(&box);

	tr0 = Triangle( vec5(vec3(-5, -5, 5), vec2(0, 0)), vec5(vec3(5, -5, 5), vec2(1, 0)), vec5(vec3(-5, 5, 5), vec2(0, 1)), &hM1);
	tr1 = Triangle(vec5(vec3(5, -5, 5), vec2(1, 0)), vec5(vec3(5, 5, 5), vec2(1, 1)), vec5(vec3(-5, 5, 5), vec2(0, 1)), &hM1);
	tr2 = Triangle(vec5(vec3(-5, -5, 5), vec2(1, 0)), vec5(vec3(-5, 5, 5), vec2(1, 1)), vec5(vec3(-5, -5, -5), vec2(0, 0)), &hM1);
	tr3 = Triangle(vec5(vec3(-5, -5, -5), vec2(0, 0)), vec5(vec3(-5, 5, 5), vec2(1, 1)), vec5(vec3(-5, 5, -5), vec2(0, 1)), &hM1);
	tr4 = Triangle(vec5(vec3(5, 5, 5), vec2(0, 1)), vec5(vec3(5, -5, 5), vec2(0, 0)), vec5(vec3(5, -5, -5), vec2(1, 0)), &hM1);
	tr5 = Triangle(vec5(vec3(5, 5, 5), vec2(0, 1)), vec5(vec3(5, -5, -5), vec2(1, 0)), vec5(vec3(5, 5, -5), vec2(1, 1)), &hM1);
	tr6 = Triangle(vec5(vec3(5, 5, -5), vec2(0, 1)), vec5(vec3(5, -5, -5), vec2(0, 0)), vec5(vec3(-5, 5, -5), vec2(1, 1)), &hM1);
	tr7 = Triangle(vec5(vec3(-5, 5, -5), vec2(1, 1)), vec5(vec3(5, -5, -5), vec2(0, 0)), vec5(vec3(-5, -5, -5), vec2(1, 0)), &hM1);
	tr8 = Triangle(vec5(vec3(5, 5, 5), vec2(1, 1)), vec5(vec3(-5, 5, -5), vec2(0, 0)), vec5(vec3(5, 5, -5), vec2(1, 0)), &hM1);
	tr9 = Triangle(vec5(vec3(-5, 5, 5), vec2(0, 1)), vec5(vec3(-5, 5, -5), vec2(0, 0)), vec5(vec3(5, 5, 5), vec2(1, 1)), &hM1);
	tr10 = Triangle(vec5(vec3(5, -5, 5), vec2(1, 1)), vec5(vec3(5, -5, -5), vec2(0, 1)), vec5(vec3(-5, -5, 5), vec2(1, 0)),  &hM1);
	tr11 = Triangle(vec5(vec3(-5, -5, -5), vec2(0, 0)),  vec5(vec3(-5, -5, 5), vec2(1, 0)), vec5(vec3(5, -5, -5), vec2(0, 1)), &hM1);

	Triangles box1({ tr0,tr1,tr2,tr3,tr4,tr5,tr6,tr7,tr8,tr9,tr10,tr11 });
	box1.setPosition(vec3(-10, 20, -10));
	box1.setTransform(angle(vec3(0,70,0)));
	box1.move();
	s.push_back(&box1);

	float start = clock();

	//for (int i = 0; i < img.rows; i++)
	//{
	//	for (int j = 0; j < img.cols; j++)
	//	{
	//		vec3 color = render(i, j, img.rows, img.cols, s, camera).color;
	//		if (color.z > 255)
	//			color.z = 255;
	//		if (color.y > 255)
	//			color.y = 255;
	//		if (color.x > 255)
	//			color.x = 255;
	//		img.at<Vec3b>(i, j) = Vec3b(color.z, color.y, color.x);
	//	}
	//}


	thread t1([&]() {
		for (int i = 0; i < img.rows / 2; i++)
		{
			for (int j = 0; j < img.cols / 2; j++)
			{
				vec3 color = render(i, j, img.rows, img.cols, s, camera).color;
				if (color.z > 255)
					color.z = 255;
				if (color.y > 255)
					color.y = 255;
				if (color.x > 255)
					color.x = 255;
				img.at<Vec3b>(i, j) = Vec3b(color.z, color.y, color.x);
			}
		}
		});
	thread t2([&]() {
		for (int i = img.rows / 2; i < img.rows; i++)
		{
			for (int j = 0; j < img.cols / 2; j++)
			{
				vec3 color = render(i, j, img.rows, img.cols, s, camera).color;
				if (color.z > 255)
					color.z = 255;
				if (color.y > 255)
					color.y = 255;
				if (color.x > 255)
					color.x = 255;
				img.at<Vec3b>(i, j) = Vec3b(color.z, color.y, color.x);
			}
		}
		});
	thread t3([&]() {
		for (int i = 0; i < img.rows / 2; i++)
		{
			for (int j = img.cols / 2; j < img.cols; j++)
			{
				vec3 color = render(i, j, img.rows, img.cols, s, camera).color;
				if (color.z > 255)
					color.z = 255;
				if (color.y > 255)
					color.y = 255;
				if (color.x > 255)
					color.x = 255;
				img.at<Vec3b>(i, j) = Vec3b(color.z, color.y, color.x);
			}
		}
		});
	thread t4([&]() {
		for (int i = img.rows / 2; i < img.rows; i++)
		{
			for (int j = img.cols / 2; j < img.cols; j++)
			{
				vec3 color = render(i, j, img.rows, img.cols, s, camera).color;
				if (color.z > 255)
					color.z = 255;
				if (color.y > 255)
					color.y = 255;
				if (color.x > 255)
					color.x = 255;
				img.at<Vec3b>(i, j) = Vec3b(color.z, color.y, color.x);
			}
		}
		});
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	float end = clock();
	cout << (end - start)/ CLOCKS_PER_SEC << "s" << endl;
	imshow("img", img);
	imwrite("1.jpg", img);
	waitKey(0);
	return 0;
}