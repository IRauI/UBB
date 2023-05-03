#pragma once
#include <string>
#include <iostream>

using std::string;
using std::ostream;

class Activity
{
private:
	std::string title;
	std::string description;
	std::string type;
	int duration;
public:
	Activity() = default;

	Activity(const string title, const string description, const string type, const int duration) :
		title{ title }, description{ description }, type{ type }, duration{ duration }{}

	Activity(const Activity& a) : title{ a.getTitle() }, description{ a.getDescription() }, type{ a.getType() }, duration{ a.getDuration() }{};

	Activity& operator =(const Activity& a) {
		title = a.getTitle();
		description = a.getDescription();
		type = a.getType();
		duration = a.getDuration();
		return *this;
	}

	Activity(Activity&&) = default;

	Activity& operator =(Activity&&) = default;

	~Activity() = default;

	string getTitle() const {
		return title;
	}

	string getDescription() const {
		return description;
	}

	string getType() const {
		return type;
	}

	int getDuration() const noexcept {
		return duration;
	}

	void setType(const string t) {
		type = t;
	}

	void setDescription(const string d) {
		description = d;
	}

	void setDuration(const int d) noexcept {
		duration = d;
	}

	bool operator == (const Activity& a) {
		if (title == a.getTitle())
			return true;
		return false;
	}


	friend ostream& operator <<(ostream& out, const Activity& a) {
		return out << a.getTitle() << " " << a.getDescription() << " " << a.getType() << " " << a.getDuration();
	}
};


/*
Compara dupa descriere
returneaza true daca a1.descriere e mai mic decat a2.descriere
*/
bool cmpDescription(const Activity& a1, const Activity& a2);

/*
Compara dupa titlu
returneaza true daca a1.title e mai mic decat a2.title
*/
bool cmpTitle(const Activity& a1, const Activity& a2);

/*
Compara dupa tip + durata
returneaza true a1 < a2
*/
bool cmpTypeDuration(const Activity& a1, const Activity& a2);

