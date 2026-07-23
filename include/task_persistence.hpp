// persistence.hpp
#pragma once

#include <vector>

#include "task.hpp"

class TaskPersistence
{
public:
    virtual ~TaskPersistence() = default;
    virtual void load() = 0;
    virtual void save(std::vector<Task> tasks) const = 0;
};

class DatabasePersistence : public TaskPersistence
{
public:
    DatabasePersistence(const std::string &dbPath) : path(dbPath) {}
    void save(std::vector<Task> tasks) const override;
    void load() override;

private:
    std::string path;
};

class FilePersistence : public TaskPersistence
{
public:
    FilePersistence(const std::string &filePath) : path(filePath) {}
    void save(std::vector<Task> tasks) const override;
    void load() override;

private:
    std::string path;
};