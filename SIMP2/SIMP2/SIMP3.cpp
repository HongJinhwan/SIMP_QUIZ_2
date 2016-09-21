#include <GLFW/glfw3.h>
#include <cstring>
#include <stdlib.h>		  // srand, rand
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include "math.h"

const int width = 640;
const int height = 480;
const int line_width = 5; 
 
float* pixels = new float[width*height * 3];

void drawPixel(const int& i, const int& j, const float& red, const float& green, const float& blue)
{
	pixels[(i + width* j) * 3 + 0] = red;
	pixels[(i + width* j) * 3 + 1] = green;
	pixels[(i + width* j) * 3 + 2] = blue;
}

// scratched from https://courses.engr.illinois.edu/ece390/archive/archive-f2000/mp/mp4/anti.html
// see 'Rasterization' part.
void drawLine(const int& i0, const int& j0, const int& i1, const int& j1, const float& red, const float& green, const float& blue)
{
	for (int i = i0; i <= i1; i++)
	{
		const int j = (j1 - j0)*(i - i0) / (i1 - i0) + j0;

		drawPixel(i, j, red, green, blue);
	}
}

void drawBoldLine(const int& i0, const int& j0, const int& i1, const int& j1, const float& red, const float& green, const float& blue)
{
	for (int i = i0; i <= i1; i++)
	{
		const int j = (j1 - j0)*(i - i0) / (i1 - i0) + j0;

		for (int a = i - line_width; a <= i + line_width; a++) {
			for (int b = j - line_width; b <= j + line_width; b++) {
				drawPixel(a, b, red, green, blue);
			}
		}
	}
}

void drawSquare(const int& i0, const int& j0, const int& i1, const int& j1, const float& red, const float& green, const float& blue)
{
	for (int i = i0; i <= i1; i++)
	{
		drawPixel(i, j0, red, green, blue);
	}
	for (int i = i0; i <= i1; i++)
	{
		drawPixel(i, j1, red, green, blue);
	}
	for (int j = j1; j <= j0; j++)
	{
		drawPixel(i0, j, red, green, blue);
	}
	for (int j = j1; j <= j0; j++)
	{
		drawPixel(i1, j, red, green, blue);
	}
}

void drawFilledSquare(const int& i0, const int& j0, const int& i1, const int& j1, const float& red, const float& green, const float& blue)
{
	for (int i = i0; i <= i1; i++)
	{
		for (int j = j1; j <= j0; j++)
		{
			drawPixel(i, j, red, green, blue);
		}
	}
}

void drawTriangle(const int& i0, const int& j0, const float& length, const float& red, const float& green, const float& blue) {
	drawLine(i0, j0, i0+length, j0, 1.0f, 0.0f, 0.0f);
	drawLine(i0, j0, i0 + length / 2, j0 + length / 2 * 1.732, 1.0f, 0.0f, 0.0f);
	drawLine(i0 + length / 2, j0 + length / 2 * 1.732, i0 + length, j0, 1.0f, 0.0f, 0.0f);
}

void drawPentagon(const int& i0, const int& j0, const float& length, const float& red, const float& green, const float& blue) {
	drawLine(i0 - length / 2, j0 - 1.732 / 2 * length, i0 + length / 2, j0 - 1.732 / 2 * length, 1.0f, 0.0f, 0.0f);
	drawLine(i0 + length / 2, j0 - 1.732 / 2 * length, i0+length, j0, 1.0f, 0.0f, 0.0f);
	drawLine(i0, j0 + length, i0 + length, j0,  1.0f, 0.0f, 0.0f);
	drawLine( i0-length, j0, i0, j0 + length, 1.0f, 0.0f, 0.0f);
	drawLine(i0 - length, j0, i0 - length / 2, j0 - 1.732 / 2 * length, 1.0f, 0.0f, 0.0f);
}

void drawCircle(const int& i0, const int& j0, const float& r, const float& red, const float& green, const float& blue) {
	for (int i = i0 - r; i <= i0 + r; i++) {
		for (int j = j0 - r; j <= j0 + r; j++) {
			int f = (i - i0)*(i - i0) + (j - j0)*(j - j0) - r*r;
			if (f <= 50 && f>=-50) {
				drawPixel(i, j, red, green, blue);
			}
		}
	}
}

void drawOnPixelBuffer()
{
	//std::memset(pixels, 1.0f, sizeof(float)*width*height * 3); // doesn't work
	std::fill_n(pixels, width*height * 3, 1.0f);	// white background

													//for (int i = 0; i<width*height; i++) {
													//	pixels[i * 3 + 0] = 1.0f; // red 
													//	pixels[i * 3 + 1] = 1.0f; // green
													//	pixels[i * 3 + 2] = 1.0f; // blue
													//}

	const int i = rand() % width, j = rand() % height;
	drawPixel(i, j, 0.0f, 0.0f, 0.0f);

	// drawing a line
	//TODO: anti-aliasing
	const int i0 = 100, i1 = 200;
	const int j0 = 50, j1 = 80;

	//TODO: try moving object
}


int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glClearColor(1, 1, 1, 1); // while background

							  /* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		//glClear(GL_COLOR_BUFFER_BIT);

		drawOnPixelBuffer();

		//TODO: RGB struct
		//Make a pixel drawing function
		//Make a line drawing function

		drawBoldLine(50, 380, 120, 450, 1.0f, 0.0f, 0.0f); //±½Àº Á÷¼±

		drawSquare(250, 450, 350, 350, 1.0f, 0.0f, 0.0f); //ºó »ç°¢Çü

		drawFilledSquare(450, 450, 550, 350, 1.0f, 0.0f, 0.0f); //»öÄ¥µÈ »ç°¢Çü

		drawTriangle(50, 100, 150, 1.0f, 0.0f, 0.0f);//»ï°¢Çü

		drawPentagon(300, 150, 50, 1.0f, 0.0f, 0.0f); //¿À°¢Çü

		drawCircle(450, 150, 50, 1.0f, 0.0f, 0.0f);


		glDrawPixels(width, height, GL_RGB, GL_FLOAT, pixels);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	glfwTerminate();

	delete[] pixels; // or you may reuse pixels array 

	return 0;
}

 
