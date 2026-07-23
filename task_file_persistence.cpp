#include "include/task_persistence.hpp"

FilePersistence::FilePersistence(const std::string &filePath) : path(filePath) {}

void FilePersistence::save(std::vector<Task> tasks) const
{
    // Implementation for saving tasks to file
    for (auto &_ : tasks)
    {
    }
}

void FilePersistence::load()
{
    // Implementation for loading tasks from file
}