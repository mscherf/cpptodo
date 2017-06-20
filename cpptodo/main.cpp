
#include "cpptodo.h"

#include <iostream>

int main(int argc, char** argv)
{
	cpptodo::task_list list;

	list.create_task("Task 1");
	list.create_task("Task 2");

	auto lines = list.map_tasks<std::string>(cpptodo::make_oneliner);

	for (auto s : lines)
		std::cout << s << std::endl;

	char c;
	std::cin >> c;

	return 0;
}