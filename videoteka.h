#ifndef VIDEOTEKA_H
#define VIDEOTEKA_H
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <algorithm>
using namespace std;

struct Film {
    string title;
    double cost;
    string director;
};

const int N = 5;

void generateRandomFilms(Film* films, int size);
void ManualFilmInput(Film* films, int size);
void AllFilmsInfoInput(const Film* films, int size);
void OutputFilmsByDirector(const Film* films, int size, const string& director);
void Menu();
int getIntInput(const string& request, int min, int max);
double getDoubleInput(const string& request, double min, double max);
string getStringInput(const string& request);


void sortFilmsByTitle(Film* films, int size);
void sortFilmsByCostAsc(Film* films, int size);
void sortFilmsByCostDesc(Film* films, int size);
void sortFilmsByDirector(Film* films, int size);

#endif