#define NOMINMAX
#include <windows.h>
#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <stdexcept>
#include <clocale>

using std::vector;
using std::string;
using std::cout;
using std::cin;

int inputInt(const string& prompt, int lo, int hi) {
	int v;
	while (true) {
		cout << prompt;
		if (cin >> v && v >= lo && v <= hi) {
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			return v;
		}
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << "  Ошибка! Введите число от " << lo << " до " << hi << ".\n";
	}
}

string inputLine(const string& prompt, bool allowEmpty = false) {
	string s;
	while (true) {
		cout << prompt;
		std::getline(cin, s);
		size_t b = s.find_first_not_of(" \t");
		size_t e = s.find_last_not_of(" \t");
		s = (b == string::npos) ? "" : s.substr(b, e - b + 1);
		if (allowEmpty || !s.empty()) return s;
		cout << "  Поле не может быть пустым. Повторите.\n";
	}
}

class Abonent {
private:
	string FullName;
	int InstallYear;
	string PhoneNumber;
	string Address;
	string Comment;

public:
	Abonent()
		: FullName("Неизвестно"), InstallYear(0), PhoneNumber("Не определен"),
		Address("Не указан"), Comment("") {
	}

	Abonent(const string& name, int year, const string& phone,
		const string& addr, const string& com_ = "")
		: FullName(name), InstallYear(year), PhoneNumber(phone),
		Address(addr), Comment(com_) {
		if (year < 1960 || year > 2026)
			throw std::invalid_argument("Ошибка! Неправильно указан год установки");
	}

	Abonent(const Abonent& other)
		: FullName(other.FullName), InstallYear(other.InstallYear),
		PhoneNumber(other.PhoneNumber), Address(other.Address),
		Comment(other.Comment) {
	}

	~Abonent() = default;

	string getFullName() const { return FullName; }
	int getInstallYear() const { return InstallYear; }
	string getPhoneNumber() const { return PhoneNumber; }
	string getAddress() const { return Address; }
	string getComment() const { return Comment; }

	void setFullName(const string& name) {
		if (name.empty()) throw std::invalid_argument("Ф.И.О. не может быть пустым");
		FullName = name;
	}
	void setInstallYear(int year) {
		if (year < 1960 || year > 2026) throw std::invalid_argument("Неверный год");
		InstallYear = year;
	}
	void setPhoneNumber(const string& phone) {
		if (phone.empty()) throw std::invalid_argument("Телефон не может быть пустым");
		PhoneNumber = phone;
	}
	void setAddress(const string& addr) {
		if (addr.empty()) throw std::invalid_argument("Адрес не может быть пустым");
		Address = addr;
	}
	void setComment(const string& c) { Comment = c; }

	void print() const {
		cout << "Ф.И.О.: " << FullName << "\n"
			<< "Год установки: " << InstallYear << "\n"
			<< "Телефон: " << PhoneNumber << "\n"
			<< "Адрес: " << Address << "\n"
			<< "Примечание: " << (Comment.empty() ? "—" : Comment) << "\n"
			<< "----------------------------------------\n";
	}

	bool InstalledInYear(int year) const { return InstallYear == year; }
	bool PhoneEndsNULL(char digit) const {
		return !PhoneNumber.empty() && PhoneNumber.back() == digit;
	}

	Abonent& operator=(const Abonent& other) {
		if (this != &other) {
			FullName = other.FullName;
			InstallYear = other.InstallYear;
			PhoneNumber = other.PhoneNumber;
			Address = other.Address;
			Comment = other.Comment;
		}
		return *this;
	}

	bool operator==(const Abonent& other) const {
		return PhoneNumber == other.PhoneNumber && FullName == other.FullName;
	}
	bool operator!=(const Abonent& other) const { return !(*this == other); }
	bool operator<(const Abonent& other)  const { return InstallYear < other.InstallYear; }

	int operator+(int n) const { return InstallYear + n; }
	int operator+(const Abonent& other) const { return InstallYear + other.InstallYear; }

	friend std::ostream& operator<<(std::ostream& os, const Abonent& a) {
		os << a.FullName << " | " << a.PhoneNumber << " | "
			<< a.InstallYear << " | " << a.Address;
		if (!a.Comment.empty()) os << " | " << a.Comment;
		return os;
	}
};

class AbonentBase {
private:
	vector<Abonent> data;

public:
	AbonentBase() = default;
	AbonentBase(const AbonentBase& other) : data(other.data) {}
	~AbonentBase() = default;

	void add(const Abonent& a) { data.push_back(a); }
	void clear() { data.clear(); }
	size_t size() const { return data.size(); }
	bool empty() const { return data.empty(); }

	Abonent& operator[](size_t i) { return data[i]; }
	const Abonent& operator[](size_t i) const { return data[i]; }

	AbonentBase& operator=(const AbonentBase& other) {
		if (this != &other) data = other.data;
		return *this;
	}

	friend std::ostream& operator<<(std::ostream& os, const AbonentBase& b) {
		if (b.data.empty()) { os << "Список пуст.\n"; return os; }
		for (const auto& a : b.data) os << a << "\n";
		return os;
	}

	void printByYear(int year) const {
		cout << "\n   Абоненты, установившие телефон в " << year << " году -->\n";
		bool found = false;
		for (const auto& a : data)
			if (a.InstalledInYear(year)) { a.print(); found = true; }
		if (!found) cout << "Записей не найдено.\n";
	}

	void printEndingWithZero() const {
		cout << "\n   Абоненты, чей номер заканчивается на 0 -->\n";
		bool found = false;
		for (const auto& a : data)
			if (a.PhoneEndsNULL('0')) { a.print(); found = true; }
		if (!found) cout << "Записей не найдено.\n";
	}
};

void fillDemo(AbonentBase& base) {
	base.clear();
	base.add(Abonent("Иванов Иван Иванович", 2000, "89611234560", "г. Ростов-на-Дону, ул. Ленина, 1", "льготный"));
	base.add(Abonent("Петров Пётр Петрович", 2018, "84957654321", "г. Москва, ул. Гагарина, 5", ""));
	base.add(Abonent("Сидорова Анна Сергеевна", 2015, "84951112230", "г. Тверь, ул. Мира, 12", "пенсионер"));
	base.add(Abonent("Кузнецов Олег Игоревич", 2020, "84959998877", "г. Сочи, ул. Морская, 3", ""));
	base.add(Abonent("Поркшеян Виталий Маркосович", 2019, "84953334450", "г. Казань, ул. Баумана, 8", "VIP"));
	base.add(Abonent("Сабельников Руслан Михайлович", 2025, "89610001110", "г. Пермь, ул. Садовая, 9", ""));
	cout << "\nСгенерировано " << base.size() << " записей.\n";
}

void InputManual(AbonentBase& base) {
	base.clear();
	int count = inputInt("Сколько абонентов добавить? ", 1, 50);

	for (int i = 0; i < count; ++i) {
		cout << "\n Абонент #" << i + 1 << " ---\n";
		string name = inputLine("Ф.И.О.: ");
		int year = inputInt("Год установки (1960-2026): ", 1960, 2026);
		string phone = inputLine("Номер телефона: ");
		string addr = inputLine("Адрес: ");
		string com = inputLine("Примечание (можно пустое): ", true);

		try {
			base.add(Abonent(name, year, phone, addr, com));
		}
		catch (const std::exception& e) {
			cout << "  Ошибка при создании: " << e.what() << "\n";
			--i;
		}
	}
	cout << "\nДобавлено " << base.size() << " записей.\n";
}

void printAll(const AbonentBase& base) {
	if (base.empty()) { cout << "Список пуст.\n"; return; }
	cout << "\n   Все абоненты (" << base.size() << ")   \n";
	cout << base;
}

void demoOperators(AbonentBase& base) {
	if (base.size() < 2) {
		cout << "Нужно минимум 2 записи для демонстрации.\n";
		return;
	}
	cout << "\nДемонстрация перегруженных операций \n";
	cout << "1) base[0] = " << base[0] << "\n";
	cout << "2) base[0] == base[1] ? " << (base[0] == base[1] ? "да" : "нет") << "\n";
	cout << "3) base[0] != base[1] ? " << (base[0] != base[1] ? "да" : "нет") << "\n";
	cout << "4) base[0] <  base[1] ? " << (base[0] < base[1] ? "да" : "нет") << "\n";
	cout << "5) base[0] + 5 = " << (base[0] + 5) << "\n";
	cout << "6) base[0] + base[1] = " << (base[0] + base[1]) << " (сумма годов)\n";

	Abonent tmp;
	tmp = base[0];
	cout << "7) tmp = base[0]; tmp = " << tmp << "\n";

	AbonentBase copy;
	copy = base;
	cout << "8) copy = base; copy.size() = " << copy.size() << "\n";
}

int main() {
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	setlocale(LC_ALL, "Russian");

	AbonentBase abonents;
	bool filled = false;
	int choice;

	do {
		cout << "\n МЕНЮ \n";
		cout << "1. Заполнить данные вручную\n";
		cout << "2. Сгенерировать данные\n";
		cout << "3. Показать всех абонентов\n";
		cout << "4. Найти по году установки\n";
		cout << "5. Найти номера, оканчивающиеся на 0\n";
		cout << "6. Демонстрация перегруженных операций\n";
		cout << "0. Выход\n";
		cout << "Ваш выбор: ";

		choice = inputInt("", 0, 6); 

		switch (choice) {
		case 1: InputManual(abonents); filled = true; break;
		case 2: fillDemo(abonents);    filled = true; break;
		case 3:
			if (!filled) cout << "Сначала выберите пункт 1 или 2\n";
			else printAll(abonents);
			break;
		case 4:
			if (!filled) { cout << "Сначала выберите пункт 1 или 2\n"; break; }
			abonents.printByYear(inputInt("Введите год установки: ", 1960, 2026));
			break;
		case 5:
			if (!filled) cout << "Сначала выберите пункт 1 или 2\n";
			else abonents.printEndingWithZero();
			break;
		case 6:
			if (!filled) cout << "Сначала выберите пункт 1 или 2\n";
			else demoOperators(abonents);
			break;
		case 0:
			cout << "Выход.\n";
			break;
		}
	} while (choice != 0);

	return 0;
}