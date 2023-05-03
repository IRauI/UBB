#pragma once
#include "Activity.h"
#include "VectorDinamicTemplate.h"

#include <vector>
#include <string>
#include <iostream>

using std::vector;
using std::string;
using std::ostream;

class ActivityRepo
{
private:
	VectDinNewDeleteT<Activity> activities;
	//vector<Activity> activities;
	bool exists(const Activity& a) const;
public:
	ActivityRepo() = default;

	ActivityRepo(const ActivityRepo& r) = delete;

	void store(const Activity& a);

	void rmv(const Activity& a);

	void modify(const Activity& a, const string& newDescription, const string& newType, const int& newDuration);

	Activity fnd(const string& title) const;

	const VectDinNewDeleteT<Activity>& getAll() const noexcept;
};

class ActivityRepoException {
	string msg;
public:
	ActivityRepoException(string m) :msg{ m } {}
	//functie friend (vreau sa folosesc membru privat msg)
	friend ostream& operator<<(ostream& out, const ActivityRepoException& ex) {
		return out << ex.msg;
	}
};



void testeRepo();
