#include <iostream>
#include <string>
#include <fstream>
//using namespace std;

struct NOTEBOOK
{
	std::string model; // наименование
	struct size // габаритные размеры
	{
		float x;
		float y;
		float z;
	};
	size s; //размеры
	float w; // вес
	int price; // цена
	float hdd; //объем hdd
};
NOTEBOOK* LoadFromFile(NOTEBOOK* notebooks, int& N) { //читаем из файла в структуру
	std::ifstream fin;
	fin.open("data.txt");
	fin >> N;
	notebooks = new NOTEBOOK[N](); //заносим данные в массив 
	int i = 0;
	while (!fin.eof() && i < N)
	{
		NOTEBOOK tmp;
		fin >> tmp.model;
		fin >> tmp.s.x;
		fin >> tmp.s.y;
		fin >> tmp.s.z;
		fin >> tmp.w;
		fin >> tmp.price;
		fin >> tmp.hdd;
		notebooks[i] = tmp;
		i++;
	}
	fin.close();
	return notebooks;
}
int Selection(NOTEBOOK* notebooks, const int N) { //выбор нужных ноутбуков
	int k = -1;
	for (int i = 0; i < N; i++)
	{
		if (notebooks[i].hdd > 1)
		{
			k++;
			notebooks[i].model = "~";
		}
	}
	return k;
}
void Sort(NOTEBOOK* notebooks, const int N) { //сортировка моделей по алфавиту
	NOTEBOOK temp;
	for (int i = 0; i < N - 1; i++) {
		for (int j = 0; j < N - i - 1; j++) {
			if (notebooks[j].model[0] > notebooks[j + 1].model[0]) {
				// меняем элементы местами
				temp = notebooks[j];
				notebooks[j] = notebooks[j + 1];
				notebooks[j + 1] = temp;
			}
		}
	}
}
void PrintToFile(NOTEBOOK* notebooks, const int K) { //заносим инфу о ноутбуках в бинарный файл
	std::ofstream fout;
	fout.open("output.bin", std::ios::binary);

	fout.write((char*)&K, sizeof(int));

	for (int i = 0; i < K; i++)
	{
		size_t size = notebooks[i].model.size();
		fout.write((char*)&size, sizeof(size));
		fout.write(notebooks[i].model.c_str(), size);

		fout.write((char*)&notebooks[i].s.x, sizeof(float));
		fout.write((char*)&notebooks[i].s.y, sizeof(float));
		fout.write((char*)&notebooks[i].s.z, sizeof(float));
		fout.write((char*)&notebooks[i].w, sizeof(float));
		fout.write((char*)&notebooks[i].price, sizeof(int));
		fout.write((char*)&notebooks[i].hdd, sizeof(float));

	}
	fout.close();
}

int main()
{
	NOTEBOOK* notebooks = NULL;
	int N = 0;
	notebooks = LoadFromFile(notebooks, N);
	int k = Selection(notebooks, N);
	Sort(notebooks, N);
	PrintToFile(notebooks, k);
}
