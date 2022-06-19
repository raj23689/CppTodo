#pragma once
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include "todo.h"
#include "utils.h"

class TodoList {
public:
  std::vector<Todo> todos;
  TodoList(){}
  // TodoList(TodoList &&) = default;
  // TodoList(const TodoList &) = default;
  // TodoList &operator=(TodoList &&) = default;
  // TodoList &operator=(const TodoList &) = default;
  void readFromFile();
  void writeToFile();
  void printTodos();

  void sortTodos();

  void addTodo(Todo todo) { todos.push_back(todo); }
  void modTodo(int index, Todo todo, bool month, bool day, bool minutes);
  void rdTodo(std::vector<int> indexes);

  void parseAdd(std::vector<std::string> input);
  void parseMod(std::vector<std::string> input);
  void parseRd(std::vector<std::string> input);

  int findIndexByDesc(std::string);

  void parseInput(std::vector<std::string> input);

  /* ~TodoList(); */

  // private:
};

// TodoList::TodoList() {}

// TodoList::~TodoList() {}

void TodoList::modTodo(int index, Todo todo, bool month, bool day,
                       bool minutes) {
  if (!isEmpty(todo.todoDesc)) {
    todos[index].todoDesc;
  }
  if (month) {
    todos[index].date.setMonth(todo.date.month);
  }
  if (day) {
    todos[index].date.setDay(todo.date.day);
  }
  if (minutes) {
    todos[index].date.minutes = todo.date.minutes;
  }
}

void TodoList::rdTodo(std::vector<int> indexes) {
  for (int i = 0; i < indexes.size(); i++) {
    if (indexes[i] > todos.size() || indexes[i] < i) {
      errorsCaught.push_back({"", 32}); // out of range
    } else {
      todos[indexes[i] - 1].empty();
    }
  }
  std::vector<Todo> keptTodos;
  for (int i = 0; i < todos.size(); i++) {
    if (!todos[i].isEmpty()) {
      keptTodos.push_back(todos[i]);
    }
  }
  todos = keptTodos;
}

int TodoList::findIndexByDesc(std::string toFind) {
  int index = 0;
  int count = 0;
  for (int i = 0; i < todos.size(); i++) {
    if (todos[i].todoDesc.find(toFind) != std::string::npos) {
      index = i + 1;
      count++;
    }
  }
  if (count == 0)
    return 0; // didnt find
  if (count != 1)
    return -1; // multiple matches
  else
    return index;
}

void TodoList::readFromFile() {
  std::ifstream input(getDir());
  std::string str;
  std::vector<Todo> todos;
  while (getline(input, str)) {
    std::vector<std::string> fLine = tokenizer(str);
    todos.push_back(Todo::createFromFileLine(fLine));
  }
  input.close();
  this->todos = todos;
}

void TodoList::writeToFile() {
  std::ofstream file(getDir());
  for (int i = 0; i < todos.size(); i++) {
    file << todos[i].toString() << std::endl;
  }
  file.close();
}

void TodoList::printTodos() {
  std::cout << "DeadLine        Tasks\n\n";
  for (int i = 0; i < todos.size(); i++) {

    std::string sep = "";
    if (PRINTSERIAL) {
      if (i < 9)
        sep += " " + std::to_string(i + 1) + ". ";
      else
        sep += std::to_string(i + 1) + ". ";
    }

    std::cout << todos[i].date.toString() << sep << todos[i].todoDesc
              << std::endl;
  }
  std::cout << std::endl;
}

void TodoList::sortTodos() {
  std::vector<Todo> sortedTodos;

  while (!todos.empty()) {
    Todo max = todos[0];
    int maxi = 0;
    int i = 1;
    for (i = 1; i < todos.size(); i++) {
      if (max.date.month < todos.at(i).date.month) {
        max = todos.at(i);
        maxi = i;
      } else if (max.date.month == todos.at(i).date.month) {
        if (max.date.day < todos.at(i).date.day) {
          max = todos.at(i);
          maxi = i;
        } else if (max.date.day == todos.at(i).date.day) {
          if (max.date.minutes < todos.at(i).date.minutes) {
            max = todos.at(i);
            maxi = i;
          }
        }
      }
    }
    sortedTodos.push_back(max);
    todos.erase(todos.begin() + maxi);
  }

  todos = sortedTodos;
}

void TodoList::parseAdd(std::vector<std::string> input) {
  if (input.size() == 0)
    errorsCaught.push_back({"", 30}); // missing arguments

  while (!input.empty()) {
    if (input[0] == LINESEPARATOR)
      input.erase(input.begin());

    bool month, day, minutes;
    Todo todo = Todo::createFromInputLine(input, month, day, minutes);
    addTodo(todo);
  }
}

void TodoList::parseMod(std::vector<std::string> input) {
  if (input.size() == 0)
    errorsCaught.push_back({"", 30}); // missing arguments

  while (!input.empty()) {
    if (input[0] == LINESEPARATOR)
      input.erase(input.begin());

    int toModIndex = 0;
    bool validIndex = false;
    bool indexExists = false;
    try {
      toModIndex = std::stoi(input[0]);
      input.erase(input.begin());
      indexExists = true;
      validIndex = toModIndex >= 1 && toModIndex <= todos.size();
    } catch (const std::exception &e) {
      errorsCaught.push_back({"", 31}); // missing index arg
    }

    if (validIndex) {
      bool month, day, minutes;
      Todo todo = Todo::createFromInputLine(input, month, day, minutes);
      modTodo(toModIndex - 1, todo, month, day, minutes);
    }
    if (!validIndex && indexExists)
      errorsCaught.push_back({"", 32}); // index out of range

    // clear input untill next separator
    if (!validIndex)
      while (!input.empty() && input[0] != LINESEPARATOR)
        input.erase(input.begin());
  }
}

void TodoList::parseRd(std::vector<std::string> input) {
  if (input.size() == 0)
    errorsCaught.push_back({"", 30}); // missing arguments

  std::vector<int> indexesToDelete;

  while (!input.empty()) {
    if (input[0] == LINESEPARATOR)
      input.erase(input.begin());

    // last item if size==1 || input[1]==LINESEP
    bool lastItem = input.size() == 1;
    if (!lastItem)
      lastItem = input[1] == LINESEPARATOR;

    int index = 0;
    if (lastItem) {
      if (getArray(input[0], indexesToDelete)) {
        input.erase(input.begin());
      } else if (toInt(input[0], index)) {
        indexesToDelete.push_back(index);
        input.erase(input.begin());
      } else {
        lastItem = false;
      }
    }
    if (!lastItem) {
      std::string toFind = "";
      while (!input.empty() && input[0] != LINESEPARATOR) {
        toFind += input[0];
        input.erase(input.begin());
        if (!input.empty()) {
          if (input[0] != LINESEPARATOR)
            toFind += " ";
        }
      }
      index = findIndexByDesc(toFind);
      if (index == 0)
        errorsCaught.push_back({"", 34}); // couldnt find this task;
      if (index == -1)
        errorsCaught.push_back(
            {"Warning: There are multiple matching tasks for \"" + toFind +
                 "\"!\n         Please be more specific!\n",
             0});
      if (index > 0)
        indexesToDelete.push_back(index);
    }
  }

  rdTodo(indexesToDelete);
}

void TodoList::parseInput(std::vector<std::string> input) {
  std::string cmd;
  if (!input.empty()) {
    cmd = input.at(0);
    input.erase(input.begin());
  } else
    cmd = "";

  if (cmd == "q" || cmd == "quit" || cmd == "exit" || cmd == "-q" ||
      cmd == "--quit" || cmd == "--exit")
    exit(0);

  else if (cmd == "h" || cmd == "help" || cmd == "-h" || cmd == "--help")
    errorsCaught.push_back({"", 100}); // printCommandList();

  else if (cmd == "a" || cmd == "add" || cmd == "-a" || cmd == "--add")
    parseAdd(input);

  else if (cmd == "r" || cmd == "rem" || cmd == "-r" || cmd == "--rem" ||
           cmd == "rm" || cmd == "remove" || cmd == "--rm" || cmd == "--remove")
    parseRd(input);

  else if (cmd == "m" || cmd == "mod" || cmd == "-m" || cmd == "--mod")
    parseMod(input);

  else if (cmd == "s" || cmd == "sort" || cmd == "-s" || cmd == "--sort")
    sortTodos();

  else if (cmd != "")
    errorsCaught.push_back(
        {"",
         101}); // "Unknown command, type \"h\" or \"help\" for command list\n"
}
