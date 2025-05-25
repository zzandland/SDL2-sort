#include "observer.h"

#include <algorithm>

void Observable::Notify(SortEvent *event) {
  SDL_SemWait(event_sem);

  SDL_Event sdl_event;
  sdl_event.type = SDL_USEREVENT;
  sdl_event.user.data1 = static_cast<void *>(event);
  sdl_event.user.data2 = nullptr;

  if (SDL_PushEvent(&sdl_event) < 0) {
    // Handle the error if needed, e.g., log it
    // For now, we just print an error message
    SDL_Log("Failed to push event: %s", SDL_GetError());
    SDL_SemPost(event_sem);
    delete event;
  }
}

void Observable::AddObserver(std::shared_ptr<Observer> observer) {
  observers_.push_back(observer);
}

void Observable::RemoveObserver(std::shared_ptr<Observer> observer) {
  // Remove the observer pointer from the vector
  observers_.erase(std::remove(observers_.begin(), observers_.end(), observer),
                   observers_.end());
}