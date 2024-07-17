#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<fstream>	
#include<string.h>
#include"Human.h"
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define TEACHER_TAKE_PARAMETERS const std::string& speciality, int experience
#define TEACHER_GIVE_PARAMETERS speciality, experience

class Teacher : public Human
{
private:

	static const int SPECIALITY_WIDTH = 25;
	static const int EXPERIENCE_WIDTH = 5;
	std::string speciality;
	int experience;

public:

	const std::string& get_speciality()const;
	int get_experience()const;

	void set_speciality(const std::string& speciality);
	void set_experience(int experience);

	//constructors
	Teacher(HUMAN_TAKE_PARAMETERS, TEACHER_TAKE_PARAMETERS);
	~Teacher();

	//methods
	std::ostream& print(std::ostream& os)const override;
	std::ofstream& print(std::ofstream& ofs)const override;
	
};