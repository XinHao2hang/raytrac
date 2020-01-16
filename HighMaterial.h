#pragma once
#include <opencv2/opencv.hpp>
#include "Material.h"
using namespace cv;
class HighMaterial : public Material
{
	Mat texture;
	Mat normals;
	Mat speculars;
public:
	void setTexture(Mat _mat) { texture = _mat; }
	void setNormalTexture(Mat _mat) { normals = _mat; }
	void setSpecularTexture(Mat _mat) { speculars = _mat; cvtColor(speculars, speculars, CV_BGR2GRAY); }
	HighMaterial();
	vec3 getColor(vec2 uv);
	vec3 getNormal(vec2 uv);
	float getSpecular(vec2 uv);
	HighMaterial(float _light, float _specular, float _diffuse, float _refract, float _transparent, vec3 _color) 
	{
		light = _light;
		specular = _specular;
		transparent = _transparent;
		diffuse = _diffuse;
		refract = _refract;
		color = _color;
	}
	~HighMaterial();
};

