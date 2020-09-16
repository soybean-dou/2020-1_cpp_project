#include "Graduated.h"
#include <iomanip>

void print_sub_table() {
	cout << setw(10) << "과목분류" << "|";
	cout << setw(25) << "전공명" << "| ";
	cout << setw(10) << "이수학점" << "| ";
	cout << setw(10) << "성적" << "| ";
	cout << setw(10) << "영어강의" <<"| ";
	cout << setw(10) << "전공분류" << endl;
}

Subject::Subject() {
	map<string, double> grade_map;
	grade_map["A+"] = 4.5, grade_map["A0"] = 4.0, grade_map["B+"] = 3.5, grade_map["B0"] = 3, grade_map["C+"] = 2.5,
		grade_map["C0"] = 2, grade_map["D+"] = 1.5, grade_map["D0"] = 1, grade_map["F"] = 0; grade_map["P"] = 5; grade_map["NP"] = -1;

	string tmp;

	cout << "과목 분류에 [전공|공교|학기|MSC|직필|일교] 중 하나를 적어주세요." << endl;
	cout << "\t* 학기 : 공대 기본 소양(학문기초)" << endl
		<< "\t* MSC : 수학, 과학 등 학문" << endl
		<< "## 공대가 아닌 과의 학문기초도 모두 MSC 항목으로 등록 바랍니다. ## " << endl;
	cout << "과목분류 : ";
	cin >> category;
	cin.ignore(1);
	cout << "과목명 : ";
	getline(cin, name);
	cout << "이수학점 : ";
	cin >> unit;
	cout << "성적 (A+|...|D0|F / P|NP) : ";
	cin >> tmp;
	grade = grade_map[tmp];
	cout << "영어과목 ? (YES : 1 | NO : 0) >> ";
	cin >> eng_class;
}

Subject::Subject(ifstream &fin) {
	string tmp;
	fin.ignore(1);

	getline(fin, category, ',');
	getline(fin, name, ',');

	getline(fin, tmp, ',');
	unit = atoi(tmp.c_str());
	
	getline(fin, tmp, ',');
	grade = atof(tmp.c_str());
	
	getline(fin, tmp, ',');
	if (tmp == "1")
		eng_class = 1;
	else
		eng_class = 0;

}


string Subject::get_category() { return category; }

int Subject::get_unit() { return unit; }

int Subject::get_grade() { return grade; }

void Subject::print_subject() {

	map<double, string> grade_map;
	grade_map[4.5] = "A+", grade_map[4] = "A0", grade_map[3.5] = "B+", grade_map[3] = "B0", grade_map[2.5] = "C+",
		grade_map[2] = "C0", grade_map[1.5] = "D+", grade_map[1] = "D0", grade_map[0] = "F", grade_map[5] = "P", grade_map[-1] = "NP",

	cout << setw(10) << category << "|";
	cout << setw(25) << name << "| ";
	cout << setw(10) << unit << "| ";
	cout << setw(10) << grade_map[grade] << "| ";
	if (eng_class)
		cout << setw(10) << "Y" << "| ";
	else
		cout << setw(10) << " " << "| ";
	if (category == "전공")
		cout << setw(10) << major;
	cout << endl;
}

//--------------------------------------------------------------------
Major::Major() {
	bool cmd;
	cout << "[전공 세부 설정] YES :1 / NO :0 " << endl;
	cout << "일반전공? : ";
	cin >> cmd;
	if (cmd == 1)
		major_unit = 46;
	cout << "교직? : ";
	cin >> teaching;
	if (teaching)
		teach_unit = 22;
}

Major::Major(string new_add){
	
		cout << " 단과대 : ";
		cin >> college;
		cout << " 전공명 : ";
		cin >> major;
		cout << " 총 졸업학점 : ";
		cin >> all_unit;
		cout << " 전공학점 : ";
		cin >> major_unit;
		cout << "공통교양 학점 : ";
		cin >> cultural_unit;

		if (college == "공과대학") {
			cout << "MSC(수학, 과학과목) 학점 : ";
			cin >> msc_unit;
			cout << "학문기초(공대교양 학점) : ";
			cin >> basic_unit;
		}
		else {
			basic_unit = 0;
			cout << "MSC(수학, 과학과목) 학점 : ";
			cin >> msc_unit;
		}
	
	
	cout << "[전공 세부 설정] YES :1 / NO :0 " << endl;
	cout << "교직? : ";
	cin >> teaching;
	if (teaching)
		teach_unit = 22;
}

Major::Major(ifstream &fin) {
	string tmp;
	fin.ignore(1);
	getline(fin, college, ',');
	getline(fin, major, ',');
	
	getline(fin, tmp, ',');
	if (tmp == "1") {
		teaching = 1;
	}

	getline(fin, tmp, ',');
	all_unit = atoi(tmp.c_str());

	getline(fin, tmp, ',');
	major_unit = atoi(tmp.c_str());

	getline(fin, tmp, ',');
	cultural_unit = atoi(tmp.c_str());

	getline(fin, tmp, ',');
	basic_unit = atoi(tmp.c_str());

	getline(fin, tmp, ',');
	msc_unit = atoi(tmp.c_str());

	getline(fin, tmp, ',');
	teach_unit = atoi(tmp.c_str());

	if(teaching == 1)
		teach_unit = 22;
}

int Major::get_graduate_unit() {
	return all_unit;
}

//-------------------------------------------------------------------------------
Student::Student() {

	cout << "이름 : ";
	cin >> name;
	cout << "학번 : ";
	cin >> student_num;
	Major computer_major;
	maj.push_back(computer_major);
	cout << "설정이 완료되었습니다" << endl;
};

Student::Student(ifstream& fin) {
	string cmd;

	getline(fin, name, ',');
	getline(fin, student_num, ',');
	while(1) {
		fin.ignore(1);
		getline(fin, cmd, ',');
		if (cmd == "subject")
			break;
		Major m(fin);
		maj.push_back(m);
	}
	while (!fin.eof()) {
		Subject newSub(fin);
		add_subject(fin, newSub);
	}
}

void Student::add_major() {
	Major double_major("add");
	for (int i = 0; i < maj.size(); i++) {
		if (double_major == maj[i]) {
			cout << "오류 : 이미 등록한 전공입니다" << endl;
			return;
		}
	}
	cout << "설정이 완료되었습니다" << endl;
	maj.push_back(double_major);
}

void Student::add_subject() {
	Subject newSub;
	all_sub.push_back(newSub);
	my_all_unit += all_sub.back().unit;
	if (all_sub.back().eng_class)
		eng_cnt++;

	if (newSub.category == "전공") {
		if(maj.size()==1)
			maj[0].major_sub.push_back(all_sub.back());
		else {
			cout << "입력하신 과목의 전공 과를 설정해주세요 : " ;
			string cmd;
			cin >> cmd;
			newSub.major = cmd;
			all_sub.back() = newSub;
			for (int i = 0; i < maj.size(); i++) {
				if (maj[i].major == cmd) {
					maj[i].major_sub.push_back(all_sub.back());
					my_major_unit[i] += all_sub.back().unit;
					break;
				}
			}
		}
	}
	else if (newSub.category == "공교") {
		sub_category[0].push_back(all_sub.back());
		my_unit_arr[0] += all_sub.back().unit;
	}
	else if (newSub.category == "학기") {
		sub_category[1].push_back(all_sub.back());
		my_unit_arr[1] += all_sub.back().unit;
	}
	else if (newSub.category == "MSC") {
		sub_category[2].push_back(all_sub.back());
		my_unit_arr[2] += all_sub.back().unit;
	}
	else if (newSub.category == "직필") {
		sub_category[3].push_back(all_sub.back());
		my_unit_arr[3] += all_sub.back().unit;
	}
	else{
		sub_category[4].push_back(all_sub.back());
		my_unit_arr[4] += all_sub.back().unit;
	}
	cout << "과목 추가가 완료되었습니다." << endl << endl;

}

void Student::add_subject(ifstream& fin, Subject newSub){
	string cmd;
	all_sub.push_back(newSub);
	my_all_unit += all_sub.back().unit;
	if (all_sub.back().eng_class)
		eng_cnt++;

	if (newSub.category == "전공") {
		if (maj.size() == 1)
			maj[0].major_sub.push_back(all_sub.back());
		else {
			getline(fin, cmd, ',');
			newSub.major = cmd;
			all_sub.back() = newSub;
			for (int i = 0; i < maj.size(); i++) {
				if (maj[i].major == cmd) {
					maj[i].major_sub.push_back(all_sub.back());
					my_major_unit[i] += all_sub.back().unit;
					break;
				}
			}
		}
	}
	else if (newSub.category == "공교") {
		sub_category[0].push_back(all_sub.back());
		my_unit_arr[0] += all_sub.back().unit;
	}
	else if (newSub.category == "학기") {
		sub_category[1].push_back(all_sub.back());
		my_unit_arr[1] += all_sub.back().unit;
	}
	else if (newSub.category == "MSC") {
		sub_category[2].push_back(all_sub.back());
		my_unit_arr[2] += all_sub.back().unit;
	}
	else if (newSub.category == "직필") {
		sub_category[3].push_back(all_sub.back());
		my_unit_arr[3] += all_sub.back().unit;
	}
	else if (newSub.category == "일교"){
		sub_category[4].push_back(all_sub.back());
		my_unit_arr[4] += all_sub.back().unit;
	}
	else {
		all_sub.pop_back();
		return;
	}
}

void Student::print_personal_info() {
	cout << name << " | " << student_num << endl;
	for (int i = 0; i < maj.size(); i++) {
		cout << "전공 " << i + 1 << " : " << maj[i].college << " " << maj[i].major << endl;
		cout << "교직 이수 " << (maj[i].teaching?"YES":"NO") << endl << endl;
	}
}

void Student::print_subject_info() {
	string cmd;
	map<string, int> category_map;
	category_map["전체"] = 0, category_map["전공"] = 1, category_map["공교"] = 2, category_map["학기"] = 3,
	category_map["MSC"] = 4, category_map["직필"] = 5, category_map["일교"] = 6;


	cout << "출력하실 과목 분류를 선택하십시오. [전체|전공|공교|학기|MSC|직필|일교] " << endl;
	cout << "과목 분류 : ";
	cin >> cmd;
	
	switch (category_map[cmd])
	{
	case 0:
		print_sub_table();
		for (int i = 0; i < all_sub.size(); i++)
			all_sub[i].print_subject();
		break;

	case 1:
		cout << "출력할 전공을 선택하세요 : ";
		cin >> cmd;
		print_sub_table();
		for (int i = 0; i < maj.size(); i++) {
			if (maj[i].major == cmd) {
				for (int j = 0; j < maj[i].major_sub.size(); j++) {
					maj[i].major_sub.at(j).print_subject();
				}
				break;
			}
		}
		break;

	case 2: //공교
		print_sub_table();
		for (int i = 0; i < sub_category[0].size(); i++)
			sub_category[0].at(i).print_subject();
		break;

	case 3: //학기
		print_sub_table();
		for (int i = 0; i < sub_category[1].size(); i++)
			sub_category[1].at(i).print_subject();
		break;

	case 4: //MSC
		print_sub_table();
		for (int i = 0; i < sub_category[2].size(); i++)
			sub_category[2].at(i).print_subject();
		break;

	case 5: //직필
		print_sub_table();
		for (int i = 0; i < sub_category[3].size(); i++)
			sub_category[3].at(i).print_subject();
		break;

	case 6: //직필
		print_sub_table();
		for (int i = 0; i < sub_category[4].size(); i++)
			sub_category[4].at(i).print_subject();
		break;

	default:
		break;
	}	
}

void Student::print_grade() {
	double sum_grade=0;
	int pf_cnt=0;

	for (int i = 0; i < all_sub.size(); i++) {
		if (all_sub[i].grade != 5 && all_sub[i].grade != -1)
			sum_grade += all_sub[i].grade * all_sub[i].unit;
		else
			pf_cnt += all_sub[i].unit;
	}
	cout << "전체 성적 평균 : " << sum_grade / (double)(my_all_unit-pf_cnt) << endl;

	for (int i = 0; i < maj.size(); i++) {
		sum_grade = 0;
		pf_cnt = 0;
		for (int j = 0; j < maj[i].major_sub.size(); j++) {
			if (maj[i].major_sub[j].grade != 5 && maj[i].major_sub[j].grade != -1)
				sum_grade += maj[i].major_sub[j].grade * maj[i].major_sub[j].unit;
			else
				pf_cnt += maj[i].major_sub[j].unit;
		}
		cout << "전공 " << i+1 << " 성적 평균 : " << sum_grade / (double)(my_major_unit[i]-pf_cnt) << endl;
	}
}

void Student::save_file() {
	ofstream fout;
	fout.open("graduate_data.csv");
	if (!fout.is_open()) {
		cout << "파일을 저장할 수 없습니다! " << endl;
		return;
	}
	fout << name << "," << student_num << "," << endl;

	for (int i = 0; i < maj.size(); i++) {
		fout << "major infomation," << endl;
		fout << maj[i].college << "," << maj[i].major << "," << maj[i].teaching << "," << endl;
		fout << maj[i].all_unit << "," << maj[i].major_unit << "," << maj[i].cultural_unit << ","
			<< maj[i].basic_unit << "," << maj[i].msc_unit << "," << maj[i].teach_unit << "," << endl;
	}
	fout << "subject,";
	for (int i = 0; i < all_sub.size(); i++) {
		fout << endl;
		fout << all_sub[i].category << "," << all_sub[i].name << ","
			<< all_sub[i].unit << "," << all_sub[i].grade << "," << all_sub[i].eng_class << ",";
		if (all_sub[i].category == "전공")
			fout << all_sub[i].major << ",";
	}
	fout << EOF;
	fout.close();
	cout << "저장 완료" << endl;
}

bool Student::can_graduate() {
	bool flag = true;
	for (int i = 0; i < maj.size(); i++) {

		cout << "전공 " << i+1 << "졸업학점 :::" << endl;
		cout << "전체 학점 : " << maj[i].all_unit << " | " << my_all_unit << endl;
		cout << "전공 학점 : " << maj[i].major_unit << " | " << my_major_unit[i] << endl;
		cout << "공교 학점 : " << maj[i].cultural_unit << " | " << my_unit_arr[0] << endl;
		cout << "학기 학점 : " << maj[i].basic_unit << " | " << my_unit_arr[1] << endl;
		cout << "MSC 학점 : " << maj[i].msc_unit << " | " << my_unit_arr[2] << endl;
		cout << "교직 학점 : " << maj[i].teach_unit << " | " << my_unit_arr[3] << endl << endl;

		if (eng_cnt <= 2+2*maj.size())
			flag = false;
		if (maj[i].all_unit > my_all_unit)
			flag = false;
		if (maj[i].major_unit > my_major_unit[i])
			flag = false;
		if (maj[i].cultural_unit > my_unit_arr[0])
			flag = false;
		if (maj[i].basic_unit > my_unit_arr[1])
			flag = false;
		if (maj[i].msc_unit > my_unit_arr[2])
			flag = false;
		if (maj[i].teach_unit > my_unit_arr[3])
			flag = false;
	}

	return flag;
}

