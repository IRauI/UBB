#pragma once
#include "Activity.h"
#include "ActivityRepo.h"
#include <vector>
class ActionUndo
{
public:
	virtual void doUndo(ActivityRepo& repo) = 0;
};

