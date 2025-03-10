#include "linear_transformation.h"

void linear_transformation::get_rotation_mat(const mathematics::vec3& axis, float angle, mathematics::mat4& res)
{
	float cos_theta = cos(angle);
	float sin_theta = sin(angle);

	mathematics::vec3 normalize_axis = normalize(axis);

	res[0][0] = cos_theta + axis.x * axis.x * (1 - cos_theta);
	res[0][1] = axis.x * axis.y * (1 - cos_theta) - axis.z * sin_theta;
	res[0][2] = axis.x * axis.z * (1 - cos_theta) + axis.y * sin_theta;
	res[0][3] = 0;

	res[1][0] = axis.y * axis.x * (1 - cos_theta) + axis.z * sin_theta;
	res[1][1] = cos_theta + axis.y * axis.y * (1 - cos_theta);
	res[1][2] = axis.y * axis.z * (1 - cos_theta) - axis.x * sin_theta;
	res[1][3] = 0;

	res[2][0] = axis.z * axis.x * (1 - cos_theta) - axis.y * sin_theta;
	res[2][1] = axis.z * axis.y * (1 - cos_theta) + axis.x * sin_theta;
	res[2][2] = cos_theta + axis.z * axis.z * (1 - cos_theta);
	res[2][3] = 0;

	res[3][0] = 0;
	res[3][1] = 0;
	res[3][2] = 0;
	res[3][3] = 1;
}

void linear_transformation::get_rotation_quaternion(const mathematics::vec3& axis, float angle, mathematics::quaternion& res)
{
	mathematics::vec3 n_axis = normalize(axis);

	float half_angle = angle / 2.0f;
	float sin_half_angle = sin(half_angle);

	res.w = cos(half_angle);
	res.w = n_axis.x * sin_half_angle;
	res.w = n_axis.y * sin_half_angle;
	res.w = n_axis.z * sin_half_angle;
}

mathematics::vec3 linear_transformation::rotation_by_quaternion(const mathematics::vec3& position, const mathematics::vec3& axis, float angle)
{
	mathematics::quaternion position_quaternion{ 0,position.x,position.y,position.z };

	mathematics::quaternion rotate_quaternion{ 0,0,0,0 };
	linear_transformation::get_rotation_quaternion(axis, angle, rotate_quaternion);

	mathematics::quaternion rotate_quaternion_conjugate = ~rotate_quaternion;

	mathematics::quaternion fina_quaternion = rotate_quaternion * position_quaternion * rotate_quaternion_conjugate;

	return mathematics::vec3{ fina_quaternion.x,fina_quaternion.y,fina_quaternion.z };
}

mathematics::vec3 linear_transformation::rotation_by_mat(const mathematics::vec3& position, const mathematics::vec3& axis, float angle)
{
	mathematics::vec4 temp_position(position.x, position.y, position.z, 0);
	mathematics::mat4 rotate_mat;
	linear_transformation::get_rotation_mat(axis, angle, rotate_mat);

	mathematics::vec4 fina_position = rotate_mat * temp_position;
	return mathematics::vec3{ fina_position.x, fina_position.y, fina_position.z };
}

void linear_transformation::get_scale_mat(float scale_x, float scale_y, float scale_z, mathematics::mat4& res)
{
	res[0][0] = scale_x;
	res[0][1] = 0;
	res[0][2] = 0;
	res[0][3] = 0;

	res[1][0] = 0;
	res[1][1] = scale_y;
	res[1][2] = 0;
	res[1][3] = 0;

	res[2][0] = 0;
	res[2][1] = 0;
	res[2][2] = scale_z;
	res[2][3] = 0;

	res[3][0] = 0;
	res[3][1] = 0;
	res[3][2] = 0;
	res[3][3] = 1;
}

void linear_transformation::get_translation_mat(const mathematics::vec3& translation_coefficient, mathematics::mat4& res)
{
	res[0][0] = 1;
	res[0][1] = 0;
	res[0][2] = 0;
	res[0][3] = translation_coefficient.x;

	res[1][0] = 0;
	res[1][1] = 1;
	res[1][2] = 0;
	res[1][3] = translation_coefficient.y;

	res[2][0] = 0;
	res[2][1] = 0;
	res[2][2] = 1;
	res[2][3] = translation_coefficient.z;

	res[3][0] = 0;
	res[3][1] = 0;
	res[3][2] = 0;
	res[3][3] = 1;
}

void linear_transformation::get_look_at_mat(const mathematics::vec3& eye, const mathematics::vec3& center, const mathematics::vec3& world_up, mathematics::mat4& res)
{
	mathematics::vec3 front = center - eye;
	front.normalize();

	mathematics::vec3 right = mathematics::cross(front, world_up);

	mathematics::vec3 up = mathematics::cross(right, front);

	float n_right_dot_eye = -mathematics::dot(right, eye);
	float n_up_dot_eye = -mathematics::dot(up, eye);
	float n_front_dot_eye = -mathematics::dot(front, eye);

	res[0][0] = right.x;
	res[0][1] = right.y;
	res[0][2] = right.z;
	res[0][3] = n_right_dot_eye;

	res[1][0] = up.x;
	res[1][1] = up.y;
	res[1][2] = up.z;
	res[1][3] = n_up_dot_eye;

	res[2][0] = -front.x;
	res[2][1] = -front.y;
	res[2][2] = -front.z;
	res[2][3] = n_front_dot_eye;

	res[3][0] = 0;
	res[3][1] = 0;
	res[3][2] = 0;
	res[3][3] = 1;
}

void linear_transformation::get_projection_mat(float right, float left, float top, float bottom, float near, float far, mathematics::mat4& res)
{
	res[0][0] = (2 * near) / (right - left);
	res[0][1] = 0;
	res[0][2] = (right + left) / (right - left);
	res[0][3] = 0;

	res[1][0] = 0;
	res[1][1] = (2 * near) / (top - bottom);
	res[1][2] = (top + bottom) / (top - bottom);
	res[1][3] = 0;

	res[2][0] = 0;
	res[2][1] = 0;
	res[2][2] = -(far + near) / (far - near);
	res[2][3] = -2 * far * near / (far - near);

	res[3][0] = 0;
	res[3][1] = 0;
	res[3][2] = -1;
	res[3][3] = 0;
}

void linear_transformation::get_projection_mat(float fovy, float aspect, float near, float far, mathematics::mat4& res)
{
	float rad = acos(-1.0f) / 180;

	float tan_half_fovy = tan(fovy / 2.0f * rad);

	float top = near * tan_half_fovy;
	float right = top * aspect;

	res[0][0] = near / right;
	res[0][1] = 0;
	res[0][2] = 0;
	res[0][3] = 0;

	res[1][0] = 0;
	res[1][1] = near / top;
	res[1][2] = 0;
	res[1][3] = 0;

	res[2][0] = 0;
	res[2][1] = 0;
	res[2][2] = -1;
	res[2][3] = -2 * near;

	res[3][0] = 0;
	res[3][1] = 0;
	res[3][2] = -1;
	res[3][3] = 0;
}

void linear_transformation::project_to_ndc(mathematics::vec4& vec)
{
	vec.x = vec.x / vec.w;
	vec.y = vec.y / vec.w;
	vec.z = vec.z / vec.w;
	vec.w = 1.0f;
}

mathematics::vec2 linear_transformation::ndc_to_veiwport(mathematics::vec4& vec, float width, float height)
{
	mathematics::vec2 res = mathematics::ZERO_VEC2;

	res.x = (vec.x + 1.0f) / 2.0f * width;
	res.y = (vec.y + 1.0f) / 2.0f * height;

	return res;
}



