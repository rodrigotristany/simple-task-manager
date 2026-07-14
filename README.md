# simple-task-manager
Console application task manager developed in c++

Based code imported from Ayman Alheraki's book titled "Modern C++ from Zero to Professional"

## Version 0.1 (before the improvements)
### Architecture
- Task class that store a simple task (id, completed, created_at, title).
- TaskManager class design to execute actions like add task, list tasks, mark tasks as done, delete tasks, search tasks, save tasks and load tasks.
- main.cpp: the interactive loop.

### Data persistence 
The tasks are stored in a single file, using this sample schema:
```
4
3
1
0
2026-03-20 12:00:01
Write chapter 43
2
1
2026-03-20 12:05:13
Review task manager design
3
0
2026-03-20 12:07:54
Test file loading
```

Where the first line is the next available ID; second line is the number of tasks. Then four lines per task: ID, completion flag, creation time and title.

### How to build it (Fedora)
```bash
> g++ -std=gnu++17 -Wall -Wextra -Wpedantic main.cpp task_manager.cpp task_manager.hpp task.hpp -o build/task_manager
```