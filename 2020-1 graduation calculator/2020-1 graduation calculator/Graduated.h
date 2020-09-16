#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
using namespace std;

class Subject {

	string category;
	string name;
	int unit;
	double grade;
	bool eng_class;
	string major;

public:
	Subject();
	Subject(ifstream &fin);
	string get_category();
	int get_unit();
	int get_grade();
	void print_subject();

	friend class Student;
};

class Major {
	string college = "공과대학";
	string major = "컴퓨터공학전공";

	int all_unit = 140, major_unit = 84, cultural_unit = 16, msc_unit = 21, basic_unit = 9;

	int teach_unit = 0;
	bool teaching = 0;
	
	vector<Subject> major_sub;

public:
	Major();
	Major(string new_add);
	Major(ifstream &fin);

	int get_graduate_unit();
	//void teaching_on();
	bool operator==(Major& m) {
		if (college == m.college && major == m.major)
			return 1;
		else
			return 0;
	}

	friend class Student;
};

class Student {
	string name, student_num;

	vector<Major> maj;
	vector<Subject> all_sub;

	vector<vector<Subject>> sub_category = vector<vector<Subject>>(6);

	int my_major_unit[5] = { 0 };
	int my_all_unit = 0;
	int my_unit_arr[6] = { 0 };
	int eng_cnt;

public:
	Student();
	Student(ifstream& fin);
	void add_major();
	void add_subject();
	void add_subject(ifstream &fin, Subject newSub);
	void print_personal_info();
	void print_subject_info();
	void print_grade();
	void save_file();
	bool can_graduate();

};
