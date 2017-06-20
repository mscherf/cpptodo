#include "cpptodo.h"

#include <assert.h>

namespace cpptodo
{
	task::task(task_id_t id, const std::string& synopsis) : _id(id), _synopsis(synopsis), _finished(false)
	{
	}

	const std::string & task::synopsis() const
	{
		return _synopsis;
	}

	void task::set_synopsis(const std::string& synopsis)
	{
		_synopsis = synopsis;
	}

	task_id_t task::id() const
	{
		return _id;
	}

	bool task::finished() const
	{
		return _finished;
					
	}

	void task::set_finished(const bool finished)
	{
		_finished = finished;
	}

	task_list::task_list()
	{
	}

	const task& task_list::create_task(const std::string& synopsis)
	{
		_tasks.push_back(task(_tasks.size(), synopsis));

		return _tasks[_tasks.size() - 1];
	}

	void task_list::finish_task(const task_id_t id)
	{
		assert(id < _tasks.size());

		_tasks[id].set_finished(true);
	}

	void task_list::unfinish_task(const task_id_t id)
	{
		assert(id < _tasks.size());

		_tasks[id].set_finished(false);
	}

	void task_list::set_synopsis(const task_id_t id, const std::string & synopsis)
	{
		assert(id < _tasks.size());

		_tasks[id].set_synopsis(synopsis);
	}

	std::string make_oneliner(const task& task)
	{
		std::string result("#");
		result += std::to_string(task.id());
		result += '[';
		if (task.finished())
			result += "x] ";
		else
			result += " ] ";

		result += task.synopsis();

		return result;
	}

}