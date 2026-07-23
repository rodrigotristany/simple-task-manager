#include "include/task_persistence.hpp"

DatabasePersistence::DatabasePersistence(const std::string& dbPath) : path(dbPath)
{
    // Create db if doesn't exist
}

void DatabasePersistence::save(std::vector<Task> tasks) const
{
    // Implementation for saving tasks to database
    for (auto &_ : tasks)
    {
    }
}

void DatabasePersistence::load()
{
    // Implementation for loading tasks from database
}