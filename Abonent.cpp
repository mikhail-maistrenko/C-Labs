#include "Abonent.h"
#include <stdexcept>
#include <iostream>;


Abonent::Abonent()
	: FullName("Неизвестно"), InstallYear(0), PhoneNumber("Не определен"),
	Address("Не указан"), Comment("") {}

Abonent::Abonent(const std::string& name, int year, const std::string& phone,
	const std::string& addr, const std::string& com_)
	: FullName(name), InstallYear(year), PhoneNumber(phone),
	Address(addr), Comment(com_) {
	if (year < 1960 || year > 2026)
		throw std::invalid_argument("Ошибка! Не правильно указан год установки");
}

Abonent::Abonent(const Abonent& other)
	: FullName(other.FullName), InstallYear(other.InstallYear),
	PhoneNumber(other.PhoneNumber), Address(other.Address),
	Comment(other.Comment) {
}

void Abonent::setFullName(const std::string& name) {
	if (name.empty())
		throw std::invalid_argument("Ошибка! Ф.И.О. не может быть пустым");
	FullName = name;
}

void Abonent::setInstallYear(const int year) {
	if (year < 1960 || year > 2026)
		throw std::invalid_argument("Ошибка! Не правильно указан год установки");
	InstallYear = year;
}

void Abonent::setPhoneNumber(const std::string& phone) {
	if (phone.empty())
		throw std::invalid_argument("Ошибка! Номер телефона не может быть пустым");
	PhoneNumber = phone;
}

void Abonent::setAddress(const std::string& addr) {
	if (addr.empty())
		throw std::invalid_argument("Ошибка! Адрес не может быть пустым");
	Address = addr;
}

void Abonent::print() const {
	std::cout << "Ф.И.О.: " << FullName << "\n"
		<< "Год установки: " << InstallYear << "\n"
		<< "Телефон: " << PhoneNumber << "\n"
		<< "Адрес: " << Address << "\n"
		<< "Примечание: " << (Comment.empty() ? "—" : Comment) << "\n"
		<< "----------------------------------------\n";
}

bool Abonent::InstalledInYear(int year) const {
	return InstallYear == year;
}

bool Abonent::PhoneEndsNULL(char digit) const {
	if (PhoneNumber.empty()) return false;
	return PhoneNumber.back() == digit;
}

bool Abonent::operator==(const Abonent& other) const {
	return PhoneNumber == other.PhoneNumber &&
		FullName == other.FullName;
}

std::ostream& operator<<(std::ostream& os, const Abonent& a) {
	os << a.FullName << " | "
		<< a.PhoneNumber << " | "
		<< a.InstallYear << " | "
		<< a.Address;
	if (!a.Comment.empty())
		os << " | " << a.Comment;
	return os;
}