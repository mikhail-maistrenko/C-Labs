#include "videoteka.h"

void generateRandomFilms(Film* films, int size) {
    srand(time(0));

    string titles[] = {
        "Матрица", "Титаник", "Аватар", "Звездные войны", "Властелин колец",
        "Форрест Гамп", "Пираты Карибского моря", "Гарри Поттер", "Начало",
        "Интерстеллар", "Гладиатор", "Храброе сердце", "Бегущий по лезвию",
        "Бойцовский клуб", "Криминальное чтиво", "Зеленая миля", "Терминатор",
        "Список Шиндлера", "Леон", "Семь самураев"
    };

    string directors[] = {
        "Стивен Спилберг", "Кристофер Нолан", "Джеймс Кэмерон",
        "Квентин Тарантино", "Ридли Скотт", "Питер Джексон",
        "Альфред Хичкок", "Стэнли Кубрик", "Мартин Скорсезе",
        "Фрэнсис Форд Коппола", "Люк Бессон", "Гай Ричи"
    };

    for (int i = 0; i < size; i++) {
        int randomIndex = rand() % 20;
        films[i].title = titles[randomIndex];
        films[i].cost = 100 + (rand() % 900) + (rand() % 100) / 100.0;
        films[i].director = directors[randomIndex % 12];
    }
}

void ManualFilmInput(Film* films, int size) {
    cout << "Введите информацию о " << size << " фильмах:\n\n";

    for (int i = 0; i < size; i++) {
        cout << "Фильм: " << i + 1 << ":\n";
        cout << "  Название фильма: ";
        films[i].title = getStringInput("");
        cout << "  Стоимость (руб): ";
        films[i].cost = getDoubleInput("", 0, 999999);
        cout << "  Режиссер: ";
        films[i].director = getStringInput("");
        cout << endl;
    }
}

void AllFilmsInfoInput(const Film* films, int size) {
    cout << "Всего фильмов: " << size << "\n\n";
    cout << " Название фильма                       Стоимость (руб)  Режиссер\n";
    cout << "--------------------------------------------------------------\n";

    for (int i = 0; i < size; i++) {
        cout << i + 1 << ". ";
        cout << films[i].title;
        int titleLen = films[i].title.length();
        for (int j = titleLen; j < 32; j++) cout << " ";

        cout << "   " << films[i].cost;
        string costStr = to_string(films[i].cost);
        int costLen = costStr.length();
        for (int j = costLen; j < 12; j++) cout << " ";
        cout << "   " << films[i].director << endl;
    }
    cout << endl;
}

void OutputFilmsByDirector(const Film* films, int size, const string& director) {
    cout << "\n Фильмы выбранного режиссера: " << director;

    bool found = false;
    int count = 0;

    for (int i = 0; i < size; i++) {
        string filmDirector = films[i].director;
        string searchDirector = director;

        transform(filmDirector.begin(), filmDirector.end(), filmDirector.begin(), ::tolower);
        transform(searchDirector.begin(), searchDirector.end(), searchDirector.begin(), ::tolower);

        if (filmDirector == searchDirector) {
            if (!found) {
                cout << "\nНайдены следующие фильмы:\n";
                cout << "Название                          Стоимость (руб)\n";
                cout << "---------------------------------------------\n";
                found = true;
            }
            cout << films[i].title;
            int titleLen = films[i].title.length();
            for (int j = titleLen; j < 32; j++) cout << " ";
            cout << "   " << films[i].cost << endl;
            count++;
        }
    }
    if (!found) {
        cout << "\nФильмы режиссера \"" << director << "\" не найдены.\n";
    }
    else {
        cout << "\nВсего найдено: " << count << " фильмов.\n";
    }
    cout << endl;
}

void Menu() {
    cout << "      ВИДЕОТЕКА - ГЛАВНОЕ МЕНЮ\n";
    cout << "-----------------------------------------\n";
    cout << "1. Заполнить видеотеку случайными данными\n";
    cout << "2. Ввести данные о фильмах вручную\n";
    cout << "3. Показать всю видеотеку\n";
    cout << "4. Найти фильмы по режиссеру\n";
    cout << "5. Сортировка по названию\n";
    cout << "6. Сортировка по возрастанию стоимости\n";
    cout << "7. Сортировка по убыванию стоимости\n";
    cout << "8. Сортировка по режиссеру\n";
    cout << "9. Выход\n";
    cout << "-----------------------------------------\n";
    cout << "Ваш выбор: ";
}

int getIntInput(const string& request, int min, int max) {
    int value;
    bool valid = false;

    while (!valid) {
        if (!request.empty()) {
            cout << request;
        }
        cin >> value;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ошибка! Введите целое число.\n";
        }
        else if (value < min || value > max) {
            cout << "Ошибка! Число должно быть от " << min << " до " << max << ".\n";
        }
        else {
            valid = true;
        }
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return value;
}

double getDoubleInput(const string& request, double min, double max) {
    double value;
    bool valid = false;

    while (!valid) {
        if (!request.empty()) {
            cout << request;
        }
        cin >> value;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ошибка! Введите число.\n";
        }
        else if (value < min || value > max) {
            cout << "Ошибка! Число должно быть от " << min << " до " << max << ".\n";
        }
        else {
            valid = true;
        }
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return value;
}

string getStringInput(const string& request) {
    string value;
    bool valid = false;

    while (!valid) {
        if (!request.empty()) {
            cout << request;
        }
        getline(cin, value);
        value.erase(0, value.find_first_not_of(" \t"));
        value.erase(value.find_last_not_of(" \t") + 1);

        if (value.empty()) {
            cout << "Ошибка! Строка не может быть пустой.\n";
        }
        else {
            valid = true;
        }
    }

    return value;
}


void sortFilmsByTitle(Film* films, int size) {
    sort(films, films + size, [](const Film& a, const Film& b) {
        return a.title < b.title;
        });
    cout << "Фильмы отсортированы по названию.\n";
}

void sortFilmsByCostAsc(Film* films, int size) {
    sort(films, films + size, [](const Film& a, const Film& b) {
        return a.cost < b.cost;
        });
    cout << "Фильмы отсортированы по стоимости (от дешевых к дорогим).\n";
}

void sortFilmsByCostDesc(Film* films, int size) {
    sort(films, films + size, [](const Film& a, const Film& b) {
        return a.cost > b.cost;
        });
    cout << "Фильмы отсортированы по стоимости (от дорогих к дешевым).\n";
}


void sortFilmsByDirector(Film* films, int size) {
    sort(films, films + size, [](const Film& a, const Film& b) {
        return a.director < b.director;
        });
    cout << "Фильмы отсортированы по режиссеру.\n";
}