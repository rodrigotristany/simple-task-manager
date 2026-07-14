// task_manager.hpp
#pragma once

#include <string>
#include <string_view>
#include <filesystem>
#include <optional>
#include <vector>

#include "task.hpp"

class TaskManager
{
public:
    void add_task(const std::string &title);
    void list_tasks() const;
    void mark_done(int id);
    void remove_task(int id);
    void find_tasks(std::string_view keyword) const;
    void save_to_file(const std::filesystem::path &file_path) const;
    void load_from_file(const std::filesystem::path &file_path);
    static void print_help();

private:
    std::optional<std::reference_wrapper<Task>> find_task_by_id(int id);
    static std::optional<int> parse_int(std::string_view text);
    static std::string current_time_string();

private:
    std::vector<Task> tasks_;
    int next_id_;
};