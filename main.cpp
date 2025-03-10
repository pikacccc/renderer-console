#include <vector>
#include <iostream>
#include <cmath>
#include <thread>
#include <windows.h>
#include "mathematics.h"
#include "linear_transformation.h"

#define WIDTH 800
#define HEIGHT 400
#define FOV 40.0
#define NEAR 0.1
#define FAR 100.0

int screen[WIDTH][HEIGHT];

void draw_line(mathematics::vec2 start, mathematics::vec2 end);
std::string render_screen();
void SetConsoleFontSize(int fontSize);

int main() {
	// ����������� 8 ������
	std::vector<mathematics::vec4> cube = {
		{-0.5f, -0.5f, -0.5f, 1.0f}, // 0
		{ 0.5f, -0.5f, -0.5f, 1.0f}, // 1
		{ 0.5f,  0.5f, -0.5f, 1.0f}, // 2
		{-0.5f,  0.5f, -0.5f, 1.0f}, // 3
		{-0.5f, -0.5f,  0.5f, 1.0f}, // 4
		{ 0.5f, -0.5f,  0.5f, 1.0f}, // 5
		{ 0.5f,  0.5f,  0.5f, 1.0f}, // 6
		{-0.5f,  0.5f,  0.5f, 1.0f}  // 7
	};

	// ����������� 12 ����
	std::vector<std::pair<int, int>> edges = {
		{0, 1}, {1, 2}, {2, 3}, {3, 0}, // ǰ��
		{4, 5}, {5, 6}, {6, 7}, {7, 4}, // ����
		{0, 4}, {1, 5}, {2, 6}, {3, 7}  // ����ǰ��
	};

	mathematics::vec3 eye{ 1.5f,1.5f, -1.5f }; // �����λ��
	mathematics::vec3 enter{ 0.0f, 0.0f,  0.0f }; // ����ĵ�
	mathematics::vec3 up{ 0.0f, 1.0f,  0.0f }; // �Ϸ���

	float angle = 0.0f; // ��ʼ�Ƕ�

	mathematics::mat4 view;
	linear_transformation::get_look_at_mat(eye, enter, up, view);

	mathematics::mat4 project;
	linear_transformation::get_projection_mat(FOV, ((float)WIDTH) / ((float)HEIGHT), NEAR, FAR, project);

	SetConsoleFontSize(1);
	while (true) { // ����ѭ��
		std::vector<mathematics::vec4> temp_cube(cube);
		angle += 0.1f; // ������ת�Ƕ�

		mathematics::mat4 model;
		linear_transformation::get_rotation_mat(mathematics::vec3{ 0.0f, 1.0f, 0.0f }, angle, model); // ��Y����ת

		// �任������Ķ���
		for (auto& vertex : temp_cube) {
			vertex = project * (view * (model * vertex));
			linear_transformation::project_to_ndc(vertex);
		}

		// ������ת�����ӿ�����
		std::vector<mathematics::vec2> viewport_cube;
		for (auto& vertex : temp_cube) {
			viewport_cube.emplace_back(linear_transformation::ndc_to_veiwport(vertex, WIDTH, HEIGHT));
		}

		// �����Ļ
		//for (int i = 0; i < WIDTH; ++i) {
		//	for (int j = 0; j < HEIGHT; ++j) {
		//		screen[i][j] = 0;
		//	}
		//}

		memset(screen, 0, WIDTH * HEIGHT * sizeof(int));
		// ����������ı�
		for (const auto& edge : edges) {
			draw_line(viewport_cube[edge.first], viewport_cube[edge.second]);
		}

		std::cout << render_screen();

		std::cout << "\033[H"; // ʹ��ANSIת�����н�����ƻ���Ļ����
		std::this_thread::sleep_for(std::chrono::milliseconds(30)); // ����֡��
		system("cls");
	}
}

void draw_line(mathematics::vec2 start, mathematics::vec2 end) {
	int x0 = static_cast<int>(start.x);
	int y0 = static_cast<int>(start.y);
	int x1 = static_cast<int>(end.x);
	int y1 = static_cast<int>(end.y);

	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);
	int sx = (x0 < x1) ? 1 : -1;
	int sy = (y0 < y1) ? 1 : -1;
	int err = dx - dy;

	while (true) {
		// ���Ƶ�ǰ��
		if (x0 >= 0 && x0 < WIDTH && y0 >= 0 && y0 < HEIGHT) {
			screen[x0][y0] = 1;
		}

		// ��������յ㣬�˳�ѭ��
		if (x0 == x1 && y0 == y1) break;

		int e2 = 2 * err;
		if (e2 > -dy) {
			err -= dy;
			x0 += sx;
		}
		if (e2 < dx) {
			err += dx;
			y0 += sy;
		}
	}
}

std::string render_screen()
{
	std::string output;
	for (int y = HEIGHT - 1; y >= 0; --y) {
		for (int x = 0; x < WIDTH; ++x) {
			if (screen[x][y] == 1) {
				output += "*";
			}
			else {
				output += " ";
			}
		}
		output += "\n";
	}
	return output;
}

#include <windows.h>

void SetConsoleFontSize(int fontSize) {
	// ��ȡ����̨���ھ��
	HWND consoleWindow = GetConsoleWindow();

	// ��ȡ����̨����豸�ľ��
	HANDLE consoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	// ��ȡ��ǰ�Ŀ���̨������Ϣ
	CONSOLE_FONT_INFOEX fontInfo;
	fontInfo.cbSize = sizeof(fontInfo);
	GetCurrentConsoleFontEx(consoleOutput, FALSE, &fontInfo);

	// �����µ������С
	fontInfo.dwFontSize.X = fontSize; // ������
	fontInfo.dwFontSize.Y = fontSize; // ����߶�

	// ��Ҳ���Ը����������Ƶ���������
	wcscpy_s(fontInfo.FaceName, L"Consolas"); // ʹ����ϲ����������

	// Ӧ���µ���������
	SetCurrentConsoleFontEx(consoleOutput, FALSE, &fontInfo);
}