#include "Utils.h"
#include <chrono>

std::default_random_engine engine{ static_cast<unsigned int>(
        std::chrono::system_clock::now().time_since_epoch().count()) };

int Utils::GetRandomNumber(int max)
{
  std::uniform_int_distribution<int> int_distribution(max);
  return int_distribution(engine);
}

int Utils::GetRandomNumber(int min, int max)
{
  std::uniform_int_distribution<int> int_distribution(min, max);
  return int_distribution(engine);
}
