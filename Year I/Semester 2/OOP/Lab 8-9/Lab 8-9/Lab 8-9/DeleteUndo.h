#pragma once
#include "ActionUndo.h"
#include "Activity.h"
#include <vector>

class DeleteUndo : public ActionUndo
{
private:
	std::vector<Activity> state;
	int size = 0;

public:
	void doUndo(ActivityRepo& repo) override;

	void addState(const std::vector<Activity>& state);

	std::vector<Activity> getLastState();

	DeleteUndo() = default;

	DeleteUndo(std::vector<Activity> activities) {
		state = activities;
	}
	virtual ~DeleteUndo() {
		state.clear();
	}

	DeleteUndo(const DeleteUndo&) = default;

	DeleteUndo& operator =(const DeleteUndo&) = default;

	DeleteUndo(DeleteUndo&&) = default;

	DeleteUndo& operator =(DeleteUndo&&) = default;
};

void testDeleteUndo();


