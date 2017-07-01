#ifndef CPPTODO_H
#define CPPTODO_H

#include <string>
#include <vector>
#include <functional>
#include <algorithm>
#include <chrono>

namespace cpptodo
{
	typedef unsigned int task_id_t;

	class task
	{
	private:
		task_id_t _id;
		std::string _synopsis;
		bool _finished;
		std::chrono::minutes _effort;

	public:
		
		task(task_id_t id, const std::string& synopsis);

		task_id_t id() const;

		auto synopsis() const -> const std::string&;
		void set_synopsis(const std::string& synopsis);


		auto finished() const -> bool;
		void set_finished(const bool finished);
		void toggle_finish();

		auto effort() const ->std::chrono::minutes;
		void set_effort(const std::chrono::minutes effort);
	};

	

	class dependency
	{
	public:
		enum class dependecy_type { end_start };

		dependency(task_id_t from, task_id_t to, dependecy_type type);

		auto from() const->task_id_t;
		auto to() const->task_id_t;
		auto type() const->dependecy_type;

		bool operator==(const dependency& other);
	private:
		task_id_t _from;
		task_id_t _to;
		dependecy_type _type;

	};

	class task_list
	{
	private:
		std::vector<task> _tasks;
		std::vector<dependency> _deps;

	public:
		task_list();

		auto create_task(const std::string& synopsis) noexcept -> const task&;
		void delete_task(const task_id_t id);
		auto tasks() const -> const std::vector<task>&;
		auto deps() const -> const std::vector<dependency>&;
		auto task_by_id(const task_id_t id) -> task*;
		auto is_valid_id(const task_id_t id) const -> bool;

		auto depends_on(const task_id_t t, const task_id_t other) const -> bool;

		auto dependents(const task_id_t id) const -> std::vector<dependency>;
		auto dependings(const task_id_t id) const -> std::vector<dependency>;
		auto add_dependency(const task_id_t from, const task_id_t to, const dependency::dependecy_type type) -> std::pair<int, dependency*>;
		template <typename T>
		auto map_tasks(std::function<T(const task&)> f) -> std::vector<T>;
		
	};

	template<typename T>
	inline auto task_list::map_tasks(std::function<T(const task&)> f) -> std::vector<T>
	{
		std::vector<T> result;
		std::transform(_tasks.begin(), _tasks.end(), std::back_inserter(result), f);


		return result;
	}

	std::string make_oneliner(const task& task, const task_list* const list = nullptr);
}

#endif
