
#include <iostream>
using namespace std;
#include <ctime>
#include <queue>

const int RANDOM_GET_NUBER = 10;
const int RANDOM_GET_LENGTH_MASS = 10;

/*�������� �� ������������� ���� �������*/
bool checkLengthMass(int massLength[], int countMassLength)
{
	if (countMassLength == 0) return true; // ������ ��� ��� ����������
	else {

		for (int i = 0; i < countMassLength; i++)
		{
			if (massLength[i] == massLength[countMassLength])
				return false;
		}
	}
	return true;
}

/*��������� ����� �������*/
int getLengthMass()
{
	return (1 + rand() % RANDOM_GET_LENGTH_MASS);
}

/*�������� ��������*/
void createMass(int **massPoint, int *massLength, int number)
{
	int countMass = number; // ���������� ��������
	int lengthMass = 0;
	bool resultCheckLengthMass = false; // ���� ��� �������� ������������� ���� ��������
	for (int i = 0; i < countMass; i++)
	{

		if (RANDOM_GET_NUBER > RANDOM_GET_LENGTH_MASS){
			cout << "MUST BE RANDOM_GET_LENGTH_MASS >= RANDOM_GET_NUBER";
			exit(0);
		}
		else {

			while (resultCheckLengthMass == false)
			{
				massLength[i] = getLengthMass();
				resultCheckLengthMass = checkLengthMass(massLength, i);
				lengthMass = massLength[i];
			}

			resultCheckLengthMass = false;
			massPoint[i] = new int[lengthMass]; // ����������� ��������� � �������

			for (int count = 0; count < lengthMass; count++) // ��������� ������ ����������
			{
				massPoint[i][count] = (1 + rand() % 10);
			}
		}
	}
}

/*������������ � ������ �� ��������*/
void mix_desc(int p1, int p1e, int p2, int p2e, int* mas, int* mt) // �� ��������
{ // p1 - ������ �����, � ���������� ����� ��������� �� min ����� � �����
	//p2 - ����� ������� �����, �������� �������� ������������������ � �����
	int pos = p1;
	while ((p1 <= p1e) && (p2 <= p2e))
	{		//�������� �������� ����������� ������������������ �������� � ������� ���������� ��������� � �����
		if (mas[p1] >= mas[p2])  //  ���� �������� ����������� ������������������ �������� ������, ��� �������� �������� �� �����
		{
			if (p1>p1e) break;
			mt[pos] = mas[p1]; // ���������� �������� �������� �� �����
			pos++;
			p1++;
		}
		else
		{// ����� �������� ����������� ������������������ �������� ������, ��� �������� �������� �� �����
			if (p2>p2e) break; // �������� �� ����� �� ������� �����
			mt[pos] = mas[p2];
			pos++;
			p2++;
		}
	}
	while (p1 <= p1e)
	{
		mt[pos] = mas[p1];
		pos++;
		p1++;
	}
	while (p2 <= p2e)
	{
		mt[pos] = mas[p2];
		pos += 1;
		p2 += 1;
	}
}

/*��������� �� ��������*/
void sort_desc(int* mas, int masLength)
{
	int* mt1 = mas;
	int* mt2 = new int[masLength];
	int* tmp; /// ��������� ������

	queue<int> points; // ������� ��� ��������� �����, ��� �������� ����������
	points.push(0); // ������ �������

	for (int i = 0; i<masLength - 1; i++)//�������� �����, ��� ���������� ��������, � �������

	if (mas[i] < mas[i + 1]) {
		points.push(i + 1);
	}
	points.push(masLength);//����� �������
	do{
		int a = points.front();
		points.pop();
		if (a == masLength){
			points.push(masLength);//�������� ��������� ���������� ����� �������
			tmp = mt1;//����� ��������� ����� ������ ��������� ������� ����� �� ���������� ������� ���������
			mt1 = mt2;
			mt2 = tmp;
			continue;
		}

		int b = points.front();
		points.pop();
		if (b == masLength){
			if (a == 0) break;//a==0 b==n �������� ����� ����������
			mix_desc(a, masLength - 1, masLength + 2, masLength + 1, mt1, mt2);//n+2 � n+1 - ����� ������ ���� (�������� ���) �� �������������� � �������
			points.push(a);
			points.push(masLength);//�������� ��������� ���������� ����� �������
			tmp = mt1;//����� ��������� ����� ������ ��������� ������� ����� �� ���������� ������� ���������
			mt1 = mt2;
			mt2 = tmp;
			continue;
		}
		mix_desc(a, b - 1, b, points.front() - 1, mt1, mt2);
		points.push(a);//�������� � ������� ������ ������ ����������� �������
	} while (true);
	if (mt2 == mas)
	{
		for (int i = 0; i < masLength; i++){
			mt2[i] = mt1[i];
		}
		delete mt1;
	}
	else delete mt2;
}

/*������������ � ������ �� �����������*/

void mix_asc(int p1, int p1e, int p2, int p2e, int* mas, int* mt)
{
	int pos = p1;
	while ((p1 <= p1e) && (p2 <= p2e))
	{
		if (mas[p1] <= mas[p2])
		{
			if (p1>p1e) break;
			mt[pos] = mas[p1];
			pos++;
			p1++;
		}
		else
		{
			if (p2>p2e) break;
			mt[pos] = mas[p2];
			pos++;
			p2++;
		}
	}
	while (p1 <= p1e)
	{
		mt[pos] = mas[p1];
		pos++;
		p1++;
	}
	while (p2 <= p2e)
	{
		mt[pos] = mas[p2];
		pos += 1;
		p2 += 1;
	}
}

/*��������� �� �����������*/
void sort_asc(int* mas, int masLength)
{
	int* mt1 = mas;
	int* mt2 = new int[masLength];
	int* tmp; /// ��������� ������

	queue<int> points; // ������� ��� ��������� �����, ��� �������� ����������
	points.push(0); // ������ �������

	for (int i = 0; i<masLength - 1; i++)//�������� �����, ��� ���������� �������� � �������
	if (mas[i]>mas[i + 1]) points.push(i + 1);
	points.push(masLength);//������ ��������� ���������� �������
	do{
		int a = points.front();
		points.pop();
		if (a == masLength){
			points.push(masLength);
			tmp = mt1;
			mt1 = mt2;
			mt2 = tmp;
			continue;
		}
		int b = points.front();
		points.pop();
		if (b == masLength){
			if (a == 0) break;//a==0 b==n �������� ����� ����������*/
			mix_asc(a, masLength - 1, masLength + 2, masLength + 1, mt1, mt2);
			points.push(a);
			points.push(masLength);
			tmp = mt1;
			mt1 = mt2;
			mt2 = tmp;
			continue;
		}

		mix_asc(a, b - 1, b, points.front() - 1, mt1, mt2);
		points.push(a);
	} while (true);

	if (mt2 == mas)
	{
		for (int i = 0; i<masLength; i++) mt2[i] = mt1[i];
		delete mt1;
	}
	else delete mt2;
}




int** getNumber(int number){
	int **massPoint = new int*[number];
	int *massLength = new int[number];

	cout << "Number = " << number << endl;
	createMass(massPoint, massLength, number);


	for (int i = 0; i < number; i++)
	{
		cout << endl;
		cout << "Mass " << i + 1 << endl;
		for (int j = 0; j < massLength[i]; j++)
			cout << massPoint[i][j] << "  ";
	}
	for (int i = 0; i < number; i++)
	{
		if (i % 2 == 0)     sort_desc(massPoint[i], massLength[i]);
		else sort_asc(massPoint[i], massLength[i]);
	}


	for (int i = 0; i < number; i++)
	{
		cout << endl;
		cout << "SortMass " << i + 1 << endl;
		for (int j = 0; j < massLength[i]; j++)
			cout << massPoint[i][j] << "  ";
	}
	cout << endl;



	delete massLength;

	return massPoint;

}

void main()
{
	srand(time(0));
	int number = 1 + rand() % RANDOM_GET_NUBER;
	int** sortMass = getNumber(number);

	for (int i = 0; i < number; i++)
	{

		delete[] sortMass[i];
	}

	system("pause");
}



