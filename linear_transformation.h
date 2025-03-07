#pragma once

#include <math.h>

#include "mathematics.h"

namespace linear_transformation {
	void get_rotation_mat(const mathematics::vec3& axis, float angle, mathematics::mat4& res);
	void get_rotation_quaternion(const mathematics::vec3& axis, float angle, mathematics::quaternion& res);

	mathematics::vec3 rotation_by_quaternion(const mathematics::vec3& position, const mathematics::vec3& axis, float angle);
	mathematics::vec3 rotation_by_mat(const mathematics::vec3& position, const mathematics::vec3& axis, float angle);

	void get_scale_mat(float scale_x, float scale_y, float scale_z, mathematics::mat4& res);
	void get_translation_mat(const mathematics::vec3& translation_coefficient, mathematics::mat4& res);

	void get_look_at_mat(const mathematics::vec3& eye, const mathematics::vec3& center, const mathematics::vec3& up, mathematics::mat4& res);

	void get_projection_mat(float right, float left, float up, float down, float near, float far, mathematics::mat4& res);
	void get_projection_mat(float fovy, float aspect, float near, float far, mathematics::mat4& res);

	void project_to_ndc(mathematics::vec4& vec);

	mathematics::vec2 ndc_to_veiwport(mathematics::vec4& vec, float width, float height);
}