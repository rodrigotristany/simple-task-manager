#include <filesystem>
#include <iostream>
#include "task_manager.hpp"

int main()
{
    const std::filesystem::path data_file = "data/tasks.txt";

    TaskManager manager;
    manager.load_from_file(data_file);

    std::cout << "Modern C++ Task Manager\n";
    std::cout << "Type 'help' to see available commands.\n\n";

    std::string line;

    while (true)
    {
        std::cout << "> ";

        if (!std::getline(std::cin, line))
            break;

        if (line.empty())
            continue;

        std::istringstream input(line);

        std::string command;
        input >> command;

        if (command == "add")
        {
            std::string title;
            std::getline(input >> std::ws, title);
            manager.add_task(title);
        }
        else if (command == "list")
        {
            manager.list_tasks();
        }
        else if (command == "done")
        {
            std::string id_text;
            input >> id_text;

            auto id = manager.parse_int(id_text);
            if (!id)
                std::cout << "Invalid task ID.\n";
            else
                manager.mark_done(*id);
        }
        else if (command == "remove")
        {
            std::string id_text;
            input >> id_text;

            auto id = manager.parse_int(id_text);
            if (!id)
                std::cout << "Invalid task ID.\n";
            else
                manager.remove_task(*id);
        }
        else if (command == "find")
        {
            std::string keyword;
            std::getline(input >> std::ws, keyword);
            if (keyword.empty())
                std::cout << "Please provide a search keyword.\n";
            else
                manager.find_tasks(keyword);
        }
        else if (command == "help")
        {
            manager.print_help();
        }
        else if (command == "exit")
        {
            manager.save_to_file(data_file);
            std::cout << "Tasks saved. Goodbye.\n";
            break;
        }
        else
        {
            std::cout << "Unknown command. Type 'help' to see available commands.\n";
        }

        std::cout << '\n';
    }

    return 0;
}