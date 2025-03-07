#pragma once

#include <math.h>

namespace mathematics {
	struct vec2 {
		float x;
		float y;

		vec2(float x, float y) :x(x), y(y) {}

		vec2 operator +(const vec2& other) const;
		vec2 operator -(const vec2& other) const;
		vec2 operator *(const float& other) const;

		void normalize();
	};

	struct vec3 {
		float x;
		float y;
		float z;

		vec3(float x, float y, float z) :x(x), y(y), z(z) {}

		vec3 operator +(const vec3& other) const;
		vec3 operator -(const vec3& other) const;
		vec3 operator *(const float& other) const;

	public:
		void normalize();
	};

	struct vec4 {
		float x;
		float y;
		float z;
		float w;

		vec4(float x, float y, float z, float w) :x(x), y(y), z(z), w(w) {}

		vec4 operator +(const vec4& other) const;
		vec4 operator -(const vec4& other) const;
		vec4 operator *(const float& other) const;

	public:
		void normalize();
	};

	struct vertex {
		vec3 position;
	};

	struct mat2
	{
		float mat[2][2];

		mat2() {
			for (int i = 0; i < 2; ++i) {
				for (int j = 0; j < 2; ++j) {
					mat[i][j] = 0;
				}
			}
		}

		float* operator[](int rowIndex);
		const float* operator[](int rowIndex) const;
	};

	struct mat3
	{
		float mat[3][3];

		mat3() {
			for (int i = 0; i < 3; ++i) {
				for (int j = 0; j < 3; ++j) {
					mat[i][j] = 0;
				}
			}
		}

		float* operator[](int rowIndex);
		const float* operator[](int rowIndex) const;
	};

	struct mat4
	{
		float mat[4][4];

		mat4() {
			for (int i = 0; i < 4; ++i) {
				for (int j = 0; j < 4; ++j) {
					mat[i][j] = 0;
				}
			}
		}

		float* operator[](int rowIndex);
		const float* operator[](int rowIndex) const;

		vec4 operator*(const vec4& other);
		mat4 operator*(const mat4& other);
	};


	struct quaternion
	{
		float w;
		float x;
		float y;
		float z;

		quaternion(float w, float x, float y, float z) : w(w), x(x), y(y), z(z) {}

		quaternion operator*(const quaternion& other) const;
		quaternion operator~();
	};

	const float PI = 3.1415926;
	const vec2 ZERO_VEC2{ 0, 0 };
	const vec3 ZERO_VEC3{ 0, 0, 0 };
	const vec4  ZERO_VEC4{ 0, 0, 0, 0 };

	vec2 normalize(const vec2& vec);
	vec3 normalize(const vec3& vec);
	vec4 normalize(const vec4& vec);

	vec3 cross(const vec3& a, const vec3& b);

	float dot(const vec3& a, const vec3& b);
}