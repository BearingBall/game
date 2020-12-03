#include "collider.h"

#include <cmath>

#include "beam.h"

bool collider(Point& A, Point& B, Point& C, Point& D, Point& F, double& cosAngle)
{
	Point AB;
	AB = { A.x - B.x, A.y - B.y };
	Point AC;
	AC = { A.x - C.x , A.y - C.y };
	Point AD;
	AD = { A.x - D.x, A.y - D.y };

	{
		Point CD;
		CD = { C.x - D.x, C.y - D.y };
		cosAngle = abs((AB.x*CD.x + CD.y*AB.y)/(vectorLength(CD)*vectorLength(AB)));
	}
	
	double Z1 = AB.x*AC.y - AC.x*AB.y;
	double Z2 = AB.x*AD.y - AD.x*AB.y;

	if (Z1*Z2>0)
	{
		return false;
	}
	else
	{
		F.x = C.x + (D.x - C.x)*abs(Z1) / abs(Z2 - Z1);
		F.y = C.y + (D.y - C.y)*abs(Z1) / abs(Z2 - Z1);
		if (((A.x-F.x)*(B.x-F.x)+(A.y - F.y)*(B.y - F.y))/(vectorLength(A,F)*vectorLength(B,F))>0)
		{
			return false;
		}
		return true;
	}
}
