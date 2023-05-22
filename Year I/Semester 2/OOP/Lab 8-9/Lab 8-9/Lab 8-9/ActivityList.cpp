#include "ActivityList.h"

void ActivityList::clearList() noexcept
{
	list.clear();
}

vector<Activity> ActivityList::getList()
{
	return list;
}

void ActivityList::generateList(vector<Activity> allActivities, const int& number)
{
	vector<int> pozitions;
	int activityPoz = 0;
	for (int i = 1; i <= number && i <= (int)allActivities.size(); ++i)
	{
		do {
			activityPoz = randomInt((int)allActivities.size() + 1) - 1;
		} while (std::count(pozitions.begin(), pozitions.end(), activityPoz) != 0);
		pozitions.push_back(activityPoz);
		addToList(allActivities.at(activityPoz));
	}
}

void ActivityList::addToList(const Activity& a)
{
	list.push_back(a);
}

void ActivityList::saveList(string file)
{
	std::ofstream fout(file);
	for (auto activity : list) {
		fout << activity << '\n';
	}
	fout.close();
}

