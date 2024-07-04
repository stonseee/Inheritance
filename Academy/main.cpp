#include<iostream>
#include<string>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define HUMAN_TAKE_PARAMETERS const std::string& last_name, const std::string& first_name, int age
#define HUMAN_GIVE_PARAMETERS last_name, first_name, age
#define STUDENT_TAKE_PARAMETERS const std::string& speciality, const std::string& group, double rating, double attendance
#define STUDENT_GIVE_PARAMETERS speciality, group, rating, attendance

class Human
{
private:

	std::string last_name;
	std::string first_name;
	int age;

public:

	const std::string& get_last_name()const
	{
		return last_name;
	}
	const std::string& get_first_name()const
	{
		return first_name;
	}
	int get_age()const
	{
		return age;
	}

	void set_last_name(const std::string& last_name)
	{
		this->last_name = last_name;
	}
	void set_first_name(const std::string& first_name)
	{
		this->first_name = first_name;
	}
	void set_age(int age)
	{
		this->age = age;
	}

	//constructors:
	Human(HUMAN_TAKE_PARAMETERS)
	{
		set_last_name(last_name);
		set_first_name(first_name);
		set_age(age);
		cout << "HConstructor:\t" << this << endl;
	}
	~Human()
	{
		cout << "HDestructor:\t" << this << endl;
	}

	//methods:
	void print()const
	{
		cout << last_name << " " << first_name << " " << age << endl;
	}
};

class Student: public Human
{
private:

	std::string speciality;
	std::string group;
	double rating;
	double attendance;

public:

	const std::string& get_speciality()const
	{
		return speciality;
	}
	const std::string& get_group()const
	{
		return group;
	}
	double get_rating()const
	{
		return rating;
	}
	double get_attendance()const
	{
		return attendance;
	}

	void set_speciality(const std::string& speciality)
	{
		this->speciality = speciality;
	}
	void set_group(const std::string& group)
	{
		this->group = group;
	}
	void set_rating(double rating)
	{
		this->rating = rating;
	}
	void set_attendance(double attendance)
	{
		this->attendance = attendance;
	}

	//constructors
	Student(HUMAN_TAKE_PARAMETERS, STUDENT_TAKE_PARAMETERS) :Human(HUMAN_GIVE_PARAMETERS)
	{
		set_speciality(speciality);
		set_group(group);
		set_rating(rating);
		set_attendance(attendance);
		cout << "SConstructor:\t" << this << endl;
	}
	~Student()
	{
		cout << "SDestructor:\t" << this << endl;
	}

	//methods
	void print()const
	{
		Human::print();
		cout << speciality << " " << group << " " << rating << " " << attendance << endl;
	}
};

#define TEACHER_TAKE_PARAMETERS const std::string& speciality, int experience
#define TEACHER_GIVE_PARAMETERS speciality, experience
class Teacher : public Human
{
private:

	std::string speciality;
	int experience;

public:

	const std::string& get_speciality()const
	{
		return speciality;
	}
	int get_experience()const
	{
		return experience;
	}

	void set_speciality(const std::string& speciality)
	{
		this->speciality = speciality;
	}
	void set_experience(int experience)
	{
		this->experience = experience;
	}

	//constructors
	Teacher(HUMAN_TAKE_PARAMETERS, TEACHER_TAKE_PARAMETERS) : Human(HUMAN_GIVE_PARAMETERS)
	{
		set_speciality(speciality);
		set_experience(experience);
		cout << "TConstructor:\t" << this << endl;
	}
	~Teacher()
	{
		cout << "TDestructor:\t" << this << endl;
	}

	//methods
	void print()const
	{
		Human::print();
		cout << speciality << " " << experience << " years" << endl;
	}
};

#define GRADUATE_TAKE_PARAMETERS const std::string& title, const std::string& state_of_matter, const std::string& color, double weight
#define GRADUATE_GIVE_PARAMETERS title, state_of_matter, color, weight
class Graduate : public Student
{
private:

	std::string title;
	std::string state_of_matter;
	std::string color;
	double weight;

public:

	const std::string& get_title()const
	{
		return title;
	}
	const std::string& get_state_of_matter()const
	{
		return state_of_matter;
	}
	const std::string& get_color()const
	{
		return color;
	}
	double get_weight()const
	{
		return weight;
	}

	void set_title(const std::string& title)
	{
		this->title = title;
	}
	void set_state_of_matter(const std::string& state_of_matter)
	{
		this->state_of_matter = state_of_matter;
	}
	void set_color(const std::string& color)
	{
		this->color = color;
	}
	void set_weight(int weight)
	{
		this->weight = weight;
	}

	//constructors
	Graduate(HUMAN_TAKE_PARAMETERS, STUDENT_TAKE_PARAMETERS, GRADUATE_TAKE_PARAMETERS) : Student(HUMAN_GIVE_PARAMETERS, STUDENT_GIVE_PARAMETERS)
	{
		set_title(title);
		set_state_of_matter(state_of_matter);
		set_color(color);
		set_weight(weight);
		cout << "GConstructor:\t" << this << endl;
	}
	~Graduate()
	{
		cout << "GDestructor:\t" << this << endl;
	}

	//methods
	void print()const
	{
		Student::print();
		cout << title << " " << state_of_matter << " " << color << " " << weight << " kg" << endl;
	}
};

void main()
{
	setlocale(LC_ALL, "");
	cout << "HelloAcademy" << endl;
	Human human("Richter", "Jeffrey", 40);
	human.print();

	Student student("Pinkman", "Jessie", 20, "Chemistry", "WW_220", 95, 90);
	student.print();

	Teacher teacher("White", "Walter", 50, "Chemistry", 25);
	teacher.print();

	Graduate graduate("Dick", "Cocker", 38, "Chemistry", "ZZ_300", 45, 36, "How to stop hair loss", "liquid", "yellow", 8);
	graduate.print();
}