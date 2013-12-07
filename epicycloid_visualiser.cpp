/**
 * Visualiser for epicycloids
 * Date 2013-12-08
 *
 * Thanks to Darek Cidlinský for inspiration
 *
 * Licensed under The MIT License (MIT)
 *
 * Copyright (C) 2013 Stanley Hawkeye
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <vector>
#include <opencv2/highgui/highgui.hpp>
#include "generate_epicycloid.hpp"
using namespace cv;

#define WIDTH 500
#define HEIGHT 500

#define DW 200
#define DH 200

#define IMAGE_WINDOW "Epicycloid"
#define CONTROLS_WINDOW "Controls Window"

int numerator = 3;
int denominator = 5;
int render_type = 0;
int step = 1;

int color_red = 255;
int color_green = 255;
int color_blue = 255;

Point center(WIDTH/2, HEIGHT/2);

void render_points(const std::vector<Point2f>& points, Mat& destination, Point2f shift = Point(0,0))
{
	for(std::vector<Point2f>::const_iterator pt = points.begin(); pt != points.end(); pt++)
	{
		Point point(shift.x + pt->x, shift.y + pt->y);
		line(destination, point, point, Scalar(color_red,color_green,color_blue));
	}
}

/**
 * Originally created as a bug
 */
void render_linesPairWithLast(const std::vector<Point2f>& points, Mat& destination, Point2f shift = Point(0,0))
{
	if(points.size() < 1)
		return;

	Point last(center.x + points.end()->x, center.y + points.end()->y);
	for(std::vector<Point2f>::const_iterator pt = points.begin(); pt != points.end(); pt++)
	{
		Point point(shift.x + pt->x, shift.y + pt->y);
		line(destination, last, point, Scalar(color_red,color_green,color_blue));
	}
}

void render_lines(const std::vector<Point2f>& points, Mat& destination, Point2f shift = Point(0,0))
{
	if(points.size() < 2)
		return;

	for(unsigned int i = 1; i < points.size(); i++)
	{
		Point point1(shift.x + points[i].x, shift.y + points[i].y);
		Point point2(shift.x + points[i-1].x, shift.y + points[i-1].y);
		line(destination, point1, point2, Scalar(color_red,color_green,color_blue));
	}
}

void render_linesFromCenter(const std::vector<Point2f>& points, Mat& destination, Point2f center = Point(0,0))
{
	for(unsigned int i = 0; i < points.size(); i++)
	{
		Point point(center.x + points[i].x, center.y + points[i].y);
		line(destination, center, point, Scalar(color_red,color_green,color_blue));
	}
}

void generate_image(int x=0, void* y=0)
{
	std::vector<Point2f> points;
	generate_epicycloid(points, numerator, denominator, step * 0.005 + 0.001);
	Mat plot(HEIGHT, WIDTH, CV_8UC3, Scalar(0, 0, 0));
	switch(render_type)
	{
	case 0:
		render_points(points, plot, center);

		break;

	case 1:
		render_lines(points, plot, center);
		break;

	case 2:
		render_linesFromCenter(points, plot, center);
		break;

	case 3:
		render_linesPairWithLast(points, plot, center);
		break;
	}
	imshow(IMAGE_WINDOW, plot);
}

int main()
{
	namedWindow(IMAGE_WINDOW, WINDOW_AUTOSIZE);
	namedWindow(CONTROLS_WINDOW, WINDOW_AUTOSIZE);

	createTrackbar("Numerator", CONTROLS_WINDOW, &numerator, min(DW, DH), generate_image);
	createTrackbar("Denominator", CONTROLS_WINDOW, &denominator, min(DW, DH), generate_image);
	createTrackbar("Render Type", CONTROLS_WINDOW, &render_type, 3, generate_image);
	createTrackbar("Step", CONTROLS_WINDOW, &step, 200, generate_image);

	createTrackbar("Red", CONTROLS_WINDOW, &color_red, 255, generate_image);
	createTrackbar("Green", CONTROLS_WINDOW, &color_green, 255, generate_image);
	createTrackbar("Blue", CONTROLS_WINDOW, &color_blue, 255, generate_image);

	generate_image();

	waitKey();

	destroyAllWindows();
}


