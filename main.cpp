#include "Abonent.h"
#include <iostream>
#include <vector>
#include <string>
#include <limits>
//#include <stdexcept>
//#include <locale>

using std::vector;
using std::string;
using std::cout;
using std::cin;


void fillDemo(vector<Abonent>& list) {
	list.clear();
	list.emplace_back("Иванов Иван Иванович", 2000, "89611234560", "г. Ростов-на-Дону, ул. Ленина, 1", "льготный");
	list.emplace_back("Петров Пётр Петрович", 2018, "84957654321", "г. Москва, ул. Гагарина, 5", "");
	list.emplace_back("Сидорова Анна Сергеевна", 2015, "84951112230", "г. Тверь, ул. Мира, 12", "пенсионер");
	list.emplace_back("Кузнецов Олег Игоревич", 2020, "84959998877", "г. Сочи, ул. Морская, 3", "");
	list.emplace_back("Поркшеян Виталий Маркосович", 2019, "84953334450", "г. Казань, ул. Баумана, 8", "VIP");
	list.emplace_back("Сабельников Руслан Михайлович", 2025, "89610001110", "г. Пермь, ул. Садовая, 9", "");
	cout << "\nСгенерировано " << list.size() << " записей.\n";
}


void InputManual(vector<Abonent>& list) {
	list.clear();

	int count;
	cout << "Сколько абонентов добавить? ";
	cin >> count;
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	for (int i = 0; i < count; ++i) {
		string name, phone, addr, com;
		int year;

		cout << "\n Абонент #" << i + 1 << " ---\n";

		while (true) {
			cout << "Ф.И.О.: ";
			std::getline(cin, name);
			if (!name.empty()) break;
			cout << "  Поле не может быть пустым. Попробуйте ввести еще раз.\n";
		}

		while (true) {
			cout << "Год установки (1960-2026): ";
			cin >> year;
			if (cin.fail()) {
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				cout << "  Введите число.\n";
				continue;
			}
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			if (year >= 1960 && year <= 2026) break;
			cout << "  Год должен быть в диапазоне 1960-2026.\n";
		}

		while (true) {
			cout << "Номер телефона: ";
			std::getline(cin, phone);
			if (!phone.empty()) break;
			cout << "  Поле не может быть пустым. Повторите.\n";
		}

		while (true) {
			cout << "Адрес: ";
			std::getline(cin, addr);
			if (!addr.empty()) break;
			cout << "  Поле не может быть пустым. Повторите.\n";
		}

		cout << "Примечание может быть пустым: ";
		std::getline(cin, com);

		try {
			list.emplace_back(name, year, phone, addr, com);
		}
		catch (const std::exception& e) {
			cout << "  Ошибка при создании: " << e.what() << "\n";
			--i;
		}
	}
	cout << "\nДобавлено " << list.size() << " записей.\n";
}

void printAll(const vector<Abonent>& list) {
	if (list.empty()) {
		cout << "Список пуст.\n";
		return;
	}
	cout << "\n   Все абоненты (" << list.size() << ")   \n";
	for (const auto& a : list)
		a.print();
}

void find_by_year(const vector<Abonent>& list) {
	if (list.empty()) { cout << "Сначала заполните базу из абонентов.\n"; return; }

	int year;
	cout << "Введите год установки: ";
	cin >> year;
	if (cin.fail()) {
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << "Неверный ввод.\n";
		return;
	}

	cout << "\n   Абоненты, установившие телефон в " << year << " году -->\n";
	bool found = false;
	for (const auto& a : list) {
		if (a.InstalledInYear(year)) {
			a.print();
			found = true;
		}
	}
	if (!found) cout << "Записей не найдено.\n";
}

void find_by_last_digit(const vector<Abonent>& list) {
	if (list.empty()) { cout << "Сначала заполните коллекцию.\n"; return; }

	cout << "\n   Абоненты, чей номер заканчивается на 0 \n";
	bool found = false;
	for (const auto& a : list) {
		if (a.PhoneEndsNULL('0')) {
			a.print();
			found = true;
		}
	}
	if (!found) cout << "Записей не найдено.\n";
}

int main() {
	setlocale(LC_ALL, "Russian");

	vector<Abonent> abonents;
	bool filled = false;
	int choice;
	do {
		cout << "\n МЕНЮ \n";
		cout << "1. Заполнить данные вручную\n";
		cout << "2. Сгенерировать данные\n";
		cout << "3. Показать всех абонентов\n";
		cout << "4. Найти по году установки\n";
		cout << "5. Найти номера, оканчивающиеся на 0\n";
		cout << "0. Выход\n";
		cout << "Ваш выбор: ";

		cin >> choice;

		if (cin.fail()) {
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << "Неверный ввод. Введите число.\n";
			continue;
		}

		switch (choice) {
		case 1:
			InputManual(abonents);
			filled = true;
			break;

		case 2:
			fillDemo(abonents);
			filled = true;
			break;

		case 3:
			if (!filled) cout << "Сначала выберите пункт 1 или 2\n";
			else        printAll(abonents);
			break;

		case 4:
			if (!filled) cout << "Сначала выберите пункт 1 или 2\n";
			else        find_by_year(abonents);
			break;

		case 5:
			if (!filled) cout << "Сначала выберите пункт 1 или 2\n";
			else        find_by_last_digit(abonents);
			break;

		case 0:
			cout << "Выход.\n";
			break;

		default:
			cout << "Неверный пункт меню.\n";
		}
	} while (choice != 0);

	return 0;
}