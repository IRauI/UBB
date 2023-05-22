#include "AddUndo.h"
#include <sstream>
#include <assert.h>

void AddUndo::doUndo(ActivityRepo& repo){
	repo.setAll(state);
}

void AddUndo::addState(const std::vector<Activity>& s) {
	state = s;
}

std::vector<Activity> AddUndo::getLastState()
{
	return state;
}


void testAddUndo() {
}