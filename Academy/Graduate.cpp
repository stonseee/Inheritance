#include"Graduate.h"

const std::string& Graduate::get_subject()const
{
	return subject;
}

void Graduate::set_subject(const std::string& subject)
{
	this->subject = subject;
}
std::ifstream& Graduate::read(std::ifstream& ifs)
{
	Student::read(ifs);
	std::getline(ifs, subject);
	return ifs;
}

//constructors
Graduate::Graduate(HUMAN_TAKE_PARAMETERS, STUDENT_TAKE_PARAMETERS, GRADUATE_TAKE_PARAMETERS)
	: Student(HUMAN_GIVE_PARAMETERS, STUDENT_GIVE_PARAMETERS)
{
	set_subject(subject);
	cout << "GConstructor:\t" << this << endl;
}
Graduate::Graduate(const Student& student, const std::string& subject) : Student(student)
{
	set_subject(subject);
	cout << "GConstructor:\t" << this << endl;
}
Graduate::~Graduate()
{
	cout << "GDestructor:\t" << this << endl;
}

//methods
std::ostream& Graduate::print(std::ostream& os)const
{
	return Student::print(os) << " " << subject;
	//return Student::print(os) << endl << subject;
}
std::ofstream& Graduate::print(std::ofstream& os)const
{
	Student::print(os);	
	//os << speciality;
	return os;
}
