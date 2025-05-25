#pragma once

#include <memory>
#include <vector>

#include "event.h"

extern SDL_sem *event_sem;

class Observer {
 public:
  virtual ~Observer() = default;

  // Update signature changed to include the event
  virtual void Update(SortEvent event) = 0;
};

class Observable {
 protected:
  std::vector<std::shared_ptr<Observer>> observers_;

 public:
  virtual ~Observable() = default;

  // Notify signature changed to pass the event
  void Notify(SortEvent *event);

  // Using raw pointers for attach/detach
  void AddObserver(std::shared_ptr<Observer> observer);
  void RemoveObserver(std::shared_ptr<Observer> observer);
};
