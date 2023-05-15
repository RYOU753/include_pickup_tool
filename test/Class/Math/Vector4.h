#pragma once

namespace Kirara::Math
{
	template<typename T>
	class Vector4Template
	{
	public:
		T x;
		T y;
		T z;
		T w;
	};

	using Vector4Int = Vector4Template<int>;
	using Vector4Flt = Vector4Template<float>;
	using Vector4Dbl = Vector4Template<double>;

	using Vector4 = Vector4Flt;
}
