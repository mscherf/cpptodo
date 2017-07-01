#include "command.h"

#include <iostream>
#include <tuple>
#include <assert.h>

namespace cpptodo
{

	template<typename T>
	auto prompt_value(const std::string& prompt)
	{
		T result;
		std::cout << prompt;
		std::cin >> result;
		return result;
	}

	template<>
	auto prompt_value<std::string>(const std::string& prompt)
	{
		std::string result;
		std::cout << prompt;
		std::getline(std::cin, result);
		return result;
	}

	std::pair<int, task_id_t> prompt_task_id(const task_list& list, const std::string& prompt)
	{
		std::cout << prompt;
		std::string input;
		
		while (true) {
			std::getline(std::cin, input);
			if (input == "c")
				return std::make_pair(-1, 0);

			task_id_t id;
			try {
				id = std::stoi(input);
			}
			catch (...) {
				std::cout << "You entered an invalid number. Please try again: ";
				continue;
			}

			if (!list.is_valid_id(id)) {
				std::cout << "You entered an invalid task id. Please try again: ";
				continue;
			}

			return std::make_pair(0, id);
		}
	}


	void cmd_quit(task_list & list)
	{
		exit(0);
	}

	void cmd_new_task(task_list & list)
	{
		std::string name = "";

		while (name.empty()) {
			name = prompt_value<std::string>("Enter synopsis of new task: ");
		}

		list.create_task(name);
		return;
	}

	void cmd_toggle_finish(task_list& list)
	{
		int rc;
		task_id_t id;
		std::tie(rc, id) = prompt_task_id(list);

		task* t = list.task_by_id(id);
		assert(t != nullptr);
		
		t->toggle_finish();
	}

	void cmd_set_effort(task_list& list)
	{
		int rc;
		task_id_t id;
		std::tie(rc, id) = prompt_task_id(list);

		if (rc != 0)
			return;

		task* t = list.task_by_id(id);
		assert(t != nullptr);

		int effort = prompt_value<int>("Enter effort for the task in minutes: ");
		t->set_effort(std::chrono::minutes{ effort });
	}

	void cmd_new_dependcy(task_list & list)
	{
		int rc{ 0 };
		task_id_t id_from{ 0 }, id_to{ 0 };
		std::tie(rc, id_from) = prompt_task_id(list, "Enter id of the task you want to add the dependency to: ");
		if (rc != 0)
			return;

		std::tie(rc, id_to) = prompt_task_id(list, "Enter id of the task you want the task to depend on: ");
		if (rc != 0)
			return;

		dependency* d;
		std::tie(rc, d) = list.add_dependency(id_from, id_to, dependency::dependecy_type::end_start);
		if (rc != 0)
			std::cout << "Couldn't add dependency!" << std::endl;
	}

}