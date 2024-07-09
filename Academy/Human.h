#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define delimiter "\n----------------------------------------\n"

#define HUMAN_TAKE_PARAMETERS const std::string& last_name, const std::string& first_name, int age
#define HUMAN_GIVE_PARAMETERS last_name, first_name, age

class Human;

std::ostream& operator<<(std::ostream& os, const Human& obj);
void Print(Human* group[], const int n);
void Clear(Human* group[], const int n);


class Human
{
private:

	std::string last_name;
	std::string first_name;
	int age;

public:

	const std::string& get_last_name()const;
	const std::string& get_first_name()const;
	int get_age()const;

	void set_last_name(const std::string& last_name);
	void set_first_name(const std::string& first_name);
	void set_age(int age);

	//constructors:
	Human(HUMAN_TAKE_PARAMETERS);
	virtual ~Human();

	//methods:
	virtual std::ostream& print(std::ostream& os)const;
	virtual char* add_class(char* Type);
};
