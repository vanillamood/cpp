
#include "stdafx.h"
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include "Weapon.h"

using namespace std;

Weapon::Weapon() {			// ������
}

void Weapon::Describe() {

	ifstream read;				// ����������� ���� ��ü ����
	read.open("weapon.txt");		// ���� �б�
		
	char str[sizeof(read)] = { '\0' };		// ���� ������ ��ü ũ�� ��ŭ�� char �迭 ����

	int i=0;			// ��Ʈ�� ���ø��� ������ �ű�� ���� ����

	if (read.good()) {		// ������ ������
		while (!read.eof()) {	// ���� ���� ����������
			read.getline(str, sizeof(read));	// ���ڿ��� �о�� str�� ����

			string str1 = str;			// ��Ʈ�� ���ø��� ���� char�迭�� string���� ��ȯ

			istringstream iss(str1);		// ��ȯ�� string str1�� iss ����

			do
			{
				i++;			// ������� ���� ���� ����ϱ����� 
				string sub;		// ���ø��� �Ϻκ��� ��Ʈ���� �����ϱ����� sub ��Ʈ��
				iss >> sub;		// �߶� �κ��� �־���
				switch (i){		// ������ ã�� ����Ѵ�
					case 1: cout << "Name = " << sub << endl;break;
					case 2: cout << "Description = " << sub << endl;break;
					case 3: cout << "Weight = " << sub << endl;break;
					case 4: cout << "Value = " << sub << endl;break;
					case 5: cout << "Damage = " << sub << "\n" << endl;break;
					default: break;
				}
			} while (iss);
		}
	}

	read.close();			// ���� �б� ��ħ

}