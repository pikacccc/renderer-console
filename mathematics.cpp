#include "mathematics.h"

mathematics::vec3 mathematics::vec3::operator+(const mathematics::vec3& other) const
{
	return vec3(this->x + other.x, this->y + other.y, this->z + other.z);
}

mathematics::vec3 mathematics::vec3::operator-(const vec3& other) const
{
	return vec3(this->x - other.x, this->y - other.y, this->z - other.z);
}

mathematics::vec3 mathematics::vec3::operator*(const float& other) const
{
	return mathematics::vec3(this->x * other, this->y * other, this->z * other);
}

void mathematics::vec3::normalize()
{
	float mod = sqrt(this->x * this->x + this->y * this->y + this->z * this->z);

	if (mod == 0) return;

	this->x = this->x / mod;
	this->y = this->y / mod;
	this->z = this->z / mod;
}

mathematics::vec2 mathematics::vec2::operator+(const mathematics::vec2& other) const
{
	return mathematics::vec2(this->x + other.x, this->y + other.y);
}

mathematics::vec2 mathematics::vec2::operator-(const vec2& other) const
{
	return mathematics::vec2(this->x - other.x, this->y - other.y);
}

mathematics::vec2 mathematics::vec2::operator*(const float& other) const
{
	return mathematics::vec2(this->x * other, this->y * other);
}

void mathematics::vec2::normalize()
{
	float mod = sqrt(this->x * this->x + this->y * this->y);

	if (mod == 0) return;

	this->x = this->x / mod;
	this->y = this->y / mod;
}

mathematics::vec4 mathematics::vec4::operator+(const vec4& other) const
{
	return mathematics::vec4(this->x + other.x, this->y + other.y, this->z + other.z, this->w + other.w);
}

mathematics::vec4 mathematics::vec4::operator-(const vec4& other) const
{
	return mathematics::vec4(this->x - other.x, this->y - other.y, this->z - other.z, this->w - other.w);
}

mathematics::vec4 mathematics::vec4::operator*(const float& other) const
{
	return mathematics::vec4(this->x * other, this->y * other, this->z * other, this->w * other);
}

void mathematics::vec4::normalize()
{
	float mod = sqrt(this->x * this->x + this->y * this->y + this->z * this->z + this->w * this->w);

	if (mod == 0) return;

	this->x = this->x / mod;
	this->y = this->y / mod;
	this->z = this->z / mod;
	this->w = this->w / mod;
}

mathematics::vec2 mathematics::normalize(const vec2& vec)
{
	float mod = sqrt(vec.x * vec.x + vec.y * vec.y);

	if (mod == 0) return mathematics::ZERO_VEC2;

	return mathematics::vec2{ vec.x / mod , vec.y / mod };
}

mathematics::vec3 mathematics::normalize(const vec3& vec)
{
	float mod = sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);

	if (mod == 0) return mathematics::ZERO_VEC3;

	return mathematics::vec3{ vec.x / mod , vec.y / mod , vec.z / mod };
}

mathematics::vec4 mathematics::normalize(const vec4& vec)
{
	float mod = sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z + vec.w * vec.w);

	if (mod == 0) return mathematics::ZERO_VEC4;

	return mathematics::vec4{ vec.x / mod , vec.y / mod , vec.z / mod , vec.w / mod };
}

mathematics::vec3 mathematics::cross(const vec3& a, const vec3& b)
{
	return mathematics::vec3{
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x
	};
}

float mathematics::dot(const vec3& a, const vec3& b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

float* mathematics::mat2::operator[](int rowIndex)
{
	return mat[rowIndex];
}

const float* mathematics::mat2::operator[](int rowIndex) const
{
	return mat[rowIndex];
}

float* mathematics::mat3::operator[](int rowIndex)
{
	return mat[rowIndex];
}

const float* mathematics::mat3::operator[](int rowIndex) const
{
	return mat[rowIndex];
}

float* mathematics::mat4::operator[](int rowIndex)
{
	return mat[rowIndex];
}

const float* mathematics::mat4::operator[](int rowIndex) const
{
	return mat[rowIndex];
}

mathematics::vec4 mathematics::mat4::operator*(const vec4& other)
{
	return vec4{
		this->mat[0][0] * other.x + this->mat[0][1] * other.y + this->mat[0][2] * other.z + this->mat[0][3] * other.w,
		this->mat[1][0] * other.x + this->mat[1][1] * other.y + this->mat[1][2] * other.z + this->mat[1][3] * other.w,
		this->mat[2][0] * other.x + this->mat[2][1] * other.y + this->mat[2][2] * other.z + this->mat[2][3] * other.w,
		this->mat[3][0] * other.x + this->mat[3][1] * other.y + this->mat[3][2] * other.z + this->mat[3][3] * other.w,
	};
}

mathematics::quaternion mathematics::quaternion::operator*(const quaternion& other) const
{
	return quaternion{
		w * other.w - x * other.x - y * other.y - z * other.z,
		w * other.x + x * other.w + y * other.z - z * other.y,
		w * other.y - x * other.z + y * other.w + z * other.x,
		w * other.z + x * other.y - y * other.x + z * other.w
	};
}

mathematics::quaternion mathematics::quaternion::operator~()
{
	return quaternion(w, -x, -y, -z);
}
