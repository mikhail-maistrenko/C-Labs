#include"Me.h"
#include <string>
using namespace std;

Person::Person()
	: name("NO"), age(0){ }
void Person::setName(const string& n) {
	name = n;
}
void Person::setAge(int a) {
	if (a >= 0) {
		age = a;
	}
}


