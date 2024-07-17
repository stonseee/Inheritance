#include"Teacher.h"

const std::string& Teacher::get_speciality()const
{
	return speciality;
}
int Teacher::get_experience()const
{
	return experience;
}

void Teacher::set_speciality(const std::string& speciality)
{
	this->speciality = speciality;
}
void Teacher::set_experience(int experience)
{
	this->experience = experience;
}

//constructors
Teacher::Teacher(HUMAN_TAKE_PARAMETERS, TEACHER_TAKE_PARAMETERS) : Human(HUMAN_GIVE_PARAMETERS)
{
	set_speciality(speciality);
	set_experience(experience);
	cout << "TConstructor:\t" << this << endl;
}
Teacher::~Teacher()
{
	cout << "TDestructor:\t" << this << endl;
}

//methods
std::ostream& Teacher::print(std::ostream& os)const
{
	return Human::print(os) << " " << speciality << " " << experience << " years";	
}

std::ofstream& Teacher::print(std::ofstream& ofs)const
{
	Human::print(ofs);
	ofs.width(SPECIALITY_WIDTH);
	ofs << speciality;
	ofs.width(EXPERIENCE_WIDTH);
	ofs << experience;
	return ofs;
}

