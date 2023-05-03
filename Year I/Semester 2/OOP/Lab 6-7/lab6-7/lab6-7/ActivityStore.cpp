#include "ActivityStore.h"
#include <functional>
#include <algorithm>
#include <assert.h>


void ActivityStore::addActivity(const string& title, const string& description, const string& type, const int& duration) {
	Activity a(title, description, type, duration);
	val.validate(a);
	rep.store(a);
}

void ActivityStore::removeActivity(const Activity& a) {
	val.validate(a);
	rep.rmv(a);
}

void ActivityStore::modifyActivity(const Activity& a, const string& newDescription, const string& newType, const int& newDuration) {
	val.validate(a);
	Activity aux("aux", newDescription, newType, newDuration);
	val.validate(aux);
	rep.modify(a, newDescription, newType, newDuration);
}

VectDinNewDeleteT<Activity> ActivityStore::sortByTitle() const {
	//auto cpy = rep.getAll();
	//std::sort(cpy.begin(), cpy.end(), cmpTitle);
	//return cpy;
	
	VectDinNewDeleteT<Activity> aux;
	aux = rep.getAll();
	for (int i = 0; i < aux.size() - 1; ++i) {
		for (int j = i + 1; j < aux.size(); ++j) {
			if (aux.get(i).getTitle() > aux.get(j).getTitle()) {
				Activity a = aux.get(i);
				aux.get(i) = aux.get(j);
				aux.get(j) = a;
			}
		}
	}

	return aux;
}

VectDinNewDeleteT<Activity> ActivityStore::sortByDescription() const {
	//auto cpy = rep.getAll();
	//std::sort(cpy.begin(), cpy.end(), cmpDescription);
	//return cpy;

	VectDinNewDeleteT<Activity> aux = rep.getAll();
	for (int i = 0; i < aux.size() - 1; ++i) {
		for (int j = i + 1; j < aux.size(); ++j) {
			if (aux.get(i).getDescription() > aux.get(j).getDescription()) {
				Activity a = aux.get(i);
				aux.get(i) = aux.get(j);
				aux.get(j) = a;
			}
		}
	}

	return aux;
}

VectDinNewDeleteT<Activity> ActivityStore::sortByTypeDuration() const {
	//auto cpy = rep.getAll();
	//std::sort(cpy.begin(), cpy.end(), cmpTypeDuration);
	//return cpy;
	VectDinNewDeleteT<Activity> aux;
	aux = rep.getAll();
	for (int i = 0; i < aux.size() - 1; ++i) {
		for (int j = i + 1; j < aux.size(); ++j) {
			if (aux.get(i).getType() > aux.get(j).getType()) {
				Activity a = aux.get(i);
				aux.get(i) = aux.get(j);
				aux.get(j) = a;
			}
			else if (aux.get(i).getType() == aux.get(j).getType() && aux.get(i).getDuration() > aux.get(j).getDuration()) {
				Activity a = aux.get(i);
				aux.get(i) = aux.get(j);
				aux.get(j) = a;
			}
		}
	}

	return aux;
}

VectDinNewDeleteT<Activity> ActivityStore::filter(function<bool(const Activity&)> func) const{
	VectDinNewDeleteT<Activity> rez;
	for (int i = 0; i < rep.getAll().size(); ++i) {
		if (func(rep.getAll().get(i))) {
			rez.add(rep.getAll().get(i));
		}
	}
	return rez;
}

VectDinNewDeleteT<Activity> ActivityStore::filterByType(const string& type) const {
	return filter([type](const Activity& a) {
		return a.getType() == type;
		});
}

VectDinNewDeleteT<Activity> ActivityStore::filterByDescription(const string& description) const {
	return filter([description](const Activity& a) {
		return a.getDescription() == description;
		});
}

void testAdd() {
	ActivityRepo rep;
	ActivityValidator val;
	ActivityStore ctr{ rep,val };
	ctr.addActivity("a", "a", "a", 6);
	assert(ctr.getAll2().size() == 1);

	try {
		ctr.addActivity("", "", "", - 1);
	}
	catch (ValidateException&) {
		assert(true);
	}
	//incerc sa adaug ceva ce existadeja
	try {
		ctr.addActivity("a", "b", "c", 8);
	}
	catch (ActivityRepoException&) {
		assert(true);
	}
}

void testRmv() {
	ActivityRepo rep;
	ActivityValidator val;
	ActivityStore ctr{ rep,val };
	ctr.addActivity("a", "a", "a", 6);
	ctr.addActivity("b", "a", "a", 6);
	ctr.addActivity("c", "a", "a", 6);
	Activity b("b", "a", "a", 6);
	ctr.removeActivity(b);
	assert(ctr.getAll2().size() == 2);
	try {
		Activity aux("", "", "", -1);
		ctr.removeActivity(aux);}
	catch (ValidateException&) {
		assert(true);
	}

}

void testModify2() {
	ActivityRepo rep;
	ActivityValidator val;
	ActivityStore ctr{ rep,val };
	ctr.addActivity("a", "a", "a", 6);
	ctr.addActivity("b", "a", "a", 6);
	ctr.addActivity("c", "a", "a", 6);
	Activity b("b", "b", "c", 10);
	ctr.modifyActivity(b, "b", "c", 10);
	assert(rep.getAll().get(1).getDescription() == "b" && rep.getAll().get(1).getType() == "c" && rep.getAll().get(1).getDuration() == 10);
	try {
		ctr.modifyActivity(b, "", "", -1);
	}
	catch (ValidateException&) {
		assert(true);
	}
}

void testSort() {
	ActivityRepo rep;
	ActivityValidator val;
	ActivityStore ctr{ rep,val };
	ctr.addActivity("z", "z", "z", 6);
	ctr.addActivity("b", "a", "c", 60);
	ctr.addActivity("c", "a", "c", 600);

	auto firstP = ctr.sortByTitle().get(0);
	assert(firstP.getTitle() == "b");

	firstP = ctr.sortByDescription().get(0);
	assert(firstP.getDescription() == "a");

	firstP = ctr.sortByTypeDuration().get(0);
	assert(firstP.getDuration() == 60);
}

void testFilter() {
	ActivityRepo rep;
	ActivityValidator val;
	ActivityStore ctr{ rep,val };
	ctr.addActivity("z", "z", "z", 6);
	ctr.addActivity("b", "a", "z", 60);
	ctr.addActivity("c", "a", "z", 600);
	assert(ctr.filterByDescription("a").size() == 2);
	assert(ctr.filterByType("z").size() == 3);
}

void testCtr() {
	testAdd();
	testRmv();
	testModify2();
	testSort();
	testFilter();
}
