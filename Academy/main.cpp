#include<iostream>
#include<string>
#include<fstream>
#include"Graduate.h"
#include"Human.h"
#include"Student.h"
#include"Teacher.h"
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define delimiter "\n----------------------------------------\n"

//void Print(Human* group[], const int n)
//{
//	cout << delimiter << endl;
//	for (int i = 0; i < n; i++)
//	{
//		//group[i]->print();
//		cout << *group[i] << endl;
//		cout << delimiter << endl;
//	}
//}
//void Clear(Human* group[], const int n)
//{
//	for (int i = 0; i < n; i++)
//	{
//		delete group[i];
//	}
//}

//#define INHERITANCE_1
//#define INHERITANCE_2
#define WRITE_TO_FILE
#define READ_FROM_FILE

void main()
{
	setlocale(LC_ALL, "");

#ifdef INHERITANCE_1
	cout << "HelloAcademy" << endl;
	Human human("Richter", "Jeffrey", 40);
	human.print();

	cout << delimiter << endl;

	Student student("Pinkman", "Jessie", 20, "Chemistry", "WW_220", 95, 90);
	student.print();

	cout << delimiter << endl;

	Teacher teacher("White", "Walter", 50, "Chemistry", 25);
	teacher.print();

	cout << delimiter << endl;

	Graduate graduate("Schrader", "Hank", 38, "Chemistry", "OBN", 45, 36, "How to stop hair loss");
	graduate.print();

	cout << delimiter << endl;
#endif // NHERITANCE_1

#ifdef INHERITANCE_2
	Human human("Vercetty", "Tommy", 30);
	human.print();

	cout << delimiter << endl;

	Student student(human, "Theft", "Vice", 95, 98);
	student.print();

	cout << delimiter << endl;

	Graduate graduate(student, "How to make money");
	graduate.print();

	cout << delimiter << endl;
#endif // INHERITANCE_2

#ifdef WRITE_TO_FILE
	Human* group[] =
	{
		new Student("Pinkman", "Jessie", 20, "Chemistry", "WW_220", 95, 90),
		new Teacher("White", "Walter", 50, "Chemistry", 25),
		new Graduate("Schrader", "Hank", 38, "Chemistry", "DEA", 45, 36, "How to stop hair loss"),
		new Student("Vercetty", "Tommy", 30, "Theft", "Vice", 95, 98),
		new Teacher("Diaz", "Ricardo", 50, "Weapors distribution", 20)
	};

	std::ofstream fout;
	fout.open("File.txt", std::ios_base::app);

	fout << Print(group, sizeof(group) / sizeof(group[0])) << endl;

	fout.close();

	Print(group, sizeof(group) / sizeof(group[0]));
	Clear(group, sizeof(group) / sizeof(group[0]));
#endif // WRITE_TO_FILE

	system("notepad File.txt");

	
}