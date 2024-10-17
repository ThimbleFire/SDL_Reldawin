#include "Transform.h"

void Transform::Translate(int x, int y) {
    this->position.x += x;
    this->position.y += y;
}
void Transform::Translate(Vector2i position) {
    this->position = this->position + position;
}
void Transform::Translate(Vector2 position) {
    this->position = this->position + position;
}