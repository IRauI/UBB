#pragma once

#include "Activity.h"
#include "ActivityRepo.h"
#include "Validator.h"
#include "AddUndo.h"
#include "ModifyUndo.h"
#include "DeleteUndo.h"
#include "Utils.h"
#include "ActivityList.h"

#include <string>
#include <vector>
#include <functional>
#include <fstream>

using std::vector;
using std::function;

class ActivityStore
{
private:
	ActivityRepo& rep;
	ActivityValidator& val;
	ActivityList& lists;

	vector<ActionUndo*> undoList;

	AddUndo aUndo;
	ModifyUndo mUndo;
	DeleteUndo dUndo;

	vector<Activity> filter(function<bool(const Activity& a)> func) const;
public:
	ActivityStore(ActivityRepo& rep, ActivityValidator& val, ActivityList& lists) noexcept : rep{ rep }, val{ val }, lists{ lists }{}

	ActivityStore(const ActivityStore& as) = delete;

	const vector<Activity>& getAll2() noexcept {
		return rep.getAll();
	}

	void addActivity(const string& title, const string& description, const string& type, const int& duration);

	void removeActivity(const Activity& a);

	void modifyActivity(const Activity& a, const string& newDescription, const string& newType, const int& newDuration);

	vector<Activity> sortByTitle() const;

	vector<Activity> sortByDescription() const;

	vector<Activity> sortByTypeDuration()const;

	vector<Activity> filterByDescription(const string& description) const;

	vector<Activity> filterByType(const string& type) const;

	void undoAdd();

	void undoDelete();

	void undoModify();

	void undo();

	void addToList2(const string& title);

	vector<Activity> getList() {
		return lists.getList();
	}

	void emptyList();

	void saveList(string& file);

	void generateList(const int& noActivities);

};

void testCtr();

