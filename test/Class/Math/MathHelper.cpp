#include "MathHelper.h"

namespace Kirara::Math
{
	Quaternion AngleAxis(double rad, Vector3 axis)
	{
		Quaternion ret;

		double norm = static_cast<Vector3Dbl>(axis).SqMagnitude();
		if (norm <= 0.0)
		{
			return ret;
		}

		norm = 1.0 / sqrt(norm);
		axis = axis * static_cast<float>(norm);

		const auto c = cos(0.5 * rad);
		const auto s = sin(0.5 * rad);

		ret.w = c;
		ret.x = s * static_cast<double>(axis.x);
		ret.y = s * static_cast<double>(axis.y);
		ret.z = s * static_cast<double>(axis.z);

		return ret;
	}
}
