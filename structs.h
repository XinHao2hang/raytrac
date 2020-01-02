#pragma once
#include<glm.hpp>
using namespace glm;

struct vec5
{
	//物体坐标
	vec3 position;
	//纹理UV
	vec2 textureUV;
	vec5() {};
	vec5(vec3 _pos) :position(_pos) { textureUV = vec2(0, 0); }
	vec5(vec3 _pos, vec2 uv) :position(_pos), textureUV(uv) {}
	vec5(float x, float y, float z)
	{
		position.x = x;
		position.y = y;
		position.z = z;
		textureUV.x = 0;
		textureUV.y = 0;
	}
};
