
#include <iostream>
using namespace std;
#include <ctime>
#include <queue>

const int RANDOM_GET_NUBER = 10;
const int RANDOM_GET_LENGTH_MASS = 10;

/*Проверка на повторяемость длин массива*/
bool checkLengthMass(int massLength[], int countMassLength)
{
	if (countMassLength == 0) return true; // первый раз нет повторений
	else {

		for (int i = 0; i < countMassLength; i++)
		{
			if (massLength[i] == massLength[countMassLength])
				return false;
		}
	}
	return true;
}

/*Получение длины массива*/
int getLengthMass()
{
	return (1 + rand() % RANDOM_GET_LENGTH_MASS);
}

/*Создание массивов*/
void createMass(int **massPoint, int *massLength, int number)
{
	int countMass = number; // количество массивов
	int lengthMass = 0;
	bool resultCheckLengthMass = false; // флаг для проверки повторяемости длин массивов
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
			massPoint[i] = new int[lengthMass]; // колличество элементов в массиве

			for (int count = 0; count < lengthMass; count++) // заполняем массив элементами
			{
				massPoint[i][count] = (1 + rand() % 10);
			}
		}
	}
}

/*Перестановка в сериях по убыванию*/
void mix_desc(int p1, int p1e, int p2, int p2e, int* mas, int* mt) // по убыванию
{ // p1 - начало серии, в дальнейшем будет указывать на min число в серии
	//p2 - номер позиции числа, которого нарушило последовательность в серии
	int pos = p1;
	while ((p1 <= p1e) && (p2 <= p2e))
	{		//сравнием значение нарушившего последовательность элемента с другими значениями элементов в серии
		if (mas[p1] >= mas[p2])  //  если значение нарушившего последовательность элемента меньше, чем значение элемента из серии
		{
			if (p1>p1e) break;
			mt[pos] = mas[p1]; // записываем значение элемента из серии
			pos++;
			p1++;
		}
		else
		{// когда значение нарушившего последовательность элемента больше, чем значение элемента из серии
			if (p2>p2e) break; // проверка на выход за границы серии
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

/*Сортровка по убыванию*/
void sort_desc(int* mas, int masLength)
{
	int* mt1 = mas;
	int* mt2 = new int[masLength];
	int* tmp; /// временный массив

	queue<int> points; // очередь для собирания точек, где нарушена сортировка
	points.push(0); // начало очереди

	for (int i = 0; i<masLength - 1; i++)//собираем точки, где сортировка нарушена, в очередь

	if (mas[i] < mas[i + 1]) {
		points.push(i + 1);
	}
	points.push(masLength);//конец очереди
	do{
		int a = points.front();
		points.pop();
		if (a == masLength){
			points.push(masLength);//помечаем окончание очередного круга слияния
			tmp = mt1;//после окончания круга меняем указатели местами чтобы не копировать массивы полностью
			mt1 = mt2;
			mt2 = tmp;
			continue;
		}

		int b = points.front();
		points.pop();
		if (b == masLength){
			if (a == 0) break;//a==0 b==n признако конца сортировки
			mix_desc(a, masLength - 1, masLength + 2, masLength + 1, mt1, mt2);//n+2 и n+1 - чтобы второй блок (которого нет) не задействовался в слиянии
			points.push(a);
			points.push(masLength);//помечаем окончание очередного круга слияния
			tmp = mt1;//после окончания круга меняем указатели местами чтобы не копировать массивы полностью
			mt1 = mt2;
			mt2 = tmp;
			continue;
		}
		mix_desc(a, b - 1, b, points.front() - 1, mt1, mt2);
		points.push(a);//помещаем в очередь начало нового одногодного участка
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

/*Перестановка в сериях по возрастанию*/

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

/*Сортровка по возрастанию*/
void sort_asc(int* mas, int masLength)
{
	int* mt1 = mas;
	int* mt2 = new int[masLength];
	int* tmp; /// временный массив

	queue<int> points; // очередь для собирания точек, где нарушена сортировка
	points.push(0); // начало очереди

	for (int i = 0; i<masLength - 1; i++)//собираем точки, где сортировка нарушена в очередь
	if (mas[i]>mas[i + 1]) points.push(i + 1);
	points.push(masLength);//маркер окончания очередного прохода
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
			if (a == 0) break;//a==0 b==n признако конца сортировки*/
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



