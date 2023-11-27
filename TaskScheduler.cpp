#include <bits/stdc++.h>
using namespace std;

class Task {
public:
    string taskName;
    int priority;

    Task(const string& name, int prio) : taskName(name), priority(prio) {}
};

struct TaskComparator {
    bool operator()(const Task& a, const Task& b) const {
        return a.priority > b.priority; 
    }
};

class TaskScheduler {
private:
    priority_queue<Task,vector<Task>, TaskComparator> taskQueue;

public:
    void scheduleTask(const Task& task) {
        taskQueue.push(task);
        cout << "Task Scheduled: " << task.taskName << " (Priority: " << task.priority << ")\n";
    }

    Task getNextTask() {
        if (!taskQueue.empty()) {
            Task nextTask = taskQueue.top();
            taskQueue.pop();
            cout << "Next Task: " << nextTask.taskName << " (Priority: " << nextTask.priority << ")\n";
            return nextTask;
        } else {
            cout << "No tasks in the queue.\n";
            return Task("", 0); 
        }
    }

    bool isEmpty() const {
        return taskQueue.empty();
    }
};

int main() {
    TaskScheduler scheduler;
    scheduler.scheduleTask(Task("Task1", 3));
    scheduler.scheduleTask(Task("Task2", 1));
    scheduler.scheduleTask(Task("Task3", 2));
    while (!scheduler.isEmpty()) {
        Task nextTask = scheduler.getNextTask();
        cout << "Executing task: " << nextTask.taskName << "\n";this_thread::sleep_for(std::chrono::seconds(1));
    }

    return 0;
}
