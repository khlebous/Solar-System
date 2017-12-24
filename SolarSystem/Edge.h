#pragma once
#include "Point.h"
#include <glm/vec4.hpp> // glm::mat4

struct Edge
{
	uint32_t v0;
	uint32_t v1;

	Edge(uint32_t v0, uint32_t v1)
		: v0(v0 < v1 ? v0 : v1)
		, v1(v0 < v1 ? v1 : v0)
	{
	}

	bool operator <(const Edge &rhs) const
	{
		return v0 < rhs.v0 || (v0 == rhs.v0 && v1 < rhs.v1);
	}
};