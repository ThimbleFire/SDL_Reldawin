#include "Transform.h"

void Transform::SetPosition(int x, int y) {
    position.x = x;
    position.y = y;
    for (const auto& callback : positionChangeSubscribers) {
        callback(position);  // Pass the new position to the subscribers
    }
}

void Transform::SetPosition(Vector2i newPosition) {
    position = newPosition;
    for (const auto& callback : positionChangeSubscribers) {
        callback(position);  // Pass the new position to the subscribers
    }
}

void Transform::SetSize(int width, int height) {
    size.x = width;
    size.y = height;
    for (const auto& callback : sizeChangeSubscribers) {
        callback(size);  // Pass the new size to the subscribers
    }
}

void Transform::SetSize(Vector2i newSize) {
    size = newSize;
    for (const auto& callback : sizeChangeSubscribers) {
        callback(size);  // Pass the new size to the subscribers
    }
}

void Transform::Translate(int x, int y) {
    position.x += x;
    position.y += y;
    for (const auto& callback : positionChangeSubscribers) {
        callback(position);  // Pass the new position to the subscribers
    }
}

void Transform::Translate(Vector2i position) {
    this->position = this->position + position;
    for (const auto& callback : positionChangeSubscribers) {
        callback(position);  // Pass the new position to the subscribers
    }
}

void Transform::Translate(Vector2 position) {
    this->position = this->position + position;
}

void Transform::SubscribeToPositionChange(const std::function<void(const Vector2i&)>& callback) {
    positionChangeSubscribers.push_back(callback);
}

// Add a subscriber to the size change event
void Transform::SubscribeToSizeChange(const std::function<void(const Vector2i&)>& callback) {
    sizeChangeSubscribers.push_back(callback);
}

std::string Transform::ToString() const {
    return std::to_string(position.x) + ", " + std::to_string(position.y);
}

SDL_Rect Transform::ToRect() {
    return { position.x, position.y, size.x, size.y };
}
