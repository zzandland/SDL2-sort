#pragma once

#include <memory>
#include <vector>

#include "event.h"

class Sorter;

class Observer {
 public:
  virtual ~Observer() = default;

  // Update signature changed to include the event
  virtual void Update(const SortEvent& event) = 0;
};

class Subject {
 protected:
  std::vector<std::shared_ptr<Observer>> observers_;

 public:
  virtual ~Subject() = default;

  // Notify signature changed to pass the event
  void Notify(const SortEvent& event);

  // Using raw pointers for attach/detach
  void AddObserver(std::shared_ptr<Observer> observer);
  void RemoveObserver(std::shared_ptr<Observer> observer);
};
