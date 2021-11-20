#include <iostream>
using namespace std;

#include <map>
#include <tuple>
#include <string>
#include <vector>
#include <utility>

using namespace std;

//#ifndef WEEK1_TEAMTASKS_H
//#define WEEK1_TEAMTASKS_H
//
//
enum class TaskStatus {
	NEW,          // новая
	IN_PROGRESS,  // в разработке
	TESTING,      // на тестировании
	DONE          // завершена
};

// Объявляем тип-синоним для map<TaskStatus, int>,
// позволяющего хранить количество задач каждого статуса
using TasksInfo = map<TaskStatus, int>;

class TeamTasks {
public:
	// Получить статистику по статусам задач конкретного разработчика
	const TasksInfo& GetPersonTasksInfo(const string& person) const {
		return tasksByName.at(person);
	}

	// Добавить новую задачу (в статусе NEW) для конкретного разработчитка
	void AddNewTask(const string& person) {
		tasksByName[person][TaskStatus::NEW] += 1;
	}

	// Обновить статусы по данному количеству задач конкретного разработчика,
	// подробности см. ниже
	tuple<TasksInfo, TasksInfo> PerformPersonTasks(const string& person, int task_count) {
		//	if (tasksByName.find(person) == tasksByName.end()) {
//		return make_tuple(TasksInfo(), TasksInfo());
//	}

		TasksInfo updatedTasks, notUpdatedTasks;

		auto personTasks = tasksByName[person];

		for (auto status = TaskStatus::NEW; status != TaskStatus::DONE; status= Next(status)) {
			updatedTasks[status] = min(task_count, personTasks[status]);
			task_count -= personTasks[status];
		}

		for (auto status = TaskStatus::NEW; status != TaskStatus::DONE; status= Next(status)) {
			notUpdatedTasks[status] = personTasks[status] - updatedTasks[status];
			personTasks[status] += updatedTasks[status] - updatedTasks[Next(status)];
		}

		personTasks[TaskStatus::DONE] += updatedTasks[TaskStatus::DONE];
		DeleteZeros(updatedTasks);
		DeleteZeros(notUpdatedTasks);
		DeleteZeros(personTasks);

		return {updatedTasks, notUpdatedTasks};
	}

private:
	map<string, TasksInfo> tasksByName;

	TaskStatus Next(TaskStatus taskStatus) {
		return static_cast<TaskStatus>(static_cast<int>(taskStatus) + 1);
	}

	void DeleteZeros(TasksInfo& tasksInfo) {
		vector<TaskStatus> toDelete;
		for (auto [status, taskCount] : tasksInfo) {
			if (taskCount == 0) toDelete.push_back(status);
		}

		for (auto& status: toDelete) {
			tasksInfo.erase(status);
		}
	}
};

//#endif //WEEK1_TEAMTASKS_H

void PrintTasksInfo(TasksInfo tasks_info) {
	cout << tasks_info[TaskStatus::NEW] << " new tasks" <<
		 ", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress" <<
		 ", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested" <<
		 ", " << tasks_info[TaskStatus::DONE] << " tasks are done" << endl;
}

int main4() {
	TeamTasks tasks;
	tasks.AddNewTask("Ilia");
	for (int i = 0; i < 3; ++i) {
		tasks.AddNewTask("Ivan");
	}
	cout << "Ilia's tasks: ";
	PrintTasksInfo(tasks.GetPersonTasksInfo("Ilia"));
	cout << "Ivan's tasks: ";
	PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));

	TasksInfo updated_tasks, untouched_tasks;

	tie(updated_tasks, untouched_tasks) =
			tasks.PerformPersonTasks("Ivan", 2);
	cout << "Updated Ivan's tasks: ";
	PrintTasksInfo(updated_tasks);
	cout << "Untouched Ivan's tasks: ";
	PrintTasksInfo(untouched_tasks);

	tie(updated_tasks, untouched_tasks) =
			tasks.PerformPersonTasks("Ivan", 2);
	cout << "Updated Ivan's tasks: ";
	PrintTasksInfo(updated_tasks);
	cout << "Untouched Ivan's tasks: ";
	PrintTasksInfo(untouched_tasks);

	return 0;
}



