#include <vector>
#include "mathematics.h"
#include "linear_transformation.h"

#define WIDTH 80
#define HEIGHT 40
#define FOV 40.0
#define NEAR 1.0
#define FAR 100.0

int screen[WIDTH][HEIGHT];

int main() {
	std::vector<mathematics::vec3> triangle = {
		mathematics::vec3{ 0.0f, 1.0f, 0.0f},
		mathematics::vec3{ 0.5f, 0.0f, 0.0f},
		mathematics::vec3{-0.5f, 0.0f, 0.0f},
	};

	mathematics::vec3 eye{ 0.0f, 0.0f, -1.0f };
	mathematics::vec3 enter{ 0.0f, 0.0f,  0.0f };
	mathematics::vec3 up{ 0.0f, 1.0f,  0.0f };

	mathematics::mat4 model;

	mathematics::mat4 view;
	linear_transformation::get_look_at_mat(eye, enter, up, view);

	mathematics::mat4 project;
	linear_transformation::get_projection_mat(FOV, ((float)WIDTH) / ((float)HEIGHT), NEAR, FAR, project);
}