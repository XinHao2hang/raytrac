#pragma once
#include <opencv2/opencv.hpp>
#include "Material.h"
using namespace cv;
class HighMaterial : public Material
{
	Mat texture;
public:
	void setTexture(Mat _mat) { texture = _mat; }
	HighMaterial();
	vec3 getColor(vec2 uv);
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

