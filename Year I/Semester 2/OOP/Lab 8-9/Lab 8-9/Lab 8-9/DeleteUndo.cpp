#include "DeleteUndo.h"
#include <sstream>
#include <assert.h>

void DeleteUndo::doUndo(ActivityRepo& repo) {
	repo.setAll(state);
}

void DeleteUndo::addState(const std::vector<Activity>& s) {
	state = s;
}

std::vector<Activity> DeleteUndo::getLastState() {
	return state;
}

void testDeleteUndo() {
}