#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<fstream>	
#include<string.h>
#include"Student.h"
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define GRADUATE_TAKE_PARAMETERS const std::string& subject
#define GRADUATE_GIVE_PARAMETERS subject
class Graduate : public Student
{
private:

	std::string subject;

public:

	const std::string& get_subject()const;

	void set_subject(const std::string& subject);
	std::ifstream& read(std::ifstream& ifs) override;

	//constructors
	Graduate(HUMAN_TAKE_PARAMETERS, STUDENT_TAKE_PARAMETERS, GRADUATE_TAKE_PARAMETERS);
	Graduate(const Student& student, const std::string& subject);
	~Graduate();

	//methods
	std::ostream& print(std::ostream& os)const override;	
	std::ofstream& print(std::ofstream& os)const override;	
};