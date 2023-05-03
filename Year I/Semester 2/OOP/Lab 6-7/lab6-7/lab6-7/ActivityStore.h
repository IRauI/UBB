#pragma once

#include "Activity.h"
#include "ActivityRepo.h"
#include "Validator.h"

#include <string>
#include <vector>
#include <functional>

using std::vector;
using std::function;

class ActivityStore
{
private:
	ActivityRepo& rep;
	ActivityValidator& val;

	VectDinNewDeleteT<Activity> filter(function<bool(const Activity& a)> func) const;
public:
	ActivityStore(ActivityRepo& rep, ActivityValidator& val) noexcept : rep{ rep }, val{ val }{}

	ActivityStore(const ActivityStore& as) = delete;

	const VectDinNewDeleteT<Activity>& getAll2() noexcept {
		return rep.getAll();
	}

	void addActivity(const string& title, const string& description, const string& type, const int& duration);

	void removeActivity(const Activity& a);

	void modifyActivity(const Activity& a, const string& newDescription, const string& newType, const int& newDuration);

	VectDinNewDeleteT<Activity> sortByTitle() const;

	VectDinNewDeleteT<Activity> sortByDescription() const;

	VectDinNewDeleteT<Activity> sortByTypeDuration()const;

	VectDinNewDeleteT<Activity> filterByDescription(const string& description) const;

	VectDinNewDeleteT<Activity> filterByType(const string& type) const;

};

void testCtr();

