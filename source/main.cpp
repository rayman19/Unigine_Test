// THIS FILE IS STUB FOR INPUT AND OUTPUT DATA
// DO NOT MODIFICATE IT - IT`S PART OF ANOTHER PROJECT

// это файл-заглушка, для демонстрации как метод будет вызван.
// не модифицируйте его - возможно это часть другого проекта

#include <iostream>
#include <fstream>

#include "task.h"

#ifdef _DEBUG
#include <chrono> 
#endif // _DEBUG


int main()
{
	std::vector<unit> units;
	std::vector<int> result;

	int count = 0;

	// input
	std::ifstream in("input.txt");
	if (in.is_open())
	{
		in >> count;
		unit t;
		for (int i = 0; i < count; i++)
		{
			in >> t.position.x >> t.position.y;
			in >> t.direction.x >> t.direction.y;
			in >> t.fov_deg >> t.distance;
			units.push_back(t);
		}
		in.close();
	}


#ifdef _DEBUG
	auto begin = std::chrono::steady_clock::now();
#endif // _DEBUG

	Task::checkVisible(units, result);

#ifdef _DEBUG
	auto end = std::chrono::steady_clock::now();

	auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
	std::cout << "The time: " << elapsed_ns.count() / 1000 << " ns\n";
#endif // _DEBUG


	// output
	std::ofstream out;
	out.open("output.txt");
	if (out.is_open())
	{
		for (int i = 0; i < count; i++)
			out << result[i] << std::endl;
		out.close();
	}

	return 0;
}
