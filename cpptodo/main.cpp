
#include "cpptodo.h"
#include "command.h"

#include <iostream>
#include <map>
#include <numeric>
#include <conio.h>

enum command
{
	none,
	quit,
	new_task
};

std::map<char, std::function<void(cpptodo::task_list&)>> key_command_map;

int main(int argc, char** argv)
{
	cpptodo::task_list list;
	key_command_map['q'] = cpptodo::cmd_quit;
	key_command_map['n'] = cpptodo::cmd_new_task;
	key_command_map['f'] = cpptodo::cmd_toggle_finish;
	key_command_map['e'] = cpptodo::cmd_set_effort;
	key_command_map['d'] = cpptodo::cmd_new_dependcy;

	list.create_task("task0");
	list.create_task("task1");
	list.create_task("task2");

	while (true) {

		
	//auto lines = list.map_tasks<std::string>(cpptodo::make_oneliner);
		



		auto& l = list.tasks();
		std::vector<std::string> lines;
		std::transform(std::begin(l), std::end(l), std::back_inserter(lines), [list](const auto& t) -> std::string { return cpptodo::make_oneliner(t, &list); });
			
			
		for (const auto& s : lines)
			std::cout << s << std::endl;

		const auto effort = std::accumulate(std::begin(l), std::end(l), std::chrono::minutes{ 0 },
			[](auto acc, const auto& t) { return acc + t.effort(); });

		std::cout << std::string("Accumulated effort: ") <<  effort.count() << std::endl;
	
		char c;
		c = _getch();

		if (key_command_map.find(c) == key_command_map.end())
			continue;
		else
			key_command_map[c](list);
	}

	return 0;
}