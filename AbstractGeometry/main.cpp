﻿#define _USE_MATH_DEFINES
#include <math.h>
#include<iostream>
#include<Windows.h>
using namespace std;
using std::cout;
using std::cin;
using std::endl;

namespace Geometry
{
	enum Color
	{
		RED = 0x000000FF,
		GREEN = 0x0000FF00,
		DARK_GREEN = 0x0000AA00,
		BLUE = 0x00FF0000,
		YELLOW = 0x0000FFFF,
		CONSOLE_RED = 0xCC,
		CONSOLE_GREEN = 0xAA,
		CONSOLE_BLUE = 0x99,
		CONSOLE_DEFAULT = 0x07
	};

#define SHAPE_TAKE_PARAMETERS unsigned int start_x, unsigned int start_y, unsigned int line_width, Color color
#define SHAPE_GIVE_PARAMETERS start_x, start_y, line_width, color
	
	class Shape
	{
	protected:
		unsigned int start_x;
		unsigned int start_y;
		unsigned int line_width;
		Color color;
		static const int MIN_START_X = 100;
		static const int MIN_START_Y = 50;
		static const int MAX_START_X = 1000;
		static const int MAX_START_Y = 500;
		static const int MIN_LINE_WIDTH = 1;
		static const int MAX_LINE_WIDTH = 32;
		static const int MIN_SIZE = 50;
		static const int MAX_SIZE = 500;
		static int count;		
		HWND hwnd;
		HDC hdc;	
		HPEN hPen;
		HBRUSH hBrush;
	public:
		virtual double get_area()const = 0;
		virtual double get_perimeter()const = 0;
		
		Shape(SHAPE_TAKE_PARAMETERS) :color(color)
		{
			set_start_x(start_x);
			set_start_y(start_y);
			set_line_width(line_width);		
			count++;
		}
		virtual ~Shape() 
		{
			count--;			
			DeleteObject(hPen);
			DeleteObject(hBrush);
			ReleaseDC(hwnd, hdc);
		}
		int get_count()const
		{
			return count;
		}
		unsigned int get_start_x()const
		{
			return start_x;
		}
		unsigned int get_start_y()const
		{
			return start_y;
		}
		unsigned int get_line_width()const
		{
			return line_width;
		}		
		void set_start_x(unsigned int start_x)
		{
			if (start_x < MIN_START_X) start_x = MIN_START_X;
			if (start_x > MAX_START_X) start_x = MAX_START_X;
			this->start_x = start_x;
		}
		void set_start_y(unsigned int start_y)
		{
			if (start_y < MIN_START_Y) start_y = MIN_START_Y;
			if (start_y > MAX_START_Y) start_y = MAX_START_Y;
			this->start_y = start_y;
		}
		void set_line_width(unsigned int line_width)
		{
			this->line_width = 
				line_width < MIN_LINE_WIDTH ? MIN_LINE_WIDTH : 
				line_width > MAX_LINE_WIDTH ? MAX_LINE_WIDTH :
				line_width;
		}
		int filter_size(int size) const
		{
			return 
				size < MIN_SIZE ? MIN_SIZE : 
				size > MAX_SIZE ? MAX_SIZE : 
				size;
		}
		virtual HDC draw()
		{
			hwnd = FindWindow(NULL, L"Inheritance - Microsoft Visual Studio");			
			hdc = GetDC(hwnd);			
			hPen = CreatePen(PS_SOLID, line_width, color);			
			hBrush = CreateSolidBrush(color);

			SelectObject(hdc, hPen);			
			SelectObject(hdc, hBrush);	

			return hdc;
		}
		virtual void info()
		{
			cout << "Площадь фигуры: " << get_area() << endl;
			cout << "Периметр фигуры: " << get_perimeter() << endl;			
			draw();
		}
	};	

	class Rectangle : public Shape
	{
		double width;
		double height;
	public:
		Rectangle(double width, double height, SHAPE_TAKE_PARAMETERS) :Shape(SHAPE_GIVE_PARAMETERS)
		{						
			set_width(width);
			set_height(height);	
		}
		~Rectangle() {}
		void set_width(double width)
		{
			this->width = filter_size(width);
		}
		void set_height(double height)
		{
			this->height = filter_size(height);
		}
		double get_width()const
		{
			return width;
		}
		double get_height()const
		{
			return height;
		}
		double get_area()const override
		{
			return width * height;
		}
		double get_perimeter() const override
		{
			return (width + height) * 2;
		}
		HDC draw() override
		{
			::Rectangle(Shape::draw(), start_x, start_y, start_x + width, start_y + height);
			return Shape::draw();
		}
		void info() override
		{
			cout << typeid(*this).name() << endl;
			cout << "Ширина прямоугольника: " << get_width() << endl;
			cout << "Высота прямоугольника: " << get_height() << endl;
			Shape::info();
		}
	};

	class Square :public Rectangle
	{
	public:
		Square(double side, SHAPE_TAKE_PARAMETERS) : Rectangle(side, side, SHAPE_GIVE_PARAMETERS) {}
		~Square() {}
	};

	class Disk : public Shape
	{
		double radius;		
	public:
		Disk(double radius, SHAPE_TAKE_PARAMETERS) : Shape(SHAPE_GIVE_PARAMETERS)
		{
			set_radius(radius);	
		}
		~Disk() {}
		void set_radius(double radius)
		{
			this->radius = filter_size(radius);
		}		
		double get_radius()const
		{
			return radius;
		}	
		double get_diameter()const
		{
			return 2 * radius;
		}
		double get_area()const override
		{
			return M_PI * (radius * radius);
		}		
		double get_perimeter() const override
		{			
			return M_PI * get_diameter();
		}
		HDC draw() override
		{
			::Ellipse(Shape::draw(), start_x, start_y, start_x + get_diameter(), start_y + get_diameter());
			return Shape::draw();
		}
		void info() override
		{
			cout << typeid(*this).name() << endl;
			cout << "Радиус круга: " << get_radius() << endl;					
			cout << "Диаметрус круга: " << get_diameter() << endl;					
			Shape::info();
		}
	};

	class Triangle : public Shape
	{
		
	public:
		Triangle(SHAPE_TAKE_PARAMETERS) :Shape(SHAPE_GIVE_PARAMETERS){}
		~Triangle() {}
		virtual double get_height() const = 0;			
		void info() override
		{
			cout << "Высота треугольника: " << get_height() << endl;			
			Shape::info();
		}
	};	

	class EquilateralTriangle : public Triangle
	{
		double side;
	public:
		EquilateralTriangle(double side, SHAPE_TAKE_PARAMETERS) : Triangle(SHAPE_GIVE_PARAMETERS)
		{
			set_side(side);
		}
		~EquilateralTriangle() {}
		void set_side(double side)
		{
			this->side = filter_size(side);
		}
		double get_side()const
		{
			return side;
		}
		double get_height()const override
		{
			return sqrt(pow(side, 2) - pow(side / 2, 2));
		}
		double get_area() const override
		{
			return side * get_height() / 2;
		}
		double get_perimeter() const override
		{
			return side * 3;
		}
		HDC draw() override
		{
			POINT vertices[] =
			{
				{start_x, start_y + side},
				{start_x + side, start_y + side},
				{start_x + side / 2, start_y + side - get_height()}
			};

			::Polygon(Shape::draw(), vertices, 3);
			return Shape::draw();
		}
		void info() override
		{
			cout << typeid(*this).name() << endl;
			cout << "Длина стороны: " << get_side() << endl;
			Triangle::info();
		}
	};

	class IsoscelesTriangle : public Triangle
	{
		double base;
		double side;
	public:
		IsoscelesTriangle(double base, double side, SHAPE_TAKE_PARAMETERS)
			: Triangle(SHAPE_GIVE_PARAMETERS)
		{
			set_base(base);
			set_side(side);
		}
		~IsoscelesTriangle() {}
		void set_base(double base)
		{
			this->base = filter_size(base);
		}
		void set_side(double side)
		{
			this->side = filter_size(side);
			if (this->side <= base / 2) this->side = base * 3 / 5;
		}
		double get_base() const
		{
			return base;
		}
		double get_side() const
		{
			return side;
		}
		double get_height() const override
		{
			return sqrt(pow(side,2) - pow(base/2, 2));
		}
		double get_area() const override
		{
			return base * get_height() / 2;
		}
		double get_perimeter()const override
		{
			return base + (side * 2);
		}
		HDC draw() override
		{	
			POINT vertices[] =
			{
				{start_x, start_y + side},
				{start_x + base, start_y + side},
				{start_x + base / 2, start_y + side - get_height()}
			};

			::Polygon(Shape::draw(), vertices, 3);
			return Shape::draw();
		}
		void info() override
		{
			cout << typeid(*this).name() << endl;
			cout << "Oснование треугольника: " << get_base() << endl;
			cout << "Сторона треугольника: " << get_base() << endl;
			Triangle::info();
		}
	};

	int Shape::count = 0;
}

void main()
{
	setlocale(LC_ALL, "");
	//Shape shape(Color::CONSOLE_RED);
	Geometry::Square square(5, 100, 100, 5, Geometry::Color::RED);
	/*cout << "Длина стороны: " << square.get_side() << endl;
	cout << "Площадь квадрата: " << square.get_area() << endl;
	cout << "Периметр квадрата: " << square.get_perimeter() << endl;
	square.draw();*/
	square.info();

	Geometry::Rectangle rect(150, 130, 300, 120, 1, Geometry::Color::BLUE);			
	rect.info();

	Geometry::Disk disk(10000, 500, 100, 5, Geometry::Color::YELLOW);
	disk.info();
	
	//Geometry::Triangle triangle(300, 300, 50, Geometry::Color::GREEN);
	//triangle.info();

	//Geometry::RightTrinagle right(300, 200, 200, 100, 5, Geometry::Color::GREEN);
	//right.info();

	Geometry::IsoscelesTriangle isosceles(200, 10, 500, 200, 20, Geometry::Color::DARK_GREEN);
	isosceles.info();

	Geometry::EquilateralTriangle equilateral(150, 300, 100, 1, Geometry::Color::DARK_GREEN);
	equilateral.info();

	//cout << "Количество фигур: " << right.get_count() << endl;
}