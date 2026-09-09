
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath> 
#include <limits>
#include "videoteka.h"
using namespace std;

double getNum(const string& check, double MinValues, double MaxValues)
{
	double values;
	while (cout << check, !(cin >> values) || values < MinValues || values > MaxValues) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Неправильный ввод. Введите число от " << MinValues << " до " << MaxValues << endl;
	
	}
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	return values;
}

int getInt(const string& check, int MinValues, int MaxValues)
{
	return (int)getNum(check, (double)MinValues, (double)MaxValues);
}

double SumPositive(const double arr[], int size)
{
	double Sum = 0;
	for (int i = 0; i < size; i++) {
		if (arr[i] > 0) {
			Sum += arr[i];
		}
	}
	return Sum;
}

void GenArray(double arr[], int size)
{
	static bool call = false;
	if (!call) {
		srand((unsigned)time(NULL));
		call = true;
	}
	
	const double MinValues = -100.0;
	const double MaxValues = 100.0;

	for (int i = 0; i < size; i++) {
		double random = (double)rand() / RAND_MAX;
		arr[i] = MinValues + random * (MaxValues - MinValues);

	}
}

void printArray(const double arr[], int size, const string& name)
{
	cout << name << "[" << size << "] = [";
	for (int i = 0; i < size; i++) {
		cout << arr[i];
		if (i < size - 1) cout << "; ";
	}
	cout << "]" << endl;
}

double RootK(double X, int K, int N)
{
    if (N == 0) {
        return 1.0;
    }

    // вычисляем Y(n-1)
    double Y_n1 = RootK(X, K, N - 1);

    // Вычисляем Y(n-1)^(K-1)
    double Yn_v_pow = pow(Y_n1, K - 1);

    // Формула: Yn = Y(n-1) - (Y(n-1) - X / Y(n-1)^(K-1)) / K
    double Yn = Y_n1 - (Y_n1 - X / Yn_v_pow) / K;

    return Yn;
}

void printResults(double X, int K, int N_values[], int size)
{
    cout << "\nРезультаты по X = " << X << ", K = " << K << ":\n";

    double exact = pow(X, 1.0 / K);

    for (int i = 0; i < size; i++) {
        int N = N_values[i];
        double result = RootK(X, K, N);
        cout << "N = " << N << " --> " << result << endl;
    }

    cout << "Приближенное значение: " << exact << endl;
}


int main()
{
  setlocale(LC_ALL, "Russian");
  
  cout << "Задание 1 " << endl;
  int M = getInt("Введите размер масива А(М) от 1 до 100: ", 1, 100);
  int N_B = getInt("Введите размер масива B(N) от 1 до 100: ", 1, 100);
  int L = getInt("Введите размер масива C(L) от 1 до 100: ", 1, 100);

  double* A = new double[M];
  double* B = new double[N_B];
  double* C = new double[L];

  GenArray(A, M);
  GenArray(B, N_B);
  GenArray(C, L);

  cout << "\nСгенерированные массивы\n";
  printArray(A, M, "Массив A");
  printArray(B, N_B, "Массив B");
  printArray(C, L, "Массив C");

  double S = SumPositive(A, M);
  double T = SumPositive(B, N_B);
  double K_s = SumPositive(C, L);
  double result = (S + T + K_s) / 2.0;

  cout << "S = " << S << endl;
  cout << "T = " << T << endl;
  cout << "K = " << K_s << endl;
  cout << "M = (S + T + K) / 2 = " << result << endl;

  delete[] A;
  delete[] B;
  delete[] C;
  
  cout << "Задание 2 " << endl;
  double X = getNum("Введите число X > 0: ", 0.1, 1000.0);
  int K_p = getInt("Введите степень корня K > 1: ", 2, 10);

  
  int N_values[] = { 1, 2, 3, 4, 5, 6 };
  int size = 6;
  printResults(X, K_p, N_values, size);

  cout << "Задание 3 " << endl;
  Film* videoteka = new Film[N];
  bool dataLoaded = false;
  int choice;

  do {
      Menu();
      choice = getIntInput("", 1, 9);

      switch (choice) {
      case 1:
          cout << "\nГенерация случайных данных...\n";
          generateRandomFilms(videoteka, N);
          dataLoaded = true;
          AllFilmsInfoInput(videoteka, N);
          break;

      case 2:
          ManualFilmInput(videoteka, N);
          cout << "Данные успешно введены.\n";
          AllFilmsInfoInput(videoteka, N);
          break;

      case 3:
          if (!dataLoaded) {
              cout << "\nОшибка! Сначала необходимо заполнить видеотеку. Выберите пункт 1 или 2.\n";
          }
          else {
              AllFilmsInfoInput(videoteka, N);
          }
          break;

      case 4:
          if (!dataLoaded) {
              cout << "\nОшибка! Сначала необходимо заполнить видеотеку. Выберите пункт 1 или 2.\n";
          }
          else {
              cout << "\nВведите фамилию режиссера для поиска: ";
              string director = getStringInput("");
              OutputFilmsByDirector(videoteka, N, director);
          }
          break;

      case 5:
          if (!dataLoaded) {
              cout << "\nОшибка! Сначала необходимо заполнить видеотеку. Выберите пункт 1 или 2.\n";
          }
          else {
              sortFilmsByTitle(videoteka, N);
              AllFilmsInfoInput(videoteka, N);
          }
          break;

      case 6:
          if (!dataLoaded) {
              cout << "\nОшибка! Сначала необходимо заполнить видеотеку. Выберите пункт 1 или 2.\n";
          }
          else {
              sortFilmsByCostAsc(videoteka, N);
              AllFilmsInfoInput(videoteka, N);
          }
          break;

      case 7:
          if (!dataLoaded) {
              cout << "\nОшибка! Сначала необходимо заполнить видеотеку. Выберите пункт 1 или 2.\n";
          }
          else {
              sortFilmsByCostDesc(videoteka, N);
              AllFilmsInfoInput(videoteka, N);
          }
          break;

      case 8:
          if (!dataLoaded) {
              cout << "\nОшибка! Сначала необходимо заполнить видеотеку. Выберите пункт 1 или 2.\n";
          }
          else {
              sortFilmsByDirector(videoteka, N);
              AllFilmsInfoInput(videoteka, N);
          }
          break;

      case 9:
          cout << "\nДо свидания!\n";
          break;

      default:
          cout << "\nНеверный выбор. Попробуйте снова.\n";
          break;
      }

      if (choice != 9) {
          cout << "\nНажмите Enter для продолжения...";
          cin.get();
      }

  } while (choice != 9);

  delete[] videoteka;

 return 0;
}