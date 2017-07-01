#ifndef COMMAND_H
#define COMMAND_H

#include <memory>


#include "cpptodo.h"

namespace cpptodo
{
	std::pair<int, task_id_t> prompt_task_id(const task_list& list, const std::string& prompt = "Enter a valid task id (or c to cancel): ");

	void cmd_quit(task_list& list);
	void cmd_new_task(task_list& list);
	void cmd_toggle_finish(task_list& list);
	void cmd_set_effort(task_list& list);
	void cmd_new_dependcy(task_list& list);
};
#endif
