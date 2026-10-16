#pragma once
#include <string>
using namespace std;

class Person {
	string name;
	int age;
public:
	Person();
	string getName() const { return name; }
	int getAge() const { return age; }

	void setName(const string& n);
	void setAge(int a);
};