#include "Transform.h"

void Transform::SetPosition(Vector2i newPosition) {
    SetPosition(newPosition.x, newPosition.y);
}

void Transform::SetPosition(int x, int y) {
    position.set(x, y);
    for (const auto& callback : positionChangeSubscribers) {
        callback();  // Notify subscribers, no parameters needed
    }
}

void Transform::SetSize(Vector2i newSize) {
    SetSize(newSize.x, newSize.y);
}

void Transform::SetSize(int width, int height) {
    size.set(width, height);
    for (const auto& callback : sizeChangeSubscribers) {
        callback();  // Notify subscribers, no parameters needed
    }
}

void Transform::Translate(Vector2i position) {
    Translate(position.x, position.y);
}

void Transform::Translate(int x, int y) {
    position.x += x;
    position.y += y;
    for (const auto& callback : positionChangeSubscribers) {
        callback();  // Notify subscribers, no parameters needed
    }
}

void Transform::Translate(Vector2 position) {
    this->position = this->position + position;
    for (const auto& callback : positionChangeSubscribers) {
        callback();  // Notify subscribers, no parameters needed
    }
}

void Transform::UpdateInAccordanceWithParent(Transform& parent) {
    position.set(
        static_cast<int>(parent.position.x + left * parent.size.x) + pixel_left,
        static_cast<int>(parent.position.y + top * parent.size.y) + pixel_top
    );
    
    size.set(
        static_cast<int>((right - left) * parent.size.x) - (pixel_left + pixel_right),
        static_cast<int>((bottom - top) * parent.size.y) - (pixel_top + pixel_bottom)
    );

    for (const auto& callback : positionChangeSubscribers) {
        callback();
    }
    for (const auto& callback : sizeChangeSubscribers) {
        callback();
    }
}

void Transform::SubscribeToPositionChange(const std::function<void()>& callback) {
    positionChangeSubscribers.push_back(callback);
}

void Transform::SubscribeToSizeChange(const std::function<void()>& callback) {
    sizeChangeSubscribers.push_back(callback);
}

std::string Transform::ToString() const {
    return std::to_string(position.x) + ", " + std::to_string(position.y) + ", " + std::to_string(size.x) + ", " + std::to_string(size.y);
}

SDL_Rect Transform::ToRect() {
    return { position.x, position.y, size.x, size.y };
}
