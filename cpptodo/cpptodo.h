#ifndef CPPTODO_H
#define CPPTODO_H

#include <string>
#include <vector>
#include <functional>


namespace cpptodo
{
	typedef unsigned int task_id_t;

	class task
	{
	private:
		task_id_t _id;
		std::string _synopsis;
		bool _finished;

	public:
		
		task(task_id_t id, const std::string& synopsis);

		const std::string& synopsis() const;
		void set_synopsis(const std::string& synopsis);

		task_id_t id() const;

		bool finished() const;
		void set_finished(const bool finished);


	};

	std::string make_oneliner(const task& task);


	class task_list
	{
	private:
		std::vector<task> _tasks;

	public:
		task_list();

		const task& create_task(const std::string& synopsis);
		void finish_task(const task_id_t id);
		void unfinish_task(const task_id_t id);
		void set_synopsis(const task_id_t id, const std::string& synopsis);
		template <typename T>
		std::vector<T> map_tasks(std::function<T(const task&)> f);
	};

	template<typename T>
	inline std::vector<T> task_list::map_tasks(std::function<T(const task&)> f)
	{
		std::vector<T> result;
		for (auto t : _tasks)
			result.push_back(f(t));

		return result;
	}
}

#endif
