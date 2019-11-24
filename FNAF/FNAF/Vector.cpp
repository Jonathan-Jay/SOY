#include "Vector.h"
#include "Matrix.h"

vec2::vec2()
{
}

vec2::vec2(float _x, float _y)
{
	x = _x;
	y = _y;
}

float vec2::GetMagnitude()
{
	return float(sqrt((x * x) + (y * y)));
}

float vec2::GetMagnitudeSquared()
{
	float magnitude = GetMagnitude();
	
	return magnitude * magnitude;
}

vec2 vec2::Normalize()
{
	vec2 normalized = *this / GetMagnitude();
	
	return normalized;
}

vec2 vec2::Project(vec2 b)
{
	vec2 a = *this;
	
	//Equation
	//     A dot B
	//B * ---------
	//     ||B||^2
	
	
	float numerator = a.Dot(b);
	float denominator = b.GetMagnitudeSquared();

	return (b * (numerator / denominator));
}

void vec2::Subtract(vec2 v1)
{
	this->x -= v1.x;
	this->y -= v1.y;
}

void vec2::MultScalar(float s)
{
	this->x *= s;
	this->y *= s;
}

void vec2::DivScalar(float s)
{
	this->x /= s;
	this->y /= s;
}

float vec2::Dot(vec2 v2)
{
	return float(x * v2.x + y * v2.y);
}

float vec2::GetAngle(vec2 b)
{
	vec2 a = *this;

	//Equation
	//          A dot B
	//acos( --------------- )
	//       ||A|| * ||B||

	float numerator = a.Dot(b);
	float denominator = a.GetMagnitude() * b.GetMagnitude();
	
	return acos(numerator / denominator);
}

vec2 vec2::Rotate(float angle)
{
	mat2(RotationMatrix) = mat2( vec2(cos(angle), -sin(angle)), vec2(sin(angle), cos(angle)) );
	
	return RotationMatrix * vec2(this->x, this->y);
}

float vec2::operator[](int i)
{
	return *hold[i];
}

vec2 vec2::operator-()
{
	return vec2(-x, -y);
}

vec2 vec2::operator+(vec2 v1)
{
	return vec2(this->x + v1.x, this->y + v1.y);
}

vec2 vec2::operator-(vec2 v1)
{
	return vec2(this->x - v1.x, this->y - v1.y);
}

vec2 vec2::operator*(float f)
{
	return vec2(this->x * f, this->y * f);
}

vec2 vec2::operator/(float s)
{
	return vec2(this->x / s, this->y / s);
}

vec3::vec3()
{
}

vec3::vec3(float _x, float _y, float _z)
{
	x = _x;
	y = _y;
	z = _z;
}

void vec3::Subtract(vec3 v1)
{
	this->x -= v1.x;
	this->y -= v1.y;
	this->z -= v1.z;
}

void vec3::MultScalar(float s)
{
	this->x *= s;
	this->y *= s;
	this->z *= s;
}

void vec3::DivScalar(float s)
{
	this->x /= s;
	this->y /= s;
	this->z /= s;
}

float vec3::Dot(vec3 v2)
{
	return (x * v2.x + y * v2.y + z * v2.z);
}

float vec3::GetMagnitude()
{
	return float(sqrt((x * x) + (y * y) + (z * z)));
}

float vec3::GetMagnitudeSquared()
{
	float magnitude = GetMagnitude();
	
	return magnitude * magnitude;
}

vec3 vec3::Normalize()
{
	vec3 normalized = *this / GetMagnitude();
	
	return normalized;
}

vec3 vec3::Project(vec3 b)
{
	vec3 a = *this;

	//Equation
	//     A dot B
	//B * ---------
	//     ||B||^2

	float numerator = a.Dot(b);
	float denominator = b.GetMagnitudeSquared();
	
	return (b * (numerator / denominator));
}

float vec3::operator[](int i)
{
	return *hold[i];
}

vec3 vec3::operator-()
{
	return vec3( -x, -y, -z);
}

vec3 vec3::operator+(vec3 v2)
{
	return vec3(this->x + v2.x, this->y + v2.y, this->z + v2.z);
}

vec3 vec3::operator-(vec3 v2)
{
	return vec3(this->x - v2.x, this->y - v2.y, this->z - v2.z);
}

vec3 vec3::operator*(float f)
{
	return vec3(this->x * f, this->y * f, this->z * f);
}

vec3 vec3::operator/(float f)
{
	return vec3(this->x / f, this->y / f, this->z / f);
}

vec4::vec4()
{
}

vec4::vec4(float _x, float _y, float _z, float _w)
{
	x = _x;
	y = _y;
	z = _z;
	w = _w;
}

void vec4::Subtract(vec4 v1)
{
	this->x -= v1.x;
	this->y -= v1.y;
	this->z -= v1.x;
	this->w -= v1.w;
}

void vec4::MultScalar(float s)
{
	this->x *= s;
	this->y *= s;
	this->z *= s;
	this->w *= s;
}

void vec4::DivScalar(float s)
{
	this->x /= s;
	this->y /= s;
	this->z /= s;
	this->w /= s;
}

float vec4::Dot(vec4 v2)
{
	return (x * v2.x + y * v2.y + z * v2.z + w * v2.w);
}

float vec4::GetMagnitude()
{
	return float(sqrt((x * x) + (y * y) + (z * z) + (w * w)));
}

float vec4::GetMagnitudeSquared()
{
	float magnitude = GetMagnitude();

	return magnitude * magnitude;
}

vec4 vec4::Normalize()
{
	vec4 normalized = *this / GetMagnitude();

	return normalized;
}

vec4 vec4::Project(vec4 b)
{
	vec4 a = *this;

	//Equation
	//     A dot B
	//B * ---------
	//     ||B||^2

	float numerator = a.Dot(b);
	float denominator = b.GetMagnitudeSquared();

	return (b * (numerator / denominator));
}

float vec4::operator[](int i)
{
	return *hold[i];
}

vec4 vec4::operator-()
{
	return vec4( -x, -y, -z, -w);
}

vec4 vec4::operator+(vec4 v2)
{
	return vec4(this->x + v2.x, this->y + v2.y, this->z + v2.z, this->w + v2.w);
}

vec4 vec4::operator-(vec4 v2)
{
	return vec4(this->x - v2.x, this->y - v2.y, this->z - v2.z, this->w - v2.w);
}

vec4 vec4::operator*(float s)
{
	return vec4(this->x * s, this->y * s, this->z * s, this->w * s);
}

vec4 vec4::operator/(float s)
{
	return vec4(this->x / s, this->y / s, this->z / s, this->w / s);
}
