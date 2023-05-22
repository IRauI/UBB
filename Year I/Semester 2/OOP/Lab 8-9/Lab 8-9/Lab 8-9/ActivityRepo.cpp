#include "ActivityRepo.h"
#include <sstream>
#include <assert.h>
#include <algorithm>

using std::ostream;
using std::stringstream;

bool ActivityRepo::exists(const Activity& a) const {
	try {
		fnd(a.getTitle());
		return true;
	}
	catch (ActivityRepoException&) {
		return false;}
}

void ActivityRepo::store(const Activity& a) {
	if (exists(a))
		throw ActivityRepoException("Exista deja activitatea!");
	activities.push_back(a);
}

void ActivityRepo::rmv(const Activity& a) {
	if (!exists(a))
		throw ActivityRepoException("Activitatea nu exista!");
	/*
	for (vector<Activity>::iterator it = activities.begin(); it < activities.end(); it++)
		if (*it == a) {
			activities.erase(it);
			break;
		}
	*/
	activities.erase(find(activities.begin(), activities.end(), a));
	
}


void ActivityRepo::modify(const Activity& a, const string& newDescription, const string& newType, const int& newDuration) {
	if (!exists(a))
		throw ActivityRepoException("Activitatea nu exista!");
	std::vector<Activity>::iterator it = find(activities.begin(), activities.end(), a);
	activities.at(it - activities.begin()).setDescription(newDescription);
	activities.at(it - activities.begin()).setType(newType);
	activities.at(it - activities.begin()).setDuration(newDuration);
	
}

Activity ActivityRepo::fnd(const string& title) const {
	for (auto a : activities) {
		if (a.getTitle() == title)
			return a;
	}
	throw ActivityRepoException("Nu exista activitatea");

}

const vector<Activity>& ActivityRepo::getAll() const noexcept {
	return activities;
}

void ActivityRepo::setAll(const vector<Activity>& a) {
	activities = a;
}

void testAdauga() {
	ActivityRepo rep;
	rep.store(Activity{ "a","a","a",10 });
	rep.store(Activity{ "b","b","b",20 });
	assert(rep.getAll().size() == 2);
	std::stringstream out;
	out << rep.getAll().at(0);
	try {
		rep.store(Activity{ "a","b","b",30 });
	}
	catch (const ActivityRepoException&) {
		assert(true);
	}
}

void testRemove() {
	ActivityRepo rep;
	Activity a("a", "a", "a", 30);
	rep.store(a);
	Activity b("b", "b", "b", 20);
	rep.store(b);
	rep.rmv(b);
	assert(rep.getAll().size() == 1);

	try {
		rep.rmv(b);
	}
	catch (const ActivityRepoException&) {
		assert(true);
	}

}

void testModify() {
	ActivityRepo rep;
	rep.store(Activity{ "a","a","a",10 });
	rep.store(Activity{ "b","b","b",20 });
	rep.modify(Activity{ "b","b","b",20 }, "c", "c", 30);

	try
	{
		rep.modify(Activity{ "c","b","b",20 }, "c", "c", 30);
	}
	catch (const ActivityRepoException& e)
	{
		std::stringstream out;
		out << e;
		assert(true);
	}
}

void testeRepo() {
	testAdauga();
	testRemove();
	testModify();
}