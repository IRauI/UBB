#pragma once
#include "ActionUndo.h"
#include "Activity.h"
#include <vector>

class ModifyUndo : public ActionUndo
{
private:
	std::vector<Activity> state;
	int size = 0;

public:
	void doUndo(ActivityRepo& repo) override;

	void addState(const std::vector<Activity>& state);

	std::vector<Activity> getLastState();

	ModifyUndo() = default;

	ModifyUndo(std::vector<Activity> activities) {
		state = activities;
	}
	virtual ~ModifyUndo() {
		state.clear();
	}

	ModifyUndo(const ModifyUndo&) = default;

	ModifyUndo& operator =(const ModifyUndo&) = default;

	ModifyUndo(ModifyUndo&&) = default;

	ModifyUndo& operator =(ModifyUndo&&) = default;
};

void testModifyUndo();


