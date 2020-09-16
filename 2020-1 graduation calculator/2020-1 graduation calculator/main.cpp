
#include "Graduated.h"
using namespace std;

void print_help() {
	cout << "Command" << endl
		<< "+M : 전공 추가 " << endl
		<< "+S : 과목 추가 " << endl
		<< "PM : 전공 정보 출력 " << endl
		<< "PS : 과목 정보 출력 " << endl
		<< "PG : 성적 정보 출력" << endl
		<< "G : 졸업 가능 여부 계산 " << endl
		<< "S : 정보 저장 " << endl
		<< "H : 도움말 출력" << endl
		<< "Q : 끝내기 " << endl << endl;
}


int main() {
	string cmd; ifstream fin;

	map< string, int > cmd_map;
	cmd_map["+M"] = 1; cmd_map["+S"] = 2; cmd_map["PM"] = 3; cmd_map["PS"] = 4; cmd_map["PG"] = 5; 
	cmd_map["G"] = 6; cmd_map["S"] = 7; cmd_map["H"] = 8; cmd_map["Q"] = 9;

	cout << "- - - - - - - - 졸업학점 계산기 - - - - - - - - -" << endl;
	

	Student *s;

	fin.open("graduate_data.csv");
	if (!fin.is_open()) {
		cout << "전공 정보를 설정합니다(컴퓨터공학과 기준)" << endl;
		s = new Student;
	}
	else {
		s = new Student(fin);
	}
	print_help();

	do {
		cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - " << endl;
		cout << "명령어를 입력하시오 >> ";
		cin >> cmd;
		for (int i = 0; i < cmd.size(); i++){
			cmd[i] = toupper(cmd[i]);
		}

		cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - " << endl;

		switch (cmd_map[cmd])
		{
		case 1: //add major
			s->add_major();
			break;

		case 2: //add subjcet
			s->add_subject(); 
			break;

		case 3: //print major info
			s->print_personal_info();
			break;

		case 4: //print subject info
			s->print_subject_info();
			break;

		case 5: //print grade
			s->print_grade();
			break;

		case 6: //can greaduate 
			if (s->can_graduate())
				cout << " >>> 졸업 가능" << endl;
			else
				cout << " >>> 졸업 불가" << endl;
			break;

		case 7: //save file
			s->save_file();
			break;

		case 8: //print help
			print_help();
			break;

		case 9: //quit
			cout << "프로그램을 종료합니다." << endl << endl;
			break;

		default:
			cout << "잘못된 명령어입니다" << endl << endl;
			break;
		}
	} while (cmd_map[cmd] != 9);
}