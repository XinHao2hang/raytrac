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


HighMaterial::~HighMaterial()
{
}
