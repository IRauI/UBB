#pragma once
#include <string>
#include <random> // std::default_random_engine
#include <chrono> // std::chrono::system_clock

bool has_suffix(const std::string& str, const std::string& suffix);

std::string randomAlpha(const int& length);

int randomInt(const int& maxValue) noexcept;
