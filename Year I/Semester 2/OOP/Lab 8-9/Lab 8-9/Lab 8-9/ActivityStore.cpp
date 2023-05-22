#include "ActivityStore.h"
#include <functional>
#include <algorithm>
#include <assert.h>
#include <stdlib.h>


void ActivityStore::addActivity(const string& title, const string& description, const string& type, const int& duration) {
	aUndo.addState(rep.getAll());
	AddUndo* au = new AddUndo;
	au->addState(rep.getAll());
	undoList.push_back(au);
	Activity a(title, description, type, duration);
	val.validate(a);
	rep.store(a);

}

void ActivityStore::removeActivity(const Activity& a) {
	dUndo.addState(rep.getAll());
	DeleteUndo* au = new DeleteUndo;
	au->addState(rep.getAll());
	val.validate(a);
	rep.rmv(a);
}

void ActivityStore::modifyActivity(const Activity& a, const string& newDescription, const string& newType, const int& newDuration) {
	mUndo.addState(rep.getAll());
	ModifyUndo* au = new ModifyUndo;
	au->addState(rep.getAll());
	val.validate(a);
	Activity aux("aux", newDescription, newType, newDuration);
	val.validate(aux);
	rep.modify(a, newDescription, newType, newDuration);
}


void ActivityStore::emptyList(){
	lists.clearList();
}

void ActivityStore::saveList(string& file) {
	if (!has_suffix(file, ".csv")) {
		file += ".csv";
	}
	lists.saveList(file);
}

void ActivityStore::generateList(const int& noActivities){
	lists.generateList(rep.getAll(), noActivities);
}

vector<Activity> ActivityStore::sortByTitle() const {
	auto cpy = rep.getAll();
	std::sort(cpy.begin(), cpy.end(), cmpTitle);
	return cpy;
}

vector<Activity> ActivityStore::sortByDescription() const {
	auto cpy = rep.getAll();
	std::sort(cpy.begin(), cpy.end(), cmpDescription);
	return cpy;
}

vector<Activity> ActivityStore::sortByTypeDuration() const {
	vector<Activity> cpy = rep.getAll();
	std::sort(cpy.begin(), cpy.end(), cmpTypeDuration);
	return cpy;
}

vector<Activity> ActivityStore::filter(function<bool(const Activity&)> func) const {
	vector<Activity> cpy = rep.getAll();
	vector<Activity> rez(cpy.size());
	auto it = std::copy_if(cpy.begin(), cpy.end(), rez.begin(), func);
	rez.resize(std::distance(rez.begin(), it));
	return rez;
}

vector<Activity> ActivityStore::filterByType(const string& type) const {
	return filter([type](const Activity& a) {
		return a.getType() == type;
		});
}


void ActivityStore::undoAdd()
{
	rep.setAll(aUndo.getLastState());
	//aUndo.doUndo();
	
}

void ActivityStore::undoDelete()
{
	rep.setAll(dUndo.getLastState());
	//dUndo.doUndo();

}

void ActivityStore::undoModify()
{
	rep.setAll(mUndo.getLastState());
	//mUndo.doUndo();

}

void ActivityStore::undo()
{
	undoList.back()->doUndo(rep);
}

void ActivityStore::addToList2(const string& title)
{
	auto it = std::find_if(rep.getAll().begin(), rep.getAll().end(), [title](const Activity& a) { return a.getTitle() == title; });
	if(it - rep.getAll().begin() >= 0)
		lists.addToList(rep.getAll().at(it - rep.getAll().begin()));
}

vector<Activity> ActivityStore::filterByDescription(const string& description) const {
	return filter([description](const Activity& a) {
		return a.getDescription() == description;
		});
}

void testAdd() {
	ActivityRepo rep;
	ActivityValidator val;
	ActivityList list;
	ActivityStore ctr{ rep,val,list };
	ctr.addActivity("a", "a", "a", 6);
	assert(ctr.getAll2().size() == 1);

	try {
		ctr.addActivity("", "", "", -1);
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
	ActivityList list;
	ActivityStore ctr{ rep,val,list };
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
	ActivityList list;
	ActivityStore ctr{ rep,val,list };
	ctr.addActivity("a", "a", "a", 6);
	ctr.addActivity("b", "a", "a", 6);
	ctr.addActivity("c", "a", "a", 6);
	Activity b("b", "b", "c", 10);
	ctr.modifyActivity(b, "b", "c", 10);
	assert(rep.getAll().at(1).getDescription() == "b" && rep.getAll().at(1).getType() == "c" && rep.getAll().at(1).getDuration() == 10);
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
	ActivityList list;
	ActivityStore ctr{ rep,val,list };
	ctr.addActivity("z", "z", "z", 6);
	ctr.addActivity("b", "a", "c", 60);
	ctr.addActivity("c", "a", "c", 600);

	auto firstP = ctr.sortByTitle().at(0);
	assert(firstP.getTitle() == "b");

	firstP = ctr.sortByDescription().at(0);
	assert(firstP.getDescription() == "a");

	firstP = ctr.sortByTypeDuration().at(0);
	assert(firstP.getDuration() == 60);
}

void testFilter() {
	ActivityRepo rep;
	ActivityValidator val;
	ActivityList list;
	ActivityStore ctr{ rep,val,list };
	ctr.addActivity("z", "z", "z", 6);
	ctr.addActivity("b", "a", "z", 60);
	ctr.addActivity("c", "a", "z", 600);
	assert(ctr.filterByDescription("a").size() == 2);
	assert(ctr.filterByType("z").size() == 3);
}

void testList() {
	ActivityRepo rep;
	ActivityValidator val;
	ActivityList list;
	ActivityStore ctr{ rep,val,list };
	ctr.addActivity("z", "z", "z", 6);
	ctr.addActivity("b", "a", "z", 60);
	ctr.addActivity("c", "a", "z", 600);
	ctr.addToList2("z");
	ctr.addToList2("b");
	ctr.addToList2("c");
	assert(ctr.getList().size() == 3);

	string file = "date";
	ctr.saveList(file);
	std::ifstream fin("date.csv");
	string title;
	string description;
	string type;
	int duration;
	for (auto activity : ctr.getAll2()) {
		fin >> title >> description >> type;
		fin.get();
		fin >> duration;
		Activity aux(title, description, type, duration);
		if (!(aux == activity)) assert(false);
	}
	assert(true);

	ctr.emptyList();
	assert(ctr.getList().size() == 0);

	ctr.generateList(5);
	assert(ctr.getList().size() == 3);
}


void testUndo() {
	string a = randomAlpha(10);
	ActivityRepo rep;
	ActivityValidator val;
	ActivityList list;
	ActivityStore ctr{ rep,val,list };
	ctr.addActivity("a", "a", "a", 10);
	ctr.addActivity("b", "b", "b", 10);
	ctr.addActivity("c", "c", "c", 10);
	ctr.undoAdd();
	assert(ctr.getAll2().size() == 2);
	ctr.modifyActivity(ctr.getAll2().at(1), "d", "d", 20);
	ctr.modifyActivity(ctr.getAll2().at(0), "d", "d", 20);
	ctr.undoModify();
	assert(ctr.getAll2().at(0).getDuration() == 10);
	assert(ctr.getAll2().at(1).getDuration() == 20);
	ctr.removeActivity(ctr.getAll2().at(1));
	ctr.undoDelete();
	assert(ctr.getAll2().size() == 2);
	
}

void testCtr() {
	testAdd();
	testRmv();
	testModify2();
	testSort();
	testFilter();
	testList();
	testUndo();
}
