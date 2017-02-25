#pragma once

#include <Command.hpp>

#include <queue>

class CommandQueue
{
public:
  void        push(const Command& command);
  Command     pop();
  bool        isEmpty();

private:
  std::queue<Command> mQueue;
};