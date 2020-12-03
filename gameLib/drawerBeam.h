#pragma once
#include "textures.h"


class DrawerBeam final
{
public:
	double length;
	double lengthFromLeftEdge;
	int texture;
	double cosAngle;
	DrawerBeam() = default;
	~DrawerBeam() = default;
	bool operator<(const DrawerBeam x) const
	{
		return length < x.length;
	}
};
