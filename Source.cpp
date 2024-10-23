#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <sstream>
#include <cstdlib>

using namespace std;

typedef struct Afisha //����� �����������
{
	string monday;
	string tuesday;
	string wednesday;
	string thursday;
	string friday;
};

struct kino //������ ���� �����������
{
	string name;
	string address;
	string number;
	int halls;
	int capasity;
	int price;
	Afisha afisha;
	kino* next = NULL;
	kino* pred = NULL;
};

int getfile(string fname, int* count); //������� ����� ������ �� �����
void print(); //������� ������ ���� �����������
int newcinema(int* count); //������� ���������� ������ ����������
void menu(); //������� ����
void films(); //������� ������������� ������� �� �����
int delitecinema(int a, int* count); //������� �������� ������ ����������
void printcinema(kino* p, int i); //������� ������ ������ ����������
void printafisha(); //������� ������ ����� ���� �����������
void search(int a, string word); //������� ������ ����������
void printoneafisha(kino* p, int i); //������� ������ ����� ������ ����������
void sortelem(int a, int* count); //������� ���������� ��������
void newfilm(); //������� ���������� ������ ������
void delfilm(); //������� �������� ������
kino* head = NULL; //��������� ������� ������
kino* last = NULL; //��������� ������� ������
kino* pv = NULL; //��������� �� ������� ������
int a;
string f[10] = { " " };

int main()
{
	setlocale(LC_ALL, "rus");
	system("chcp 1251");
	int count = 0;
	int* ptrcount = &count;
	count = getfile("kino.txt", ptrcount); //���-�� ����� � ����
	films();
	menu();
	while (a)
	{
		int d;
		string r;
		switch (a) {
		case 1:
			print();
			menu();
			break;
		case 2:
			cout << "���� ������ ���������� ����� �� ��������, ������� 1, ���� �� ������ ������� 2: ";
			cin >> d;
			if (d == 1) {
				cout << "\n������� ������� ��������: ";
				cin >> r;
				search(d, r);
			}
			if (d == 2) {
				cout << "\n������� ������� ����� � ������� '�.?': ";
				cin >> r;
				search(d, r);
			}
			menu();
			break;
		case 3:
			exit(0);
		case 4:
			cout << "������� ����� ������, ������� ������ �������: ";
			cin >> d;
			count = delitecinema(d, ptrcount);
			print();
			menu();
			break;
		case 5:
			count = newcinema(ptrcount);
			menu();
			break;
		case 6:
			printafisha();
			menu();
			break;
		case 7:
			cout << "������� �������� �� �������� �� ������ �������� ����������:\n";
			cout << "1.�������� �� ��������\n2.����� �� ��������\n3.���� �� ��������\n4.���� �� �����������\n5.����������� �� ��������\n6.����������� �� �����������\n";
			cin >> d;
			sortelem(d, ptrcount);
			menu();
			break;
		case 8:
			cout << "1.�������� �����\n2.������ �����";
			cin >> d;
			switch (d) {
			case 1:
				newfilm();
				break;
			case 2:
				delfilm();
				break;
			}
			menu();
			break;
		default:
			cout << "������� �������� 1-8 �������� ����!\n";
			menu();
			break;

		}
	}
}

int getfile(string fname, int* count) {
	ifstream fin(fname);
	if (!fin.is_open()) {
		cout << "�� ���������� ������� ���� !\n";
		return 0;
	}
	if (fin.peek() == EOF) {
		return 1;
	}
	short k;
	string a;
	while (!fin.eof()) {
		pv = new kino;
		getline(fin, pv->name, ' ');
		getline(fin, pv->address, ' ');
		getline(fin, pv->number, ' ');
		getline(fin, a, ' ');
		istringstream(a) >> k; //���� ����� �� �����
		pv->halls = k;
		getline(fin, a, ' ');
		istringstream(a) >> k;
		pv->capasity = k;
		getline(fin, a, ' ');
		istringstream(a) >> k;
		pv->price = k;
		getline(fin, a, '\n');
		pv->next = NULL;
		pv->pred = NULL;
		if (last) {
			last->next = pv;
			pv->pred = last;
		}
		if (!head)head = pv;
		last = pv;
		(*count)++;
	}
	fin.close();
	return *count;
}

void films() {
	ifstream dp("afisha.txt");
	if (!dp.is_open()) {// ���� ���� �� ������
		cout << "�� ���������� ������� ���� !\n";
		exit(0);
	}
	if (dp.peek() == EOF) {
		exit(1);
	}
	if (dp)
	{
		for (int i = 0; !dp.eof(); i++)
		{
			getline(dp, f[i], '\n');
		}
	}
	dp.close();
	pv = head;
	while (pv) { //��������� ������������� ������� �� �����������
		pv->afisha.monday = f[rand() % 10];
		pv->afisha.tuesday = f[rand() % 10];
		pv->afisha.wednesday = f[rand() % 10];
		pv->afisha.thursday = f[rand() % 10];
		pv->afisha.friday = f[rand() % 10];
		pv = pv->next;
	}
}

void print() {
	int i = 1;
	if (head) {
		pv = head;
		cout << "�  " << left << setw(16) << "��������" << left << setw(20) << "�����" << left << setw(20) << "����� ��������"
			<< left << setw(20) << "���������� �����" << left << setw(20) << "�����������" << left << setw(20) << "������� ���� �� �����\n";
		while (pv) {
			cout << left << setw(4) << i << left << setw(16);
			cout << pv->name << left << setw(20);
			cout << pv->address << ' ' << left << setw(20);
			cout << pv->number << ' ' << left << setw(20);
			cout << pv->halls << ' ' << left << setw(20);
			cout << pv->capasity << ' ' << left << setw(20);
			cout << pv->price << '\n';
			pv = pv->next;
			i++;
		}
		cout << "\n";
	}
}

void printafisha() {
	int i = 1;
	if (head) {
		pv = head;
		cout << "�  " << left << setw(16) << "�����������" << left << setw(22) << "�������" << left << setw(22) << "�����"
			<< left << setw(20) << "�������" << right << setw(2) << "�������\n";
		while (pv) {
			cout << left << setw(4) << i << left << setw(16);
			cout << pv->afisha.monday << left << setw(20);
			cout << pv->afisha.tuesday << ' ' << left << setw(20);
			cout << pv->afisha.wednesday << ' ' << left << setw(20);
			cout << pv->afisha.thursday << ' ' << left << setw(20);
			cout << pv->afisha.friday << '\n';
			pv = pv->next;
			i++;
		}
		cout << "\n";
	}
};

void printcinema(kino* p, int i) {
	cout << "�  " << left << setw(16) << "��������" << left << setw(20) << "�����" << left << setw(20) << "����� ��������"
		<< left << setw(20) << "���������� �����" << left << setw(20) << "�����������" << left << setw(20) << "������� ���� �� �����\n";
	pv = p;
	cout << left << setw(4) << i << left << setw(16);
	cout << pv->name << left << setw(20);
	cout << pv->address << ' ' << left << setw(20);
	cout << pv->number << ' ' << left << setw(20);
	cout << pv->halls << ' ' << left << setw(20);
	cout << pv->capasity << ' ' << left << setw(20);
	cout << pv->price << '\n';
}

void printoneafisha(kino* p, int i) {
	cout << left << setw(16) << "�����������" << left << setw(22) << "�������" << left << setw(22) << "�����"
		<< left << setw(20) << "�������" << right << setw(2) << "�������\n";
	pv = p;
	cout << left << setw(20);
	cout << pv->afisha.monday << left << setw(20);
	cout << pv->afisha.tuesday << ' ' << left << setw(20);
	cout << pv->afisha.wednesday << ' ' << left << setw(20);
	cout << pv->afisha.thursday << ' ' << left << setw(20);
	cout << pv->afisha.friday << '\n';
}

void search(int a, string word)
{
	cout << word << " ";
	bool flag = false;
	int i = 1, k;
	pv = head;
	switch (a) {
	case 1:
		while (pv) {
			if (pv->name == word) {
				printcinema(pv, i);
				cout << "���� ������ ���������� ����� ����� ���������� ������� 1: ";
				cin >> k;
				if (k == 1) {
					printoneafisha(pv, i);
				};
				flag = true;
			}
			i++;
			pv = pv->next;
		}
		break;
	case 2:
		while (pv) {
			if (pv->address == word) {
				printcinema(pv, i);
				cout << "���� ������ ���������� ����� ����� ���������� ������� 1: ";
				cin >> k;
				if (k == 1) {
					printoneafisha(pv, i);
				};
				flag = true;
			}
			i++;
			pv = pv->next;
		}
		break;
	}
	if (flag == false)
		cout << "������ �������� � ���� �� ����������\n";
}

int newcinema(int* count)
{
	kino* newelem = NULL;
	newelem = new kino;
	string a; short k;
	cout << "������� �������� ����������: \n";
	cin >> a;
	newelem->name = a;
	cout << "������� ����� ����������: \n";
	cin >> a;
	newelem->address = a;
	cout << "������� ����� ����������: \n";
	cin >> a;
	newelem->number = a;
	cout << "������� ���������� ����� ����������:  \n";
	cin >> k;
	newelem->halls = k;
	cout << "������� ����������� ����������: \n";
	cin >> k;
	newelem->capasity = k;
	cout << "������� ������� ���� �� �����: \n";
	cin >> k;
	newelem->price = k;
	newelem->afisha.monday = f[rand() % 10];
	newelem->afisha.tuesday = f[rand() % 10];
	newelem->afisha.wednesday = f[rand() % 10];
	newelem->afisha.thursday = f[rand() % 10];
	newelem->afisha.friday = f[rand() % 10];
	newelem->next = NULL;
	newelem->pred = NULL;
	if (!head) { //���������� � ������
		head = newelem;
		last = newelem;
	}
	else {
		newelem->pred = last;
		last->next = newelem;
		last = newelem;
	}
	return *(count)+1;
};

bool comp1(kino a, kino b) { return a.name < b.name; }
bool comp2(kino a, kino b) { return a.address < b.address; }
bool comp3(kino a, kino b) { return a.price > b.price; }
bool comp4(kino a, kino b) { return a.price < b.price; }
bool comp5(kino a, kino b) { return a.capasity > b.capasity; }
bool comp6(kino a, kino b) { return a.capasity < b.capasity; }

void sortelem(int a, int* count)
{
	kino* mas = new kino[*count];
	pv = head;
	for (int i = 0; i < *count; i++) { //���������� ������ � ������ ��� ���������� ������ ������� ����������
		mas[i].name = pv->name;
		mas[i].address = pv->address;
		mas[i].number = pv->number;
		mas[i].halls = pv->halls;
		mas[i].capasity = pv->capasity;
		mas[i].price = pv->price;
		mas[i].afisha.monday = pv->afisha.monday;
		mas[i].afisha.tuesday = pv->afisha.tuesday;
		mas[i].afisha.wednesday = pv->afisha.wednesday;
		mas[i].afisha.thursday = pv->afisha.thursday;
		mas[i].afisha.thursday = pv->afisha.thursday;
		pv = pv->next;
	}
	switch (a) {
	case 1: sort(mas, mas + *count, comp1); break;
	case 2: sort(mas, mas + *count, comp2); break;
	case 3: sort(mas, mas + *count, comp3); break;
	case 4: sort(mas, mas + *count, comp4); break;
	case 5: sort(mas, mas + *count, comp5); break;
	case 6: sort(mas, mas + *count, comp6); break;
	}
	cout << "�  " << left << setw(16) << "��������" << left << setw(20) << "�����" << left << setw(20) << "����� ��������"
		<< left << setw(20) << "���������� �����" << left << setw(20) << "�����������" << left << setw(20) << "������� ���� �� �����\n";
	for (int i = 0; i < *count; i++) {
		cout << left << setw(4) << i + 1 << left << setw(16);
		cout << mas[i].name << left << setw(20);
		cout << mas[i].address << left << setw(20);
		cout << mas[i].number << left << setw(20);
		cout << mas[i].halls << left << setw(20);
		cout << mas[i].capasity << left << setw(20);
		cout << mas[i].price << '\n';
	}
	delete[] mas;
}

int delitecinema(int a, int* count)
{
	if (a == 1) { //���� ������� ������
		pv = head;
		pv->next->pred = NULL;
		head = pv->next;
		pv->next = NULL;
		delete(pv);
		return *(count)-1;
	}
	if (a == *count) { //���� ������� ���������
		pv = last;
		pv->pred->next = NULL;
		last = pv->pred;
		pv->pred = NULL;
		delete(pv);
		return *(count)-1;
	}
	else {
		pv = head;
		for (int i = 0; i < a - 1; i++) {
			pv = pv->next;
		}
		pv->pred->next = pv->next;
		pv->next->pred = pv->pred;
		pv->pred = NULL;
		pv->next = NULL;
		delete(pv);
		return *(count)-1;
	}
}

void delfilm()
{
	string s;
	cout << "������� �������� ������ ��� �������� \n";
	cin >> s;
	pv = head;
	while (pv)
	{
		for (int i = 0; i < 5; i++) {
			size_t found = pv->afisha.monday.find(s);
			if (found != string::npos) {
				pv->afisha.monday.erase(found, s.length());
			}
			found = pv->afisha.tuesday.find(s);
			if (found != string::npos) {
				pv->afisha.tuesday.erase(found, s.length());
			}
			found = pv->afisha.wednesday.find(s);
			if (found != string::npos) {
				pv->afisha.wednesday.erase(found, s.length());
			}
			found = pv->afisha.thursday.find(s);
			if (found != string::npos) {
				pv->afisha.thursday.erase(found, s.length());
			}
			found = pv->afisha.friday.find(s);
			if (found != string::npos) {
				pv->afisha.friday.erase(found, s.length());
			}
		}
		pv = pv->next;
	}
}

void newfilm()
{
	string s; short a, n;
	cout << "������� �������� ������ ������: (��� ��������)\n";
	cin >> s;
	cout << "���� �� ������ �������� ��� � ����� ������ ����������, ������� 1, ���� �������� ����� ����, ������� 2: \n";
	cin >> a;
	switch (a) {
	case 1:
		cout << "�������� ����� ����������: \n";
		cin >> n;
		pv = head;
		for (int i = 0; i < n - 1; i++) {
			pv = pv->next;
		}
		cout << "�������� ���� �����������(1)-�������(5). ������� �����: ";
		cin >> n;
		switch (n) {
		case 1:
			pv->afisha.monday = s;
			break;
		case 2:
			pv->afisha.tuesday = s;
			break;
		case 3:
			pv->afisha.wednesday = s;
			break;
		case 4:
			pv->afisha.thursday = s;
			break;
		case 5:
			pv->afisha.friday = s;
			break;
		}
		break;
	case 2:
		cout << "�������� ���� �����������(1)-�������(5). ������� �����: ";
		cin >> n;
		switch (n) {
		case 1:
			pv = head;
			while (pv) {
				pv->afisha.monday = s;
				pv = pv->next;
			}
			break;
		case 2:
			pv = head;
			while (pv) {
				pv->afisha.tuesday = s;
				pv = pv->next;
			}
			break;
			pv = head;
			while (pv) {
				pv->afisha.wednesday = s;
				pv = pv->next;
			}
			break;
		case 4:
			pv = head;
			while (pv) {
				pv->afisha.thursday = s;
				pv = pv->next;
			}
			break;
		case 5:
			pv = head;
			while (pv) {
				pv->afisha.friday = s;
				pv = pv->next;
			}
			break;
		}
		break;
	default:
		cout << "������� ���������� ��������!\n";
		menu();
		break;
	}
}

void menu()
{
	cout << "��������, ��� �� ������ �������: ";
	cout << "\n1. ����� �� �����";
	cout << "\n2. ����� ���������...";
	cout << "\n3. ����� �� ���������";
	cout << "\n4. �������� ���������� �� ����";
	cout << "\n5. ���������� ���������� � ����";
	cout << "\n6. ������� ����� ���� �����������";
	cout << "\n7. ����������";
	cout << "\n8. ��������� �����\n";
	cin >> a;
}
