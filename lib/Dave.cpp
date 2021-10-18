#include "Dave.hpp"

namespace pacman {

Dave::Dave()
  : Ghost(Atlas::Ghost::dave) {
  pos = initialPosition();
}

double Dave::speed() const {
  if (state == State::Eyes)
    return 2;
  if (state == State::Frightened)
    return 0.5;
  return 0.75;
}

void Dave::setTarget(Position pacManPos) {
  if (isInPen()) {
    target = penDoorPosition();
    return;
  }
  if (positionDistance(pos, pacManPos) > 8) {
    target = pacManPos;
  } else {
    target = scatterTarget();
  }
}

Position Dave::initialPosition() const {
  return { 15.5, 14 };
}

Position Dave::scatterTarget() const {
  return { 0, 30 };
}

} // namespace pacman
