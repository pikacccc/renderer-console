#include <vector>
#include "mathematics.h"
#include "linear_transformation.h"

#define WIDTH 80
#define HEIGHT 40
#define FOV 40.0
#define NEAR 1.0
#define FAR 100.0

int screen[WIDTH][HEIGHT];

void draw_line(int x0, int y0, int x1, int y1);

int main() {
	std::vector<mathematics::vec4> triangle = {
		mathematics::vec4{ 0.0f, 1.0f, 0.0f, 0.0f},
		mathematics::vec4{ 0.5f, 0.0f, 0.0f, 0.0f},
		mathematics::vec4{-0.5f, 0.0f, 0.0f, 0.0f},
	};

	mathematics::vec3 eye{ 0.0f, 0.0f, -1.0f };
	mathematics::vec3 enter{ 0.0f, 0.0f,  0.0f };
	mathematics::vec3 up{ 0.0f, 1.0f,  0.0f };

	mathematics::mat4 model;
	linear_transformation::get_translation_mat(mathematics::vec3{ 0.0f,0.0f,0.0f }, model);
	mathematics::mat4 view;
	linear_transformation::get_look_at_mat(eye, enter, up, view);

	mathematics::mat4 project;
	linear_transformation::get_projection_mat(FOV, ((float)WIDTH) / ((float)HEIGHT), NEAR, FAR, project);

	triangle[0] = project * (view * (model * triangle[0]));
	triangle[1] = project * (view * (model * triangle[1]));
	triangle[2] = project * (view * (model * triangle[2]));

	linear_transformation::project_to_ndc(triangle[0]);
	linear_transformation::project_to_ndc(triangle[1]);
	linear_transformation::project_to_ndc(triangle[2]);

	std::vector<mathematics::vec2> viewport_triangle;

	viewport_triangle.emplace_back(linear_transformation::ndc_to_veiwport(triangle[0], WIDTH, HEIGHT));
	viewport_triangle.emplace_back(linear_transformation::ndc_to_veiwport(triangle[1], WIDTH, HEIGHT));
	viewport_triangle.emplace_back(linear_transformation::ndc_to_veiwport(triangle[2], WIDTH, HEIGHT));
}

void draw_line(mathematics::vec2 start, mathematics::vec2 end) {
	bool steep = (fabs(end.y - start.y) > fabs(end.x - start.x));
	if (steep) {
		std::swap(start.x, start.y);
		std::swap(end.x, end.y);
	}
	if (start.x > end.x) {
		std::swap(start.x, end.x);
		std::swap(start.y, end.y);
	}
	int dx = end.x - start.x;
	int dy = fabs(end.y - end.y);
	int error = dx / 2;
	int ystep = (start.y < end.y) ? 1 : -1;
	int y = start.y;

	int x;
	for (x = start.x; x <= end.x; x++) {
		if (steep) {
			screen[y][x] = 1;
		}
		else {
			screen[x][y] = 1;
		}
		error -= dy;
		if (error < 0) {
			y += ystep;
			error += dx;
		}
	}
}