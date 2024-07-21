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
		CONSOLE_RED = 0xCC,
		CONSOLE_GREEN = 0xAA,
		CONSOLE_BLUE = 0x99,
		CONSOLE_DEFAULT = 0x07
	};

	class Shape
	{
	protected:
		Color color;
	public:
		virtual double get_area()const = 0;
		virtual double get_perimeter()const = 0;
		virtual void draw()const = 0;
		Shape(Color color) :color(color) {}
		virtual ~Shape() {}
		virtual void info()const
		{
			cout << "Площадь фигуры: " << get_area() << endl;
			cout << "Периметр фигуры: " << get_perimeter() << endl;
			draw();
		}
	};

	class Square :public Shape
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
	};

	class Rectangle : public Shape
	{
		double width;
		double height;
	public:
		Rectangle(double width, double height, Color color) :Shape(color)
		{
			set_width(width);
			set_height(height);
		}
		~Rectangle() {}
		void set_width(double width)
		{
			this->width = width;
		}
		void set_height(double height)
		{
			this->height = height;
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
			HPEN hPen = CreatePen(PS_SOLID, 5, color);
			HBRUSH hBrush = CreateSolidBrush(color);
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);
			::Rectangle(hdc, 500, 100, 900, 300);
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

	class Disk : public Shape
	{
		double radius;		
	public:
		Disk(double radius, Color color) :Shape(color)
		{
			set_radius(radius);			
		}
		~Disk() {}
		void set_radius(double radius)
		{
			this->radius = radius;
		}		
		double get_radius()const
		{
			return radius;
		}		
		double get_area()const override
		{
			return M_PI * (radius * radius);
		}		
		double get_perimeter() const override
		{
			return 2 * M_PI * radius;
		}
		void draw() const override
		{
			HWND hwnd = FindWindow(NULL, L"Inheritance - Microsoft Visual Studio");
			HDC hdc = GetDC(hwnd);
			HPEN hPen = CreatePen(PS_SOLID, 5, color);
			HBRUSH hBrush = CreateSolidBrush(color);
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);
			::Ellipse(hdc, 500, 100, 900, 500);
			DeleteObject(hPen);
			DeleteObject(hBrush);
			ReleaseDC(hwnd, hdc);
		}
		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "Радиус круга: " << get_radius() << endl;					
			Shape::info();
		}
	};

	POINT point[3];

	class Triangle : public Shape
	{
		double width;
		double height;
	public:
		Triangle(double width, double height, Color color) :Shape(color)
		{
			set_width(width);
			set_height(height);
		}
		~Triangle() {}
		void set_width(double width)
		{
			this->width = width;
		}
		void set_height(double height)
		{
			this->height = height;
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
			return (width * height) / 2;
		}
		double get_perimeter() const override
		{
			return sqrt(((width / 2) * (width / 2)) + (height * height)) * 2 + width;
		}
		void draw() const override
		{
			HWND hwnd = FindWindow(NULL, L"Inheritance - Microsoft Visual Studio");
			HDC hdc = GetDC(hwnd);
			HPEN hPen = CreatePen(PS_SOLID, 5, color);
			HBRUSH hBrush = CreateSolidBrush(color);
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);
			point[0].x = 600; point[0].y = 400;
			point[1].x = 500; point[1].y = 450;
			point[2].x = 700; point[2].y = 450;
			::Polygon(hdc, point, 3);
			DeleteObject(hPen);
			DeleteObject(hBrush);
			ReleaseDC(hwnd, hdc);
		}
		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "Ширина треугольника: " << get_width() << endl;
			cout << "Высота треугольника: " << get_height() << endl;
			Shape::info();
		}
	};
}



void main()
{
	setlocale(LC_ALL, "");
	//Shape shape(Color::CONSOLE_RED);
	Geometry::Square square(5, Geometry::Color::CONSOLE_RED);
	/*cout << "Длина стороны: " << square.get_side() << endl;
	cout << "Площадь квадрата: " << square.get_area() << endl;
	cout << "Периметр квадрата: " << square.get_perimeter() << endl;
	square.draw();*/
	square.info();

	//Geometry::Rectangle rect(100, 50, Geometry::Color::CONSOLE_BLUE);			
	//rect.info();

	//Geometry::Disk disk(50, Geometry::Color::CONSOLE_BLUE);
	//disk.info();
	
	Geometry::Triangle triangle(100, 50, Geometry::Color::CONSOLE_BLUE);
	triangle.info();
}