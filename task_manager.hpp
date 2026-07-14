#include <string>
#include <string_view>
#include <filesystem>

class TaskManager
{
public:
    void add_task(const std::string& title);
    void list_tasks() const;
    void mark_done(int id);
    void remove_task(int id);
    void find_tasks(std::string_view keyword) const;
    void save_to_file(const std::filesystem::path& file_path) const;
    void load_from_file(const std::filesystem::path& file_path);
};