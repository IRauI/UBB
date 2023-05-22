#pragma once
#include "ActionUndo.h"
#include "Activity.h"
#include <vector>

class AddUndo : public ActionUndo
{
private:
	std::vector<Activity> state;
	int size = 0;
	
public:
	void doUndo(ActivityRepo& repo) override;

	void addState(const std::vector<Activity>& state);

	std::vector<Activity> getLastState();

	AddUndo() = default;

	AddUndo(std::vector<Activity> activities) {
		state = activities;
	}
	virtual ~AddUndo() {
		state.clear();
	}

	AddUndo(const AddUndo&) = default;

	AddUndo& operator =(const AddUndo&) = default;

	AddUndo(AddUndo&&) = default;

	AddUndo& operator =(AddUndo&&) = default;
};

void testAddUndo();

