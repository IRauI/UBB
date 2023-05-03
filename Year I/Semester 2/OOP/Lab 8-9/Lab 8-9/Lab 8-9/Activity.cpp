#include "Activity.h"



bool cmpDescription(const Activity& a1, const Activity& a2) {
	return a1.getDescription() < a2.getDescription();
}

bool cmpTitle(const Activity& a1, const Activity& a2) {
	return a1.getTitle() < a2.getTitle();
}

bool cmpTypeDuration(const Activity& a1, const Activity& a2) {
	if (a1.getType() == a2.getType())
		return a1.getDuration() < a2.getDuration();
	return a1.getType() < a2.getType();
}