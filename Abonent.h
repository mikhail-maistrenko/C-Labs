#pragma once
#include <string>;
#include <iostream>;

class Abonent {

private:
	std::string FullName;
	int InstallYear;
	std::string PhoneNumber;
	std::string Address;
	std::string Comment;

public:
	Abonent();
	Abonent(const std::string& name, int year, const std::string& phone,
			const std::string& addr, const std::string& com = "");
	Abonent(const Abonent& other);
	~Abonent() = default;

	std::string getFullName() const { return  FullName; }
	int getInstallYear() const { return InstallYear; }
	std::string getPhoneNumber() const { return PhoneNumber; }
	std::string getAddress()  const { return  Address; }
	std::string getComment() const { return Comment; }

	void setFullName(const std::string& name);
	void setInstallYear(const int year);
	void setPhoneNumber(const std::string& phone);
	void setAddress(const std::string& addr);
	void setComment(const std::string& c) { Comment = c; }

	void print() const;
	bool InstalledInYear(int year) const;
	bool PhoneEndsNULL(char digit) const;

	bool operator ==(const Abonent& other) const;
	friend std::ostream& operator<<(std::ostream& os, const Abonent& a);
};
// В базе хранятся сведения о телефонах абонентов. Каждая запись содержит
//поля: Ф.И.О.абонента, год установки телефона, номер телефона, адрес
//местожительства, примечание.Организовать вывод списка абонентов,
//установивших телефон в указанном году, а также список абонентов, у которых
//номер телефона заканчивается на 0.