#include "Transform.h"

void Transform::SetPosition(Vector2 newPosition) {
    SetPosition(newPosition.x, newPosition.y);
}

void Transform::SetPosition(float x, float y) {
    position.set(x, y);
    onPositionChanged.invoke();
}

void Transform::SetSize(Vector2 newSize) {
    SetSize(newSize.x, newSize.y);
}

void Transform::SetSize(float width, float height) {
    size.set(width, height);
    onSizeChanged.invoke();
}

void Transform::Translate(Vector2 position) {
    Translate(position.x, position.y);
}

void Transform::Translate(float x, float y) {
    position.x += x;
    position.y += y;
    onPositionChanged.invoke();
}

void Transform::UpdateInAccordanceWithParent(Transform& parent) {
    position.set( parent.position.x + left * parent.size.x + pixel_left, parent.position.y + top * parent.size.y + pixel_top );
    onPositionChanged.invoke();
    if (resizeWithParent) {
        size.set((right - left) * parent.size.x - (pixel_left + pixel_right), (bottom - top) * parent.size.y - (pixel_top + pixel_bottom));
        onSizeChanged.invoke();
    }
}

std::string Transform::ToString() const {
    return std::to_string(position.x) + ", " + std::to_string(position.y) + ", " + std::to_string(size.x) + ", " + std::to_string(size.y);
}

SDL_FRect Transform::ToRect() const {
    return { position.x, position.y, size.x, size.y };
}
