#pragma once

#include "observer.h"

#include <algorithm>  // For std::remove

#include "sorter.h"

void Subject::Notify(const SortEvent& event) {
  for (std::shared_ptr<Observer> observer : observers_) {
    if (observer != nullptr) {
      observer->Update(event);
    }
  }
}

void Subject::AddObserver(std::shared_ptr<Observer> observer) {
  observers_.push_back(observer);
}

void Subject::RemoveObserver(std::shared_ptr<Observer> observer) {
  // Remove the observer pointer from the vector
  observers_.erase(std::remove(observers_.begin(), observers_.end(), observer),
                   observers_.end());
}