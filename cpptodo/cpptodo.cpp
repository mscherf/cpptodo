#include "cpptodo.h"

#include <assert.h>
#include <algorithm>

namespace cpptodo
{
	task::task(task_id_t id, const std::string& synopsis) : _id(id), _synopsis(synopsis), _finished(false), _effort(0)
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

	void task::toggle_finish()
	{
		_finished = !_finished;
	}

	std::chrono::minutes task::effort() const
	{
		return _effort;
	}

	void task::set_effort(const std::chrono::minutes effort)
	{
		_effort = effort;
	}

	task_list::task_list()
	{
	}



	const task& task_list::create_task(const std::string& synopsis) noexcept	
	{
		_tasks.push_back(task{ _tasks.size(), synopsis });
		

		return _tasks[_tasks.size() - 1];
	}

	void task_list::delete_task(const task_id_t id)
	{

	}

	auto task_list::tasks() const -> const std::vector<task>&
	{
		return _tasks;
	}

	


	task* task_list::task_by_id(const task_id_t id)
	{
		if (!is_valid_id(id))
			return nullptr;
		else
			return &_tasks[id];
	}

	bool task_list::is_valid_id(const task_id_t id) const
	{
		return id < _tasks.size();
	}

	auto task_list::depends_on(const task_id_t t, const task_id_t other) const -> bool
	{
		std::vector<dependency> depts = dependents(other);

		for (const auto& d : dependents(other)) {
			if (d.from() == t)
				return true;
			else {
				if (depends_on(t, d.from()))
					return true;
			}
		}

		return false;
	}

	auto task_list::dependents(const task_id_t id) const -> std::vector<dependency>
	{
		std::vector<dependency> result;
		std::copy_if(std::begin(_deps), std::end(_deps), std::back_inserter(result), 
			[id](auto d) -> bool { return d.to() == id; });

		return result;
	}

	auto task_list::dependings(const task_id_t id) const -> std::vector<dependency>
	{
		std::vector<dependency> result;
		std::copy_if(std::begin(_deps), std::end(_deps), std::back_inserter(result),
			[id](auto d) -> bool { return d.from() == id; });

		return result;
	}

	auto task_list::add_dependency(const task_id_t from, const task_id_t to, const dependency::dependecy_type type) -> std::pair<int, dependency *>
	{
		if (!is_valid_id(from) || 
			!is_valid_id(to) || 
			std::find(std::begin(_deps), std::end(_deps), dependency{ from, to, type }) != std::end(_deps) || // Prevent duplicates
			depends_on(to, from)) // Prevent circular dependency
			return std::make_pair(-1, nullptr);

		_deps.push_back(dependency{ from, to, type });

		return std::make_pair(0, &_deps.back());
	}

	std::string make_oneliner(const task& task, const task_list* const list)
	{
		std::string result("#");
		result += std::to_string(task.id());
		result += '[';
		if (task.finished())
			result += "x] ";
		else
			result += " ] ";

		result += task.synopsis();

		if (list != nullptr) {
			result += "[";
			for (const auto& d : list->dependings(task.id())) {
				result += "->";
				result += std::to_string(d.to());
			}
			result += "]";
		}


		return result;
	}

	

	dependency::dependency(task_id_t from, task_id_t to, dependecy_type type) : _from(from), _to(to), _type(type)
	{
	}

	auto dependency::from() const -> task_id_t
	{
		return _from;
	}

	auto dependency::to() const -> task_id_t
	{
		return _to;
	}

	auto dependency::type() const -> dependecy_type
	{
		return _type;
	}

	bool dependency::operator==(const dependency & other)
	{
		return from() == other.from() &&
			to() == other.to() &&
			type() == other.type();
	}

}