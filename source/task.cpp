// this file you need to fill
// этот файл вам нужно заполнить
#include <cmath>
#include <thread>
#include "task.h"


constexpr auto PI = 3.14159265f;


inline bool isPosVectorsLessDist(float &cur_unit_distance2, float &vec_other_unit_x, float &vec_other_unit_y)
{
	return (vec_other_unit_x * vec_other_unit_x + vec_other_unit_y * vec_other_unit_y) <= cur_unit_distance2;
}


inline bool isAngleVectorsLessFovDeg(const unit& cur_unit, float &cur_unit_veclen, float &cur_unit_angle, float &vec_other_unit_x, float vec_other_unit_y)
{
	auto radian = (cur_unit.direction.x * vec_other_unit_x + cur_unit.direction.y * vec_other_unit_y) /
		(std::sqrt((cur_unit_veclen) * (vec_other_unit_x * vec_other_unit_x + vec_other_unit_y * vec_other_unit_y)));

	if (radian > 1.0) 
	{
		return (cur_unit_angle >= 0.0);
	}
	else if (radian < -1.0)
	{
		return (cur_unit_angle >= 180.0);
	}
	else
	{
		return (cur_unit_angle >= std::acos(radian) * 180.0 / PI);
	}
}

int countUnits(const unit &cur_unit, const std::vector<unit>& units)
{	
	int count = 0;
	for (auto &other_unit : units)
	{
		auto cur_unit_distance2 = cur_unit.distance * cur_unit.distance;
		auto cur_unit_veclen = cur_unit.direction.x * cur_unit.direction.x + cur_unit.direction.y * cur_unit.direction.y;
		auto cur_unit_angle = cur_unit.fov_deg / 2;

		if (&cur_unit != &other_unit)
		{
			auto vec_other_unit_x = other_unit.position.x - cur_unit.position.x;
			auto vec_other_unit_y = other_unit.position.y - cur_unit.position.y;

			if (isPosVectorsLessDist(cur_unit_distance2, vec_other_unit_x, vec_other_unit_y)
				&&
				isAngleVectorsLessFovDeg(cur_unit, cur_unit_veclen, cur_unit_angle, vec_other_unit_x, vec_other_unit_y))
			{
				count++;
			}
		}
	}
	return count;
}

void Task::checkVisible(const std::vector<unit> &input_units, std::vector<int> &result)
{
	for (auto i = 0u; i < input_units.size() / 8; ++i)
	{
		result.push_back(countUnits(input_units[8*i], input_units));
		result.push_back(countUnits(input_units[8*i + 1], input_units));
		result.push_back(countUnits(input_units[8*i + 2], input_units));
		result.push_back(countUnits(input_units[8*i + 3], input_units));
		result.push_back(countUnits(input_units[8*i + 4], input_units));
		result.push_back(countUnits(input_units[8*i + 5], input_units));
		result.push_back(countUnits(input_units[8*i + 6], input_units));
		result.push_back(countUnits(input_units[8*i + 7], input_units));
	}

	for (auto i = input_units.size() % 8; i > 0; --i)
	{
		result.push_back(countUnits(input_units[input_units.size() - i], input_units));
	}
}