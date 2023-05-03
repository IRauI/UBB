#include "ActivityRepo.h"
#include <sstream>
#include <assert.h>

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
	if(exists(a))
		throw ActivityRepoException("Exista deja activitatea!");
	//activities.push_back(a);
	activities.add(a);
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
	VectDinNewDeleteT<Activity> aux;
	for (int i = 0; i < activities.size(); ++i)
	{
		if (!(activities.get(i) == a))
		{
			aux.add(activities.get(i));
		}
	}
	activities = aux;
}

void ActivityRepo::modify(const Activity& a, const string& newDescription, const string& newType, const int& newDuration) {
	if(!exists(a))
		throw ActivityRepoException("Activitatea nu exista!");
	/*
	std::vector<Activity>::iterator it = find(activities.begin(), activities.end(), a);
	activities.at(it - activities.begin()).setDescription(newDescription);
	activities.at(it - activities.begin()).setType(newType);
	activities.at(it - activities.begin()).setDuration(newDuration);
	*/
	for (int i = 0; i < activities.size(); ++i)
	{
		if (activities.get(i) == a)
		{
			activities.get(i).setDescription(newDescription);
			activities.get(i).setType(newType);
			activities.get(i).setDuration(newDuration);
			break;
		}
	}
}

Activity ActivityRepo::fnd(const string& title) const{
	/*
	for (Activity a : activities) {
		if (a.getTitle() == title)
			return a;
	}
	*/
	for (int i = 0; i < activities.size(); ++i)
	{
		if (activities.get(i).getTitle() == title)
			return activities.get(i);
	}
	throw ActivityRepoException("Activitatea nu exista!");
}

const VectDinNewDeleteT<Activity>& ActivityRepo::getAll() const noexcept {
	return activities;
}

void testAdauga() {
	ActivityRepo rep;
	rep.store(Activity{ "a","a","a",10 });
	rep.store(Activity{ "b","b","b",20 });
	assert(rep.getAll().size() == 2);
	std::stringstream out;
	out << rep.getAll().get(0);
	try {
		rep.store(Activity{ "a","b","b",30 });
	}
	catch (const ActivityRepoException&) {
		assert(true);
	}
}

void testRemove() {
	ActivityRepo rep;
	Activity a("a","a","a",30);
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