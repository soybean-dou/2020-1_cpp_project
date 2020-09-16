
#include "Graduated.h"
using namespace std;

void print_help() {
	cout << "Command" << endl
		<< "+M : ���� �߰� " << endl
		<< "+S : ���� �߰� " << endl
		<< "PM : ���� ���� ��� " << endl
		<< "PS : ���� ���� ��� " << endl
		<< "PG : ���� ���� ���" << endl
		<< "G : ���� ���� ���� ��� " << endl
		<< "S : ���� ���� " << endl
		<< "H : ���� ���" << endl
		<< "Q : ������ " << endl << endl;
}


int main() {
	string cmd; ifstream fin;

	map< string, int > cmd_map;
	cmd_map["+M"] = 1; cmd_map["+S"] = 2; cmd_map["PM"] = 3; cmd_map["PS"] = 4; cmd_map["PG"] = 5; 
	cmd_map["G"] = 6; cmd_map["S"] = 7; cmd_map["H"] = 8; cmd_map["Q"] = 9;

	cout << "- - - - - - - - �������� ���� - - - - - - - - -" << endl;
	

	Student *s;

	fin.open("graduate_data.csv");
	if (!fin.is_open()) {
		cout << "���� ������ �����մϴ�(��ǻ�Ͱ��а� ����)" << endl;
		s = new Student;
	}
	else {
		s = new Student(fin);
	}
	print_help();

	do {
		cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - " << endl;
		cout << "��ɾ �Է��Ͻÿ� >> ";
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
				cout << " >>> ���� ����" << endl;
			else
				cout << " >>> ���� �Ұ�" << endl;
			break;

		case 7: //save file
			s->save_file();
			break;

		case 8: //print help
			print_help();
			break;

		case 9: //quit
			cout << "���α׷��� �����մϴ�." << endl << endl;
			break;

		default:
			cout << "�߸��� ��ɾ��Դϴ�" << endl << endl;
			break;
		}
	} while (cmd_map[cmd] != 9);
}