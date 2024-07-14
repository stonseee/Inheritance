#define _CRT_SECURE_NO_WARNINGS
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
//#define WRITE_TO_FILE
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
	//human.print();

	cout << delimiter << endl;

	Student student(human, "Theft", "Vice", 95, 98);
	//student.print();

	cout << delimiter << endl;

	Graduate graduate(student, "How to make money");
	//graduate.print();

	cout << delimiter << endl;
#endif // INHERITANCE_2

#ifdef WRITE_TO_FILE

	char* Type = new char;
	Human* group[] =
	{
		new Student("Pinkman", "Jessie", 20, "Chemistry", "WW_220", 95, 90),
		new Teacher("White", "Walter", 50, "Chemistry", 25),
		new Graduate("Schrader", "Hank", 38, "Chemistry", "DEA", 45, 36, "How to stop hair loss"),
		new Student("Vercetty", "Tommy", 30, "Theft", "Vice", 95, 98),
		new Teacher("Diaz", "Ricardo", 50, "Weapors distribution", 20)

		/*new Human("Pinkman", "Jessie", 20),
		new Teacher("White", "Walter", 50, "Chemistry", 25),
		new Graduate("Schrader", "Hank", 38, "Chemistry", "DEA", 45, 36, "How to stop hair loss"),
		new Student("Vercetty", "Tommy", 30, "Theft", "Vice", 95, 98),
		new Human("Diaz", "Ricardo", 50)*/
	};

	std::ofstream fout;
	fout.open("File.txt", std::ios_base::app);

	for (int i = 0; i < (group, sizeof(group) / sizeof(group[0])); ++i)
	{
		fout << group[i]->add_class(Type) << *group[i] << endl;
	}	

	fout.close();

	Print(group, sizeof(group) / sizeof(group[0]));
	Clear(group, sizeof(group) / sizeof(group[0]));
#endif // WRITE_TO_FILE

#ifdef READ_FROM_FILE
	//system("notepad File.txt");

	int n = 5;

	Human* group[] =
	{
		new Human("", "", 0),
		new Human("", "", 0),		
		new Human("", "", 0),
		new Human("", "", 0),
		new Human("", "", 0)		
	};	

	//Human* group = new Human[5];

	std::ifstream fin("File.txt"); 
	if (fin.is_open())
	{
		char type[32]{};
		int ctr = 0;
		int nameCtr = -1;	
		char speciality[64]{};
		char subject[64]{};
		int experience = 0;		
		char gr[64]{};
		int rating = 0;
		int attendance = 0;
		while (!fin.eof()) 
		{
			const int SIZE = 1024000;
			char buffer[SIZE]{};			

			if ((!strcmp(type, "Human ") && ctr == 4) || 
				(!strcmp(type, "Teacher ") && ctr == 6) ||
				(!strcmp(type, "Student ") && ctr == 8) ||
				(!strcmp(type, "Graduate ") && ctr == 9))ctr = 0;

			if (ctr == 0)
			{	
				fin.getline(type, SIZE);
				cout << "type === " << type << endl;
				++nameCtr;
			}
			else
			{
				fin.getline(buffer, SIZE);
				//cout << buffer << endl;
				//cout << "buffer === "  << buffer << endl;
			}						

			if (((!strcmp(type, "Human ")) ||
				(!strcmp(type, "Teacher ")) ||
				(!strcmp(type, "Student ")) ||
				(!strcmp(type, "Graduate "))) && ctr == 1)
			{
				group[nameCtr]->set_last_name(buffer);
			}
			if (((!strcmp(type, "Human ")) ||
				(!strcmp(type, "Teacher ")) ||
				(!strcmp(type, "Student ")) ||
				(!strcmp(type, "Graduate "))) && ctr == 2)
			{
				group[nameCtr]->set_first_name(buffer);
			}
			if (((!strcmp(type, "Human ")) ||
				(!strcmp(type, "Teacher ")) ||
				(!strcmp(type, "Student ")) ||
				(!strcmp(type, "Graduate "))) && ctr == 3)
			{
				group[nameCtr]->set_age(atoi(buffer));
			}
			if (((!strcmp(type, "Teacher ")) || (!strcmp(type, "Student ")) || (!strcmp(type, "Graduate "))) && ctr == 4)
			{
				strcpy(speciality, buffer);				
			}
			if ((!strcmp(type, "Teacher ")) && ctr == 5)
			{
				experience = atoi(buffer);
			}
			if (((!strcmp(type, "Student ")) || (!strcmp(type, "Graduate "))) && ctr == 5)
			{
				strcpy(gr, buffer);
			}
			if (((!strcmp(type, "Student ")) || (!strcmp(type, "Graduate "))) && ctr == 6)
			{
				rating = atoi(buffer);				
			}
			if (((!strcmp(type, "Student ")) || (!strcmp(type, "Graduate "))) && ctr == 7)
			{
				attendance = atoi(buffer);
			}
			if ((!strcmp(type, "Graduate ")) && ctr == 8)
			{
				strcpy(subject, buffer);
			}			
			if (!strcmp(type, "Teacher ") && ctr == 5)
			{
				group[nameCtr] = new Teacher(group[nameCtr]->get_last_name(), group[nameCtr]->get_first_name(), group[nameCtr]->get_age(), speciality, experience);
			}
			if (!strcmp(type, "Student ") && ctr == 7)
			{
				group[nameCtr] = new Student(group[nameCtr]->get_last_name(), group[nameCtr]->get_first_name(), group[nameCtr]->get_age(), speciality, gr, rating, attendance);
			}
			if (!strcmp(type, "Graduate ") && ctr == 8)
			{
				group[nameCtr] = new Graduate(group[nameCtr]->get_last_name(), group[nameCtr]->get_first_name(), group[nameCtr]->get_age(), speciality, gr, rating, attendance, subject);
			}

			++ctr;
		}
		fin.close();
	}
	else
	{
		std::cerr << "Error: File not found" << endl;
	}

	Print(group, sizeof(group) / sizeof(group[0]));
	Clear(group, sizeof(group) / sizeof(group[0]));
#endif // READ_FROM_FILE

}