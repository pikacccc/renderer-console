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
	// 定义立方体的 8 个顶点
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

	// 定义立方体的 12 条边
	std::vector<std::pair<int, int>> edges = {
		{0, 1}, {1, 2}, {2, 3}, {3, 0}, // 前面
		{4, 5}, {5, 6}, {6, 7}, {7, 4}, // 后面
		{0, 4}, {1, 5}, {2, 6}, {3, 7}  // 连接前后
	};

	mathematics::vec3 eye{ 1.5f,1.5f, -1.5f }; // 摄像机位置
	mathematics::vec3 enter{ 0.0f, 0.0f,  0.0f }; // 看向的点
	mathematics::vec3 up{ 0.0f, 1.0f,  0.0f }; // 上方向

	float angle = 0.0f; // 初始角度

	mathematics::mat4 view;
	linear_transformation::get_look_at_mat(eye, enter, up, view);

	mathematics::mat4 project;
	linear_transformation::get_projection_mat(FOV, ((float)WIDTH) / ((float)HEIGHT), NEAR, FAR, project);

	SetConsoleFontSize(1);
	while (true) { // 动画循环
		std::vector<mathematics::vec4> temp_cube(cube);
		angle += 0.1f; // 更新旋转角度

		mathematics::mat4 model;
		linear_transformation::get_rotation_mat(mathematics::vec3{ 0.0f, 1.0f, 0.0f }, angle, model); // 绕Y轴旋转

		// 变换立方体的顶点
		for (auto& vertex : temp_cube) {
			vertex = project * (view * (model * vertex));
			linear_transformation::project_to_ndc(vertex);
		}

		// 将顶点转换到视口坐标
		std::vector<mathematics::vec2> viewport_cube;
		for (auto& vertex : temp_cube) {
			viewport_cube.emplace_back(linear_transformation::ndc_to_veiwport(vertex, WIDTH, HEIGHT));
		}

		// 清空屏幕
		//for (int i = 0; i < WIDTH; ++i) {
		//	for (int j = 0; j < HEIGHT; ++j) {
		//		screen[i][j] = 0;
		//	}
		//}

		memset(screen, 0, WIDTH * HEIGHT * sizeof(int));
		// 绘制立方体的边
		for (const auto& edge : edges) {
			draw_line(viewport_cube[edge.first], viewport_cube[edge.second]);
		}

		std::cout << render_screen();

		std::cout << "\033[H"; // 使用ANSI转义序列将光标移回屏幕顶部
		std::this_thread::sleep_for(std::chrono::milliseconds(30)); // 控制帧率
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
		// 绘制当前点
		if (x0 >= 0 && x0 < WIDTH && y0 >= 0 && y0 < HEIGHT) {
			screen[x0][y0] = 1;
		}

		// 如果到达终点，退出循环
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
	// 获取控制台窗口句柄
	HWND consoleWindow = GetConsoleWindow();

	// 获取控制台输出设备的句柄
	HANDLE consoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	// 获取当前的控制台字体信息
	CONSOLE_FONT_INFOEX fontInfo;
	fontInfo.cbSize = sizeof(fontInfo);
	GetCurrentConsoleFontEx(consoleOutput, FALSE, &fontInfo);

	// 设置新的字体大小
	fontInfo.dwFontSize.X = fontSize; // 字体宽度
	fontInfo.dwFontSize.Y = fontSize; // 字体高度

	// 你也可以更改字体名称等其他属性
	wcscpy_s(fontInfo.FaceName, L"Consolas"); // 使用你喜欢的字体名

	// 应用新的字体设置
	SetCurrentConsoleFontEx(consoleOutput, FALSE, &fontInfo);
}