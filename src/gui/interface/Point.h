#pragma once

namespace ui
{

//Lightweight 3D Int32/Float32 Point struct for UI
struct Point
{
#if ENABLE_FLOAT_UI
# define POINT_T float
#else
# define POINT_T int
#endif

	POINT_T X;
	POINT_T Y;
	POINT_T Z;

	Point(POINT_T x, POINT_T y, POINT_T z =  static_cast<POINT_T>(0))
	: X(x)
	, Y(y)
	, Z(z)
	{
	}

	inline Point operator - () const
	{
		return Point(-X, -Y, -Z);
	}

	inline Point operator + (const Point& v) const
	{
		return Point(X + v.X, Y + v.Y, Z + v.Z);
	}

	inline Point operator + (const int v) const
	{
		return Point(X + v, Y + v, Z + v);
	}

	inline Point operator - (const Point& v) const
	{
		return Point(X - v.X, Y - v.Y, Z - v.Z);
	}

	inline Point operator - (const int v) const
	{
		return Point(X - v, Y - v, Z - v);
	}

	inline Point operator * (const Point& v) const
	{
		return Point(X * v.X, Y * v.Y, Z * v.Z);
	}

	inline Point operator * (int v) const
	{
		return Point(X * static_cast<POINT_T>(v), Y * static_cast<POINT_T>(v), Z * static_cast<POINT_T>(v));
	}

	inline Point operator * (float v) const
	{
		return Point(X * static_cast<POINT_T>(v), Y * static_cast<POINT_T>(v), Z * static_cast<POINT_T>(v));
	}

	inline Point operator / (const Point& v) const
	{
		return Point(X / v.X, Y / v.Y, Z / v.Z);
	}

	inline Point operator / (int v) const
	{
		return Point(X / static_cast<POINT_T>(v), Y / static_cast<POINT_T>(v), Z / static_cast<POINT_T>(v));
	}

	inline Point operator / (float v) const
	{
		return Point(X / static_cast<POINT_T>(v), Y / static_cast<POINT_T>(v), Z / static_cast<POINT_T>(v));
	}

	inline void operator += (const Point& v)
	{
		X += v.X;
		Y += v.Y;
		Z += v.Z;
	}

	inline void operator -= (const Point& v)
	{
		X -= v.X;
		Y -= v.Y;
		Z -= v.Z;
	}

	inline void operator *= (const Point& v)
	{
		X *= v.X;
		Y *= v.Y;
		Z *= v.Z;
	}

	inline void operator *= (int v)
	{
		X *= static_cast<POINT_T>(v);
		Y *= static_cast<POINT_T>(v);
		Z *= static_cast<POINT_T>(v);
	}

	inline void operator *= (float v)
	{
		X *= static_cast<POINT_T>(v);
		Y *= static_cast<POINT_T>(v);
		Z *= static_cast<POINT_T>(v);
	}

	inline void operator /= (const Point& v)
	{
		X /= v.X;
		Y /= v.Y;
		Z /= v.Z;
	}

	inline void operator /= (int v)
	{
		X /= static_cast<POINT_T>(v);
		Y /= static_cast<POINT_T>(v);
		Z /= static_cast<POINT_T>(v);
	}

	inline void operator /= (float v)
	{
		X /= static_cast<POINT_T>(v);
		Y /= static_cast<POINT_T>(v);
		Z /= static_cast<POINT_T>(v);
	}

	inline bool operator == (const Point& v) const
	{
		return (X == v.X && Y == v.Y && Z == v.Z);
	}

	inline bool operator != (const Point& v) const
	{
		return (X != v.X || Y != v.Y || Z != v.Z);
	}

	inline Point operator = (const Point& v)
	{
		X = v.X;
		Y = v.Y;
		Z = v.Z;
		return Point(X, Y, Z);
	}

};

}
