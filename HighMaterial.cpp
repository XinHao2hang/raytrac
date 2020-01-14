#include "HighMaterial.h"



HighMaterial::HighMaterial()
{
}

vec3 HighMaterial::getColor(vec2 uv)
{
	if (texture.cols <= 0)
		return color;
	int j = abs((int(uv.x * texture.cols)) % texture.cols);
	int i = abs((int(uv.y * texture.rows)) % texture.rows);
	vec3 tcolor;
	tcolor.z = texture.at<Vec3b>(i, j)[0];
	tcolor.y = texture.at<Vec3b>(i, j)[1];
	tcolor.x = texture.at<Vec3b>(i, j)[2];
	return tcolor;
}

vec3 HighMaterial::getNormal(vec2 uv)
{
	if (normals.cols <= 0)
		return vec3(0,0,0);
	int j = abs((int(uv.x * normals.cols)) % normals.cols);
	int i = abs((int(uv.y * normals.rows)) % normals.rows);
	vec3 tnormal;
	tnormal.z = normals.at<Vec3b>(i, j)[0]-128;
	tnormal.y = -(normals.at<Vec3b>(i, j)[1]-128);
	tnormal.x = -(normals.at<Vec3b>(i, j)[2]-128);
	return normalize(tnormal);
}




HighMaterial::~HighMaterial()
{
}
