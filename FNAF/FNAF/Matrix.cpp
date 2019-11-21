#include "Matrix.h"
#include <iomanip>

mat2::mat2()
{
}

mat2::mat2(vec2 _row1, vec2 _row2)
{
	row1 = _row1;
	row2 = _row2;
}

void mat2::Add(mat2 m)
{
	this->row1 = this->row1 + m.row1;
	this->row2 = this->row2 + m.row2;
}

void mat2::Subtract(mat2 m)
{
	this->row1 = this->row1 - m.row1;
	this->row2 = this->row2 - m.row2;
}

void mat2::Print()
{
	std::cout << std::fixed << std::setprecision(2)
		<< "[ " << this->row1.x << ", " << this->row1.y << " ]\n"
		<< "[ " << this->row2.x << ", " << this->row2.y << " ]\n";
}

mat2 mat2::Transpose()
{
	mat2(temp) = mat2(
		vec2(row1.x, row2.x),
		vec2(row1.y, row2.y)
	);

	return temp;
}

float mat2::Determinant()
{
	//Det(mat2) = AD - BC
	return (row1.x * row2.y) - (row1.y * row2.x);
}

mat2 mat2::Inverse()
{
	//the inverse is equal to
	//		 -1 = [ D -B ]		  1
	//[ A B ]   = [-C  A ] X -----------
	//[ C D ]   =			  Det(mat2)

	float OneOverDet = 1.f / Determinant();

	mat2(temp) = mat2(
		vec2(row2.y, -row1.y),
		vec2(-row2.x, row1.x)
	);
	temp = temp * OneOverDet;

	return temp;
}

mat2 mat2::operator-()
{
	return mat2(-row1, -row2);
}

mat2 mat2::operator+(mat2 m)
{
	return mat2(this->row1 + m.row1, this->row2 + m.row2);
}

mat2 mat2::operator-(mat2 m)
{
	return mat2(this->row1 - m.row1, this->row2 - m.row2);
}

mat2 mat2::operator*(mat2 m)
{
	vec2(mCol1) = vec2(m.row1.x, m.row2.x);
	vec2(mCol2) = vec2(m.row1.y, m.row2.y);
	
	mat2(temp) = mat2(
		vec2(row1.Dot(mCol1), row1.Dot(mCol2)),
		vec2(row2.Dot(mCol1), row2.Dot(mCol2))
	);
	
	return temp;
}

vec2 mat2::operator*(vec2 v)
{
	vec2(temp) = vec2(
		row1.x * v.x + row1.y * v.y, 
		row2.x * v.x + row2.y * v.y
	);
	
	return temp;
}

mat2 mat2::operator*(float f)
{
	return mat2(this->row1 * f, this->row2 * f);
}

vec2 mat2::operator[](int i)
{
	//Indexes the variables at i
	//* 0 = row1
	//* 1 = row2
	return *hold[i];
}

mat3::mat3()
{
}

mat3::mat3(vec3 _row1, vec3 _row2, vec3 _row3)
{
	row1 = _row1;
	row2 = _row2;
	row3 = _row3;
}

mat3::mat3(mat4 m)
{
	this->row1 = vec3(m.row1.x, m.row1.y, m.row1.z);
	this->row2 = vec3(m.row2.x, m.row2.y, m.row2.z);
	this->row3 = vec3(m.row3.x, m.row3.y, m.row3.z);
}

void mat3::Add(mat3 m)
{
	this->row1 = this->row1 + m.row1;
	this->row2 = this->row2 + m.row2;
	this->row3 = this->row3 + m.row3;
}

void mat3::Subtract(mat3 m)
{
	this->row1 = this->row1 - m.row1;
	this->row2 = this->row2 - m.row2;
	this->row3 = this->row3 - m.row3;
}

void mat3::Print()
{
	std::cout << std::fixed << std::setprecision(2)
		<< "[ " << this->row1.x << ", " << this->row1.y << ", " << this->row1.z << " ]\n"
		<< "[ " << this->row2.x << ", " << this->row2.y << ", " << this->row2.z << " ]\n"
		<< "[ " << this->row3.x << ", " << this->row3.y << ", " << this->row3.z << " ]\n";
}

mat3 mat3::Transpose()
{
	mat3(temp) = mat3(
		vec3(row1.x, row2.x, row3.x),
		vec3(row1.y, row2.y, row3.y),
		vec3(row1.z, row2.z, row3.z)
	);
	
	return temp;
}

float mat3::Determinant()
{
	//Det(mat3) = a(ei – fh) + b(fg - di) + c(dh – eg)
	//det( [ E F ])	= ei - fg	det( [ F D ] ) = fg - di
	//   ( [ H I ]) =			   ( [ I G ] ) =

	vec3(temp) = CofactorMatrix().row1;

	return temp.Dot(this->row1);
}

mat3 mat3::Inverse()
{
	//the inverse is equal to
	//		   -1             T
	//[ A B C ]   =  adj(mat3)
	//[ D E F ]   = -----------
	//[ G H I ]   =  det(amt3)
	float Det = Determinant();
	mat3(Cofactor) = CofactorMatrix();

	return Transpose(Cofactor) / Det;
}

mat3 mat3::CofactorMatrix()
{
	vec3(R1) = vec3(
		mat2(
			vec2(row2.y, row2.z),
			vec2(row3.y, row3.z)
		).Determinant(),
		mat2(
			vec2(row2.z, row2.x),
			vec2(row3.z, row3.x)
		).Determinant(),
		mat2(
			vec2(row2.x, row2.y),
			vec2(row3.x, row3.y)
		).Determinant()
	);

	vec3(R2) = vec3(
		mat2(
			vec2(row3.y, row3.z),
			vec2(row1.y, row1.z)
		).Determinant(),
		mat2(
			vec2(row3.z, row3.x),
			vec2(row1.z, row1.x)
		).Determinant(),
		mat2(
			vec2(row3.x, row3.y),
			vec2(row1.x, row1.y)
		).Determinant()
	);

	vec3(R3) = vec3(
		mat2(
			vec2(row1.y, row1.z),
			vec2(row2.y, row2.z)
		).Determinant(),
		mat2(
			vec2(row1.z, row1.x),
			vec2(row2.z, row2.x)
		).Determinant(),
		mat2(
			vec2(row1.x, row1.y),
			vec2(row2.x, row2.y)
		).Determinant()
	);
	
	mat3(temp) = mat3(R1, R2, R3);
	
	return temp;
}

mat3 mat3::Transpose(mat3 R)
{
	mat3 temp;

	temp.row1 = vec3(R.row1.x, R.row2.x, R.row3.x);
	temp.row2 = vec3(R.row1.y, R.row2.y, R.row3.y);
	temp.row3 = vec3(R.row1.z, R.row2.z, R.row3.z);
	
	return temp;
}

mat3 mat3::operator-()
{
	return mat3(-row1, -row2, -row3);
}

mat3 mat3::operator+(mat3 m)
{
	return mat3(this->row1 + m.row1, this->row2 + m.row2, this->row3 + m.row3);
}

mat3 mat3::operator-(mat3 m)
{
	return mat3(this->row1 - m.row1, this->row2 - m.row2, this->row3 - m.row3);
}

vec3 mat3::operator[](int i)
{
	//Indexes the variables at i
	//* 0 = row1
	//* 1 = row2
	//* 2 = row3
	return *hold[i];
}

mat3 mat3::operator*(float f)
{
	return mat3(this->row1 * f, this->row2 * f, this->row3 * f);
}

mat3 mat3::operator/(float f)
{
	return mat3(this->row1 / f, this->row2 / f, this->row3 / f);
}

mat3 mat3::operator*(mat3 m)
{
	vec3(Colm1) = vec3(m.row1.x, m.row1.y, m.row1.z);
	vec3(Colm2) = vec3(m.row2.x, m.row2.y, m.row2.z);
	vec3(Colm3) = vec3(m.row3.x, m.row3.y, m.row3.z);

	vec3(Row1) = vec3(
		this->row1.Dot(Colm1),
		this->row1.Dot(Colm2),
		this->row1.Dot(Colm3)
	);
	vec3(Row2) = vec3(
		this->row2.Dot(Colm1),
		this->row2.Dot(Colm2),
		this->row2.Dot(Colm3)
	);
	vec3(Row3) = vec3(
		this->row3.Dot(Colm1),
		this->row3.Dot(Colm2),
		this->row3.Dot(Colm3)
	);
	
	return mat3(Row1, Row2, Row3);
}

vec3 mat3::operator*(vec3 vec)
{
	vec3(temp) = vec3(
		row1.Dot(vec),
		row2.Dot(vec),
		row3.Dot(vec)
	);

	return temp;
}

mat4::mat4()
{
}

mat4::mat4(vec4 _row1, vec4 _row2, vec4 _row3, vec4 _row4)
{
	row1 = _row1;
	row2 = _row2;
	row3 = _row3;
	row4 = _row4;
}

mat4::mat4(mat3 rot, vec3 trans)
{
	row1 = vec4(rot.row1.x, rot.row1.y, rot.row1.z, trans.x);
	row2 = vec4(rot.row2.x, rot.row2.y, rot.row2.z, trans.y);
	row3 = vec4(rot.row3.x, rot.row3.y, rot.row3.z, trans.z);
	row4 = vec4(0.f, 0.f, 0.f, 1.f);
}

mat4 mat4::FastInverse(mat4 mat)
{
	//in order to do a faster inverse, we assume it's a homogenous transformation matrix which means
	//| R(3x3) | T(1x3) | inverse is equal to |R(3x3)^T|T(1x3)*-R|
	//|--------|--------|					  |--------|---------|
	//| 0(3x1) | 1(1x1) |					  | 0(3x1) |  1(1x1) |

	mat3 rotation = mat3(mat);
	vec3 translation = Translation(mat);
	rotation = mat3::Transpose(rotation);
	translation = -rotation * translation;

	return mat4(rotation, translation);
}

vec3 mat4::Translation(mat4 mat)
{
	return vec3(mat.row1.z, mat.row2.z, mat.row3.z);
}

mat4 mat4::operator-()
{
	return mat4(-row1, -row2, -row3, -row4);
}

mat4 mat4::operator+(mat4 m)
{
	return mat4(this->row1 + m.row1, this->row2 + m.row2, this->row3 + m.row3, this->row4 + m.row4);
}

mat4 mat4::operator-(mat4 m)
{
	return mat4(this->row1 - m.row1, this->row2 - m.row2, this->row3 - m.row3, this->row4 - m.row4);
}

vec4 mat4::operator[](int i)
{
	//Indexes the variables at i
	//* 0 = row1
	//* 1 = row2
	//* 2 = row3
	//* 3 = row4
	return *hold[i];
}

mat4 mat4::operator*(float f)
{
	return mat4(this->row1 * f, this->row2 * f, this->row3 * f, this->row4 * f);
}

mat4 mat4::operator/(float f)
{
	return mat4(this->row1 / f, this->row2 / f, this->row3 / f, this->row4 / f);
}

mat4 mat4::operator*(mat4 m)
{
	vec4(Colm1) = vec4(m.row1.x, m.row2.x, m.row3.x, m.row4.x);
	vec4(Colm2) = vec4(m.row1.y, m.row2.y, m.row3.y, m.row4.y);
	vec4(Colm3) = vec4(m.row1.z, m.row2.z, m.row3.z, m.row4.z);
	vec4(Colm4) = vec4(m.row1.w, m.row2.w, m.row3.w, m.row4.w);


	vec4(Row1) = vec4(
		this->row1.Dot(Colm1),
		this->row1.Dot(Colm2),
		this->row1.Dot(Colm3),
		this->row1.Dot(Colm4)
	);
	vec4(Row2) = vec4(
		this->row2.Dot(Colm1),
		this->row2.Dot(Colm2),
		this->row2.Dot(Colm3),
		this->row2.Dot(Colm4)
	);
	vec4(Row3) = vec4(
		this->row3.Dot(Colm1),
		this->row3.Dot(Colm2),
		this->row3.Dot(Colm3),
		this->row3.Dot(Colm4)
	);
	vec4(Row4) = vec4(
		this->row4.Dot(Colm1),
		this->row4.Dot(Colm2),
		this->row4.Dot(Colm3),
		this->row4.Dot(Colm4)
	);

	return mat4(Row1, Row2, Row3, Row4);
}

vec4 mat4::operator*(vec4 vec)
{
	vec4(temp) = vec4(
		row1.Dot(vec),
		row2.Dot(vec),
		row3.Dot(vec),
		row4.Dot(vec)
	);

	return temp;
}

void mat4::Print()
{
	std::cout << std::fixed << std::setprecision(2)
		<< "[ " << this->row1.x << ", " << this->row1.y << ", " << this->row1.z << ", " << this->row1.w << " ]\n"
		<< "[ " << this->row2.x << ", " << this->row2.y << ", " << this->row2.z << ", " << this->row2.w << " ]\n"
		<< "[ " << this->row3.x << ", " << this->row3.y << ", " << this->row3.z << ", " << this->row3.w << " ]\n"
		<< "[ " << this->row4.x << ", " << this->row4.y << ", " << this->row4.z << ", " << this->row4.w << " ]\n";
}

mat4 mat4::Transpose()
{
	mat4(temp) = mat4(
		vec4(row1.x, row2.x, row3.x, row4.x),
		vec4(row1.y, row2.y, row3.y, row4.y),
		vec4(row1.z, row2.z, row3.z, row4.z),
		vec4(row1.w, row2.w, row3.w, row4.w)
	);

	return temp;
}

float mat4::Determinant()
{	
	vec4(temp) = CofactorMatrix().row1;

	return temp.Dot(this->row1);
}

mat4 mat4::Inverse()
{
	float Det = Determinant();
	mat4(Cofactor) = CofactorMatrix();

	return Transpose(Cofactor) / Det;
}

mat4 mat4::CofactorMatrix()
{
	vec4(R1) = vec4(
		mat3(
			vec3(row2.y, row2.z, row2.w),
			vec3(row3.y, row3.z, row3.w),
			vec3(row4.y, row4.z, row4.w)
		).Determinant(),
		-mat3(
			vec3(row2.x, row2.z, row2.w),
			vec3(row3.x, row3.z, row3.w),
			vec3(row4.x, row4.z, row4.w)
		).Determinant(),
		mat3(
			vec3(row2.x, row2.y, row2.w),
			vec3(row3.x, row3.y, row3.w),
			vec3(row4.x, row4.y, row4.w)
		).Determinant(),
		-mat3(
			vec3(row2.x, row2.y, row2.z),
			vec3(row3.x, row3.y, row3.z),
			vec3(row4.x, row4.y, row4.z)
		).Determinant()
	);

	vec4(R2) = vec4(
		-mat3(
			vec3(row1.y, row1.z, row1.w),
			vec3(row3.y, row3.z, row3.w),
			vec3(row4.y, row4.z, row4.w)
		).Determinant(),
		mat3(
			vec3(row1.x, row1.z, row1.w),
			vec3(row3.x, row3.z, row3.w),
			vec3(row4.x, row4.z, row4.w)
		).Determinant(),
		-mat3(
			vec3(row1.x, row1.y, row1.w),
			vec3(row3.x, row3.y, row3.w),
			vec3(row4.x, row4.y, row4.w)
		).Determinant(),
		mat3(
			vec3(row1.x, row1.y, row1.z),
			vec3(row3.x, row3.y, row3.z),
			vec3(row4.x, row4.y, row4.z)
		).Determinant()
	);

	vec4(R3) = vec4(
		mat3(
			vec3(row1.y, row1.z, row1.w),
			vec3(row2.y, row2.z, row2.w),
			vec3(row4.y, row4.z, row4.w)
		).Determinant(),
		-mat3(
			vec3(row1.x, row1.z, row1.w),
			vec3(row2.x, row2.z, row2.w),
			vec3(row4.x, row4.z, row4.w)
		).Determinant(),
		mat3(
			vec3(row1.x, row1.y, row1.w),
			vec3(row2.x, row2.y, row2.w),
			vec3(row4.x, row4.y, row4.w)
		).Determinant(),
		-mat3(
			vec3(row1.x, row1.y, row1.z),
			vec3(row2.x, row2.y, row2.z),
			vec3(row4.x, row4.y, row4.z)
		).Determinant()
	);

	vec4(R4) = vec4(
		-mat3(
			vec3(row1.y, row1.z, row1.w),
			vec3(row2.y, row2.z, row2.w),
			vec3(row3.y, row3.z, row3.w)
		).Determinant(),
		mat3(
			vec3(row1.x, row1.z, row1.w),
			vec3(row2.x, row2.z, row2.w),
			vec3(row3.x, row3.z, row3.w)
		).Determinant(),
		-mat3(
			vec3(row1.x, row1.y, row1.w),
			vec3(row2.x, row2.y, row2.w),
			vec3(row3.x, row3.y, row3.w)
		).Determinant(),
		mat3(
			vec3(row1.x, row1.y, row1.z),
			vec3(row2.x, row2.y, row2.z),
			vec3(row3.x, row3.y, row3.z)
		).Determinant()
	);

	return mat4(R1, R2, R3, R4);
}

mat4 mat4::Transpose(mat4 R)
{

	mat4(temp) = mat4(
		vec4(R.row1.x, R.row2.x, R.row3.x, R.row4.x),
		vec4(R.row1.y, R.row2.y, R.row3.y, R.row4.y),
		vec4(R.row1.z, R.row2.z, R.row3.z, R.row4.z),
		vec4(R.row1.w, R.row2.w, R.row3.w, R.row4.w)
	);

	return temp;
}
