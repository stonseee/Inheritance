#define _USE_MATH_DEFINES
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
	public:
		virtual double get_area()const = 0;
		virtual double get_perimeter()const = 0;
		virtual void draw()const = 0;
		Shape(SHAPE_TAKE_PARAMETERS) :color(color)
		{
			set_start_x(start_x);
			set_start_y(start_y);
			set_line_width(line_width);								
			/*if (start_y > 720)
			{
				set_start_y(720);
			}
			if (start_x > 1280)
			{
				set_start_x(1280);
			}		*/	
			count++;
		}
		virtual ~Shape() 
		{
			count--;
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
		virtual void info()const
		{
			cout << "Площадь фигуры: " << get_area() << endl;
			cout << "Периметр фигуры: " << get_perimeter() << endl;
			draw();
		}
	};

	/*class Square :public Shape
	{
		double side;
	public:
		Square(double side, Color color) : Shape(color)
		{
			set_side(side);
		}
		~Square() {}
		void set_side(double side)
		{
			this->side = side;
		}
		double get_side()const
		{
			return this->side;
		}
		double get_area()const override
		{
			return side * side;
		}
		double get_perimeter()const override
		{
			return side * 4;
		}
		void draw()const override
		{
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, color);
			for (int i = 0; i < side; i++)
			{
				for (int i = 0; i < side; i++)
				{
					cout << "* ";
				}
				cout << endl;
			}
			SetConsoleTextAttribute(hConsole, Color::CONSOLE_DEFAULT);
		}
		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "Длина стороны: " << get_side() << endl;
			Shape::info();
		}
	};*/

	

	class Rectangle : public Shape
	{
		double width;
		double height;
	public:
		Rectangle(double width, double height, SHAPE_TAKE_PARAMETERS) :Shape(SHAPE_GIVE_PARAMETERS)
		{						
			set_width(width);
			set_height(height);	

			/*if (get_height() + get_start_y() > 360 + 720)
			{
				set_height(360 + 720 - get_start_y());
				set_width(get_height() / (height / width));				
			}

			if (get_width() + get_start_x() > 640 + 1280)
			{
				set_width(640 + 1280 - get_start_x());
				set_height(get_width() / (width / height));				
			}	*/		
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
		void draw() const override
		{
			HWND hwnd = FindWindow(NULL, L"Inheritance - Microsoft Visual Studio");
			HDC hdc = GetDC(hwnd);
			HPEN hPen = CreatePen(PS_SOLID, line_width, color);
			HBRUSH hBrush = CreateSolidBrush(color);
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);
			::Rectangle(hdc, start_x, start_y, start_x + width, start_y + height);
			DeleteObject(hPen);
			DeleteObject(hBrush);
			ReleaseDC(hwnd, hdc);
			
		}
		void info()const override
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

			/*if ((radius * 2) + get_start_y() > 1280)
			{
				set_radius((1280 - get_start_y()) / 2);
			}	*/				
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
			//return 2 * M_PI * radius;
			return M_PI * get_diameter();
		}
		void draw() const override
		{
			HWND hwnd = FindWindow(NULL, L"Inheritance - Microsoft Visual Studio");
			HDC hdc = GetDC(hwnd);
			HPEN hPen = CreatePen(PS_SOLID, 5, color);
			HBRUSH hBrush = CreateSolidBrush(color);
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);
			::Ellipse(hdc, start_x, start_y, start_x + get_diameter(), start_y + get_diameter());
			DeleteObject(hPen);
			DeleteObject(hBrush);
			ReleaseDC(hwnd, hdc);
		}
		void info()const override
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
		Triangle(SHAPE_TAKE_PARAMETERS) :Shape(SHAPE_GIVE_PARAMETERS)
		{

		}
		~Triangle() {}
		virtual double get_height() const = 0;
		virtual double get_width() const = 0;
		void info() const override
		{
			cout << "Высота треугольника: " << get_height() << endl;
			cout << "Ширина треугольника: " << get_width() << endl;
			Shape::info();
		}
	};
	
	class RightTrinagle : public Triangle
	{
		double width;
		double height;
	public:
		RightTrinagle(double width, double height, SHAPE_TAKE_PARAMETERS) : Triangle(SHAPE_GIVE_PARAMETERS)
		{
			set_width(width);
			set_height(height);
		}
		~RightTrinagle() {}
		void set_width(double width)
		{
			this->width = filter_size(width);
		}
		void set_height(double height)
		{
			this->height = filter_size(height);
		}
		double get_height() const override
		{
			return height;
		}
		double get_width() const override
		{
			return width;
		}
		double get_area()const override
		{
			return (height * width) / 2;
		}
		double get_perimeter() const override
		{
			return sqrt((height * height) + (width * width)) + height + width;
		}
		void draw() const override
		{
			POINT point[3];
			HWND hwnd = FindWindow(NULL, L"Inheritance - Microsoft Visual Studio");
			HDC hdc = GetDC(hwnd);
			HPEN hPen = CreatePen(PS_SOLID, 5, color);
			HBRUSH hBrush = CreateSolidBrush(color);
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);
			point[0].x = get_start_x(); point[0].y = get_start_y();
			point[1].x = get_start_x(); point[1].y = get_start_y() + get_height();
			point[2].x = get_start_x() + get_width(); point[2].y = get_start_y() + get_height();
			::Polygon(hdc, point, 3);
			DeleteObject(hPen);
			DeleteObject(hBrush);
			ReleaseDC(hwnd, hdc);			
		}
		void info() const override
		{
			cout << typeid(*this).name() << endl;
			Triangle::info();
		}
	};

	class IsoscalesTriangle : public Triangle
	{
		double width;
		double height;
	public:
		IsoscalesTriangle(double width, double height, SHAPE_TAKE_PARAMETERS) : Triangle(SHAPE_GIVE_PARAMETERS)
		{
			set_width(width);
			set_height(height);
		}
		~IsoscalesTriangle() {}
		void set_width(double width)
		{
			this->width = filter_size(width);
		}
		void set_height(double height)
		{
			this->height = filter_size(height);
		}
		double get_height() const override
		{
			return height;
		}
		double get_width() const override
		{
			return width;
		}
		double get_area()const override
		{
			return (height * width) / 2;
		}
		double get_perimeter() const override
		{
			return sqrt(((width / 2) * (width / 2)) + (height * height)) * 2 + width;
		}
		void draw() const override
		{
			POINT point[3];
			HWND hwnd = FindWindow(NULL, L"Inheritance - Microsoft Visual Studio");
			HDC hdc = GetDC(hwnd);
			HPEN hPen = CreatePen(PS_SOLID, 5, color);
			HBRUSH hBrush = CreateSolidBrush(color);
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);
			point[0].x = get_start_x() + (get_width() / 2); point[0].y = get_start_y();
			point[1].x = get_start_x(); point[1].y = get_start_y() + get_height();
			point[2].x = get_start_x() + get_width(); point[2].y = get_start_y() + get_height();
			::Polygon(hdc, point, 3);
			DeleteObject(hPen);
			DeleteObject(hBrush);
			ReleaseDC(hwnd, hdc);			
		}
		void info() const override
		{
			cout << typeid(*this).name() << endl;
			Triangle::info();
		}
	};

	class EquilateralTriangle : public IsoscalesTriangle
	{		
	public:
		EquilateralTriangle(double height, SHAPE_TAKE_PARAMETERS) : IsoscalesTriangle((2 * height) / sqrt(3), height, SHAPE_GIVE_PARAMETERS){}
		~EquilateralTriangle() {}		
	};

	int Shape::count = 0;
}

void main()
{
	setlocale(LC_ALL, "");
	//Shape shape(Color::CONSOLE_RED);
	//Geometry::Square square(5, 100, 100, 5, Geometry::Color::RED);
	/*cout << "Длина стороны: " << square.get_side() << endl;
	cout << "Площадь квадрата: " << square.get_area() << endl;
	cout << "Периметр квадрата: " << square.get_perimeter() << endl;
	square.draw();*/
	//square.info();

	//Geometry::Rectangle rect(500, 300, 200, 100, 1, Geometry::Color::BLUE);			
	//rect.info();

	//Geometry::Disk disk(10000, 500, 100, 5, Geometry::Color::YELLOW);
	//disk.info();
	
	//Geometry::Triangle triangle(300, 300, 50, Geometry::Color::GREEN);
	//triangle.info();

	Geometry::RightTrinagle right(300, 200, 200, 100, 5, Geometry::Color::GREEN);
	right.info();

	Geometry::IsoscalesTriangle isoscales(300, 200, 100, 800, 5, Geometry::Color::RED);
	isoscales.info();

	Geometry::EquilateralTriangle equilateral(200, 500, 800, 5, Geometry::Color::YELLOW);
	equilateral.info();

	cout << "Количество фигур: " << right.get_count() << endl;
}