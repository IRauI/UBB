#include "Utils.h"

bool has_suffix(const std::string& str, const std::string& suffix)
{
	return str.size() >= suffix.size() && str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
}

std::string randomAlpha(const int& length){
	auto seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::string letters = "aeiouybcdfghjklmnpqrstvwxz";
	std::shuffle(letters.begin(), letters.end(), std::default_random_engine(static_cast<unsigned int>(seed)));
	return letters.substr(0, length);
}

int randomInt(const int& maxValue) noexcept{
	if (maxValue <= 0)
		return 1;
	if (maxValue > 10) {
		return rand() % (maxValue - 10) + 10;
	}
	return rand() % (maxValue - 1) + 1;
}