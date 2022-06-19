#pragma once
#include "date.h"

class Todo {
public:
  std::string todoDesc;
  Date date;

  Todo(std::string todoDesc, Date date) {
    this->todoDesc = todoDesc;
    this->date = date;
  }

  std::string toString() { return date.toString() + todoDesc; }

  void empty();
  bool isEmpty();

  static Todo createFromFileLine(std::vector<std::string> vec);
  static Todo createFromInputLine(std::vector<std::string> &input, bool &month,
                                  bool &day, bool &minutes);
  // Todo();
  // Todo(Todo &&) = default;
  // Todo(const Todo &) = default;
  // Todo &operator=(Todo &&) = default;
  // Todo &operator=(const Todo &) = default;
  // ~Todo();

  // private:
};

// Todo::Todo()
// {
// }

// Todo::~Todo()
// {
// }

void Todo::empty() {
  todoDesc = "";
  Date empty;
  date = empty;
}

bool Todo::isEmpty() {
  if (todoDesc == "")
    return true;
  else
    return false;
}

Todo Todo::createFromFileLine(std::vector<std::string> vec) {
  Date date;
  std::string todoDesc;
  int dateCounter = 0;
  while (!vec.empty()) {

    if (dateCounter < 2 && date.setMonthDay(vec[0]))
      vec.erase(vec.begin());

    else if (dateCounter < 2 && date.setHourMin(vec[0]))
      vec.erase(vec.begin());

    else {
      todoDesc += vec[0] + " ";
      vec.erase(vec.begin());
    }

    dateCounter++;
  }
  Todo todo(todoDesc, date);
  return todo;
}

Todo Todo::createFromInputLine(std::vector<std::string> &input, bool &month,
                               bool &day, bool &minutes) {
  std::string todoDesc = "";
  Date date;
  month = false;
  day = false;
  minutes = false;
  while (!input.empty() && input[0] != LINESEPARATOR) {

    if (input[0] == "due" || input[0] == "--due" || input[0] == "-d") {
      input.erase(input.begin());
      int dateCounter = 0;

      while (!input.empty() && dateCounter < 4 && input[0] != LINESEPARATOR) {

        if (date.setHourMin(input[0])) {
          dateCounter += 2;
          minutes = true;
        } else if (date.setMonthDay(input[0])) {
          dateCounter += 2;
          month = true;
          day = true;
        } else if (date.setMonth(input[0])) {
          dateCounter += 1;
          month = true;
        } else if (date.setDay(input[0])) {
          dateCounter += 1;
          day = true;
        }

        // else todoDesc += input[0] + " ";
        else {
          std::string errMsg =
              "Warning: " + input[0] + " couldn't be parsed as a Date!\n";
          errorsCaught.push_back({errMsg, 0});
        }
        input.erase(input.begin());
      }
    } else {
      todoDesc += input[0] + " ";
      input.erase(input.begin());
    }
  }
  Todo todo(todoDesc, date);
  todo.date.check();
  todo.date.fix();
  return todo;
}
