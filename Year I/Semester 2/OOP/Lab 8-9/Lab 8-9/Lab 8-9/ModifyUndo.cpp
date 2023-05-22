#include "ModifyUndo.h"
#include <sstream>
#include <assert.h>

void ModifyUndo::doUndo(ActivityRepo& repo) {
	repo.setAll(state);
}

void ModifyUndo::addState(const std::vector<Activity>& s) {
	state = s;
}

std::vector<Activity> ModifyUndo::getLastState()
{
	return state;
}

void testModifyUndo() {
}