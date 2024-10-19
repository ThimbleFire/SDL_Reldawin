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
