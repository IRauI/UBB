#pragma once
#include "Activity.h"
#include "Utils.h"
#include <vector>
#include "Validator.h"
#include <fstream>

using std::vector;

class ActivityList
{
private:
	vector<Activity> list;
public:
	vector<Activity> getList();

	void clearList() noexcept;

	void generateList(vector<Activity> allActivities, const int& number);

	void addToList(const Activity& a);

	void saveList(string file);
};

