#include <string>

struct Task
{
    int id{};
    std::string title;
    bool completed{};
    std::string created_at;
};