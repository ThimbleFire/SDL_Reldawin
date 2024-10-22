#include <iostream>
#include <vector>
#include <functional>

class Event {
public:
    std::vector<std::function<void()>> listeners;

    void subscribe(const std::function<void()>& listener) {
        listeners.push_back(listener);
    }

    void invoke() {
        for (auto& listener : listeners) {
            listener();
        }
    }
};

class EventTurple {
    public:
        std::vector<std::function<void(int, int)>> listeners;

        void subscribe(const std::function<void(int, int)>& listener) {
            listeners.push_back(listener);
        }

        void invoke(int x, int y) {
            for (auto& listener : listeners) {
                listener(x, y);  // Call listeners with parameters
            }
        }
};
