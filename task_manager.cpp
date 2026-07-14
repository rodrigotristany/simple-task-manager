#include <algorithm>
#include <charconv>
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <optional>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

#include "task_manager.hpp"

TaskManager::TaskManager() : next_id_{1} {}

void TaskManager::add_task(const std::string &title)
{
    if (title.empty())
    {
        std::cout << "Error: Task title cannot be empty." << std::endl;
        return;
    }

    tasks_.push_back(Task{
        next_id_++,
        title,
        false,
        current_time_string()});

    std::cout << "Task added successfully." << std::endl;
}

void TaskManager::list_tasks() const
{
    if (tasks_.empty())
    {
        std::cout << "No tasks available.\n";
        return;
    }

    for (const auto &task : tasks_)
    {
        std::cout
            << '[' << task.id << ']'
            << '[' << (task.completed ? 'x' : ' ') << ']'
            << task.title
            << " (created: " << task.created_at << ") \n";
    }
}

void TaskManager::mark_done(int id)
{
    auto task = find_task_by_id(id);

    if (!task)
    {
        std::cout << "Task not found.\n";
        return;
    }

    task->get().completed = true;
    std::cout << "Task marked as done.\n";
}

void TaskManager::remove_task(int id)
{
    auto old_size = tasks_.size();

    tasks_.erase(
        std::remove_if(tasks_.begin(), tasks_.end(),
                       [id](const Task &task)
                       {
                           return task.id == id;
                       }),
        tasks_.end());

    if (tasks_.size() < old_size)
    {
        std::cout << "Task removed successfully.\n";
    }
    else
    {
        std::cout << "Task not found.\n";
    }
}

void TaskManager::find_tasks(std::string_view keyword) const
{
    bool found = false;

    for (const auto &task : tasks_)
    {
        if (task.title.find(keyword) != std::string::npos)
        {
            std::cout
                << '[' << task.id << ']'
                << '[' << (task.completed ? 'x' : ' ') << ']'
                << task.title
                << " (created: " << task.created_at << ") \n";
            found = true;
        }
    }

    if (!found)
    {
        std::cout << "No tasks found matching the keyword.\n";
    }
}

void TaskManager::save_to_file(const std::filesystem::path &file_path) const
{
    std::filesystem::create_directories(file_path.parent_path());
    std::ofstream out(file_path);

    if (!out)
    {
        std::cout << "Failed to save tasks. \n";
        return;
    }

    out << next_id_ << '\n';
    out << tasks_.size() << '\n';

    for (const auto &task : tasks_)
    {
        out << task.id << '\n';
        out << task.title << '\n';
        out << task.completed << '\n';
        out << task.created_at << '\n';
    }
}

void TaskManager::load_from_file(const std::filesystem::path &file_path)
{
    std::ifstream in(file_path);

    if (!in)
        return;

    tasks_.clear();
    std::string line;

    if (!std::getline(in, line))
        return;

    auto next_id = parse_int(line);
    if (!next_id)
        return;

    next_id_ = *next_id;

    if (!std::getline(in, line))
        return;

    auto task_count = parse_int(line);
    if (!task_count)
        return;

    for (int i = 0; i < *task_count; ++i)
    {
        Task task;

        // Parse id
        if (!std::getline(in, line))
            return;
        auto id = parse_int(line);
        if (!id)
            return;
        task.id = *id;

        // Parse completed
        if (!std::getline(in, line))
            return;
        auto completed = parse_int(line);
        if (!completed)
            return;
        task.completed = *completed != 0;

        // Parse created_at
        if (!std::getline(in, task.created_at))
            return;

        // Parse title
        if (!std::getline(in, task.title))
            return;

        tasks_.push_back(std::move(task));
    }
}

void TaskManager::print_help()
{
    std::cout
        << "Commands: \n"
        << "  add <title>       - Add a new task\n"
        << "  list              - List all tasks\n"
        << "  done <id>         - Mark a task as done\n"
        << "  remove <id>       - Remove a task\n"
        << "  find <keyword>    - Find tasks by keyword\n"
        << "  help              - Show this help message\n"
        << "  exit              - Exit the application\n";
}

std::optional<std::reference_wrapper<Task>> TaskManager::find_task_by_id(int id)
{
    for (auto &task : tasks_)
    {
        if (task.id == id)
            return task;
    }
    return std::nullopt;
}

std::optional<int> TaskManager::parse_int(std::string_view text)
{
    int value{};
    auto result = std::from_chars(text.data(), text.data() + text.size(), value);
    if (result.ec != std::errc{} || result.ptr != text.data() + text.size())
        return std::nullopt;
    return value;
}

std::string TaskManager::current_time_string()
{
    using clock = std::chrono::system_clock;
    const auto now = clock::now();
    const std::time_t current = clock::to_time_t(now);
    std::tm local_tm{};
#ifdef _WIN32
    localtime_s(&local_tm, &current);
#else
    local_tm = *std::localtime(&current);
#endif
    std::ostringstream out;
    out << std::put_time(&local_tm, "%Y-%m-%d %H:%M:%S");
    return out.str();
}