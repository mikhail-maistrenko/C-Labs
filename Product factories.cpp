#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <string>
#include <limits>
#define NOMINMAX  
#include <windows.h>

using namespace std;

int inputInt(const string& parameter) {
    int value;
    while (true) {
        cout << parameter;
        cin >> value;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ошибка! Введите целое число.\n";
        }
        else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
    }
}

string inputString(const string& parameter) {
    string value;
    cout << parameter;
    getline(cin, value);
    return value;
}

class ProductFactories {
private:
    char* name;
    char* cipher;
    int quantity;
    static int objectCount;

    friend void printInfo(const ProductFactories& pf);

public:
    ProductFactories() : quantity(0) {
        name = new char[1];   name[0] = '\0';
        cipher = new char[1]; cipher[0] = '\0';
        objectCount++;
    }

    ProductFactories(const char* n, const char* c, int q) : quantity(q) {
        name = new char[strlen(n) + 1];   strcpy(name, n);
        cipher = new char[strlen(c) + 1]; strcpy(cipher, c);
        objectCount++;
    }

    ~ProductFactories() {
        delete[] name;
        delete[] cipher;
        objectCount--;
    }

    void increaseProduction(int amount) {
        if (amount > 0) {
            quantity += amount;
            cout << "Продукция \"" << name << "\" увеличена на "
                << amount << ". Теперь: " << quantity << endl;
        }
        else {
            cout << "Ошибка! количество должно быть положительным!\n";
        }
    }

    void changeCipher(const char* newCipher) {
        delete[] cipher;
        cipher = new char[strlen(newCipher) + 1];
        strcpy(cipher, newCipher);
        cout << "Шифр \"" << name << "\" изменен на: " << cipher << endl;
    }

    const char* getName() const { return name; }
    const char* getCipher() const { return cipher; }
    int getQuantity() const { return quantity; }

    static int getObjectCount() { return objectCount; }
};

int ProductFactories::objectCount = 0;

void printInfo(const ProductFactories& pf) {
    cout << " Информация о продукте:\n";
    cout << "Имя:        " << pf.name << endl;
    cout << "Шифр:       " << pf.cipher << endl;
    cout << "Количество: " << pf.quantity << endl;
}

class SecretFactory {
private:
    string productName;
    int code;

    SecretFactory(const string& n, int c) : productName(n), code(c) {
        cout << "SecretFactory создан: " << productName << endl;
    }
    ~SecretFactory() {
        cout << "SecretFactory уничтожен: " << productName << endl;
    }

public:
    static SecretFactory* create(const string& n, int c) {
        return new SecretFactory(n, c);
    }
    static void destroy(SecretFactory* obj) { delete obj; }

    void showInfo() const {
        cout << "Продукт: " << productName << ", Код: " << code << endl;
    }
};

class ExternalFactory {
private:
    string productName;
    int code;

    ExternalFactory(const string& n, int c) : productName(n), code(c) {
        cout << "ExternalFactory создан: " << productName << endl;
    }
    ~ExternalFactory() {
        cout << "ExternalFactory уничтожен: " << productName << endl;
    }

    friend ExternalFactory* createExternal(const string&, int);
    friend void destroyExternal(ExternalFactory*);

public:
    void showInfo() const {
        cout << "Продукт: " << productName << ", Код: " << code << endl;
    }
};

ExternalFactory* createExternal(const string& n, int c) {
    return new ExternalFactory(n, c);
}
void destroyExternal(ExternalFactory* obj) { delete obj; }


int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    setlocale(LC_ALL, "Russian");

 
    cout << "Объектов при входе в main: "
        << ProductFactories::getObjectCount() << endl << endl;

    string name = inputString("Введите название продукта: ");
    string cipher = inputString("Введите шифр продукта: ");
    int quantity = inputInt("Введите количество продукции: ");

    ProductFactories factory(name.c_str(), cipher.c_str(), quantity);
    printInfo(factory);


    int choice = 0;
    while (choice != 4) {
        cout << "МЕНЮ: \n";
        cout << "1. Увеличить продукцию\n";
        cout << "2. Изменить шифр\n";
        cout << "3. Показать информацию\n";
        cout << "4. Продемонстрировать тесты\n";
        choice = inputInt("Ваш выбор: ");

        switch (choice) {
        case 1: factory.increaseProduction(inputInt("На сколько? ")); break;
        case 2: factory.changeCipher(inputString("Новый шифр: ").c_str()); break;
        case 3: printInfo(factory); break;
        case 4: break;
        default: cout << "Неверный выбор! Введите 1-4.\n";
        }
    }

    cout << "\n ТЕСТ: статический массив \n";
    {
        ProductFactories arr[2] = {
            ProductFactories("Кефир", "KFR-005", 30),
            ProductFactories("Йогурт", "YGT-006", 40)
        };
        cout << "Объектов после статического массива: "
            << ProductFactories::getObjectCount() << endl;
    }
    cout << "Объектов после выхода из блока массива: "
        << ProductFactories::getObjectCount() << endl;

    cout << "\n ТЕСТ: динамическое создание \n";
    ProductFactories* dynamic = new ProductFactories("Масло", "BTR-004", 75);
    cout << "Объектов после динамического создания: "
        << ProductFactories::getObjectCount() << endl;

    cout << "\n ТЕСТ: удаление динамического \n";
    delete dynamic;
    cout << "Объектов после удаления динамического: "
        << ProductFactories::getObjectCount() << endl;

    cout << "\n  ТЕСТ: SecretFactory \n";
    SecretFactory* s = SecretFactory::create("Секрет", 12345);
    s->showInfo();
    SecretFactory::destroy(s);

    cout << "\n ТЕСТ: ExternalFactory \n";
    ExternalFactory* e = createExternal("Внешний", 999);
    e->showInfo();
    destroyExternal(e);

    cout << "\nОбъектов перед выходом из main: "
        << ProductFactories::getObjectCount() << endl;

    return 0;
}