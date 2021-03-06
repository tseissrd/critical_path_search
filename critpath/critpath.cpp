#include <pch.h> //подключение библиотек
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
using namespace std; //далее используется стандартное пространство имен
class graph //объявление класса graph
{
public: //установка прав доступа к методам класса (в данном случае значения методов можно изменить извне)
	int vertices; //int - целочисленный тип данных, vertices - количество вершин графа (событий)
	vector<vector<double>> time; //двумерный массив (вектор, состоящий из векторов) значений типа double - чисел с плавающей точкой (двойной точности)
	vector<vector<bool>> ind; //...содержащих time - вес дуг графа (работ), bool - логический тип данных (значения 0 или 1), ind - матрица смежности
};
class path
{
public:
	vector<int> vertice; //массив, содержащий номера вершин на критическом пути в порядке от истока к стоку
};
void help() //void - пустой тип данных (функция help не возвращает никаких значений)
{
	cout << "planning task\nj - add a new job\nd - display the setup\nc - get the critical path(s)\n\nh - display this message\ne - exit\n";
}
void pause() //функция, ожидающая ввод перед завершением программы
{
	string nothing;
	cout << "Press ENTER to exit";
	getchar();
	getline(cin, nothing);
}
int main()
{
	int i, j, k, l, sta, end; //i-l - счетчики, sta - переменная, хранящая номер вершины-истока графа, end - вершины-стока
	vector<double> tp, tn; //ранние и поздние времена завершения работ
	vector<vector<double>> r; //резервы времен
	bool check, xcheck, graphset(0); //различные проверки по ходу вычислений
	vector<vector<int>> leads; //массив возможных путей из вершины (в случае если критических путей два+)
	string input; //строка для выбора действия
	graph data, resetd; //заданный граф и пустой граф (для обнуления заданного)
	vector<path> paths; //массив вариантов критических путей
	help(); //вызов функции help, скобки пустые потому что вызов происходит без параметров
	cout << "----------------------\nTWO CRITICAL PATHS MAX\nDON'T USE ZERO LABELED VERTICE\n\n";
resetv: //пример маркера для перехода из одной части кода в другую
	data = resetd;
	cout << "number of vertices:";
	cin >> data.vertices;
	++data.vertices; //увеличение значения метода vertices из класса data на 1
	data.time.reserve(data.vertices); //резервирование памяти для расширения вектора (массива) data.time до размера data.vertices
	data.time.resize(data.vertices); //расширение вектора
	data.ind.reserve(data.vertices);
	data.ind.resize(data.vertices);
	tp.reserve(data.vertices);
	tp.resize(data.vertices);
	tn.reserve(data.vertices);
	tn.resize(data.vertices);
	r.reserve(data.vertices);
	r.resize(data.vertices);
	leads.reserve(data.vertices);
	leads.resize(data.vertices);
	for (i = 0; i < data.vertices; ++i) //цикл с параметром i
	{
		data.time[i].reserve(data.vertices);
		data.time[i].resize(data.vertices);
		data.ind[i].reserve(data.vertices);
		data.ind[i].resize(data.vertices);
		r[i].reserve(data.vertices);
		r[i].resize(data.vertices);
		tp[i] = 0;
		for (j = 0; j < data.vertices; ++j)
		{
			data.time[i][j] = 0;
			data.ind[i][j] = 0;
		}
	}
	newopt:
	cin >> input;
	if (input == "j") //оператор ветвления (условие если-то)
	{
		cout << "start:";
		cin >> sta;
		cout << "end:";
		cin >> end;
		cout << "time:";
		cin >> data.time[sta][end];
		data.ind[sta][end] = 1;
		graphset = 1;
	}
	//два предустановленных графа, в первом 6 вершин, критический путь = 17, во втором вершин 8, критический путь = 22
	if (input == "1")
	{
		data.time[1][2] = 3;
		data.ind[1][2] = 1;
		data.time[2][5] = 7;
		data.ind[2][5] = 1;
		data.time[5][4] = 5;
		data.ind[5][4] = 1;
		data.time[1][3] = 4;
		data.ind[1][3] = 1;
		data.time[1][4] = 2;
		data.ind[1][4] = 1;
		data.time[3][6] = 8;
		data.ind[3][6] = 1;
		data.time[2][6] = 1;
		data.ind[2][6] = 1;
		data.time[3][5] = 6;
		data.ind[3][5] = 1;
		data.time[5][6] = 4;
		data.ind[5][6] = 1;
		data.time[6][4] = 3;
		data.ind[6][4] = 1;
		graphset = 1;
	}
	if (input == "2")
	{
		data.time[1][2] = 6;
		data.ind[1][2] = 1;
		data.time[1][3] = 1;
		data.ind[1][3] = 1;
		data.time[2][3] = 0;
		data.ind[2][3] = 1;
		data.time[3][6] = 9;
		data.ind[3][6] = 1;
		data.time[3][5] = 4;
		data.ind[3][5] = 1;
		data.time[3][4] = 2;
		data.ind[3][4] = 1;
		data.time[6][8] = 7;
		data.ind[6][8] = 1;
		data.time[5][6] = 1;
		data.ind[5][6] = 1;
		data.time[5][8] = 8;
		data.ind[5][8] = 1;
		data.time[5][7] = 1;
		data.ind[5][7] = 1;
		data.time[4][7] = 5;
		data.ind[4][7] = 1;
		data.time[7][8] = 2;
		data.ind[7][8] = 1;
		graphset = 1;
	}
	if (input == "d")
	{
		for (i = 0; i < data.vertices; ++i)
			for (j = 0; j < data.vertices; ++j)
				if (data.ind[i][j])
					cout << i << "->" << j << " | " << data.time[i][j] << endl; //endl - перенос вывода на новую строку
	}
	if (input == "c")
	{
		if (!graphset) //"!graphset" = условие выполнено, если значение graphset ложно
			goto newopt; //переход по ссылке newopt
		sta = 0;
		end = 0;
		//поиск стока графа
		xcheck = 0;
		for (i = 0; i < data.vertices; ++i)
		{
			check = 1;
			for (j = 0; j < data.vertices; ++j)
			{
				if (data.ind[i][j] || i==0) //"||" = "или"
					check = 0;
			}
			if (check)
			{
				if (xcheck)
				{
					cout << "graph is not a net\n";
					goto newopt;
				}
				end = i;
				xcheck = 1;
			}
		}
		//поиск истока графа
		xcheck = 0;
		for (i = 0; i < data.vertices; ++i)
		{
			check = 1;
			for (j = 0; j < data.vertices; ++j)
			{
				if (data.ind[j][i] || i == 0)
					check = 0;
			}
			if (check)
			{
				if (xcheck)
				{
					cout << "graph is not a net\n";
					goto newopt;
				}
				sta = i;
				xcheck = 1;
			}
		}
		//проверка что нет циклов (работ, начинающихся и заканчивающихся в одной вершине)
		for (i = 0; i < data.vertices; ++i)
			if (data.ind[i][i])
			{
				cout << "graph is not a net\n";
				goto newopt;
			}
		//вычисления tp[i]
		for(k=0;k<data.vertices;++k)
			for (i = 0; i < data.vertices; ++i)
			{
				for (j = 0; j < data.vertices; ++j)
					if (data.ind[i][j])
						if (tp[i] + data.time[i][j] > tp[j])
						{
							tp[j] = tp[i] + data.time[i][j];
						}
			}
		tn[end] = tp[end];
		//вычисления tn[i]
		for (i = 0; i < data.vertices; ++i)
			tn[i] = tn[end];
		for (k = 0; k < data.vertices; ++k)
			for (i = data.vertices - 1; i >= 0; --i)
			{
				for (j = 0; j < data.vertices; ++j)
					if (data.ind[i][j])
						if (tn[j] - data.time[i][j] < tn[i])
						{
							tn[i] = tn[j] - data.time[i][j];
						}
			}
		for (i = 0; i < data.vertices; ++i)
			cout << "tp[" << i << "] = " << tp[i] << endl;
		for (i = 0; i < data.vertices; ++i)
			cout << "tn[" << i << "] = " << tn[i] << endl;
		//вычисления r[i][j]
		for (i = 0; i < data.vertices; ++i)
			for (j = 0; j < data.vertices; ++j)
				if (data.ind[i][j])
				{
					r[i][j] = tn[j] - tp[i] - data.time[i][j];
					cout << "r" << i << j << " = " << r[i][j] << endl;
				}
		paths.reserve(1);
		paths.resize(1);
		//подсчет количества критических путей
		for (i = 0; i < data.vertices; ++i)
		{
			l = 0;
			k = 0;
			for (j = 0; j < data.vertices; ++j)
				if (data.ind[i][j] && r[i][j] == 0)
				{
					leads[i].reserve(leads[i].size() + 1);
					leads[i].resize(leads[i].size() + 1);
					leads[i][k] = j;
					++k;
				}
			if (k > 1)
			{
				paths.reserve(paths.size()*k);
				paths.resize(paths.size()*k);
			}
			for (l = 0; l < paths.size(); ++l)
			{
				paths[l].vertice.reserve(data.vertices);
				paths[l].vertice.resize(data.vertices);
			}
		}
		cout << "critical paths #:" << paths.size() << endl;
		//составление критического пути (одного) в случае, когда их не два
		if (paths.size() != 2)
		{
			paths[0].vertice[0] = sta;
			for (i = 0;;)
				for (j = 0; j < data.vertices; ++j)
					if (data.ind[paths[0].vertice[i]][j] && r[paths[0].vertice[i]][j] == 0)
					{
						paths[0].vertice[i + 1] = j;
						++i;
						if (j == end)
							goto done;
					}
		}
		//составление одного из критических путей если их два
		paths[0].vertice[0] = sta;
		for (i = 0;;)
			for (j = 0; j < data.vertices; ++j)
				if (data.ind[paths[0].vertice[i]][j] && r[paths[0].vertice[i]][j] == 0)
				{
					paths[0].vertice[i + 1] = j;
					++i;
					if (j == end)
						goto finalize;
				}
	finalize:
		//копирование составленного пути и замена вершины, в которой происходит разветвление, на второй вариант
		if (paths.size()==2)
		{
			paths[1] = paths[0];
			k = 0;
			for (i = 0; i < data.vertices; ++i)
				if(leads[i].size()==2)
					for (j = 0; j < 2; ++j)
					{
						paths[j].vertice[i] = leads[i][k];
						++k;
					}
			goto done;
		}
	}
	if (input == "r")
		goto resetv;
	if (input == "h")
		help();
	if (input == "e")
		goto exit;
	goto newopt;
done:
	//вывод критических путей и времени
	for (i = 0; i < paths.size(); ++i)
	{
		check = 1;
		cout << i + 1 << ": " << sta;
		for (j = 1;check; ++j)
		{
			cout << "->" << paths[i].vertice[j];
			if (paths[i].vertice[j] == end)
				check = 0;
		}
	newp:
		cout << endl;
		if (paths.size() > 2)
			goto ct;
	}
	ct:
	cout << "critical time:" << tp[end] << endl;
	goto newopt;
exit:
	pause();
	return 0; //возвращение главной функцией - main значения 0 (=завершение работы программы)
}