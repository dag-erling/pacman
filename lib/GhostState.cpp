#include "GhostState.hpp"
#include "GameState.hpp"

namespace pacman {

void GhostState::setTarget(GridPosition pacManPosition, Direction pacManDirection) {
  blinky.setTarget(gridPositionToPosition(pacManPosition));
  pinky.setTarget(pacManPosition, pacManDirection);
  inky.setTarget(pacManPosition, pacManDirection, blinky.positionInGrid());
  dave.setTarget(gridPositionToPosition(pacManPosition));
}

void GhostState::update(std::chrono::milliseconds delta) {
  blinky.update(delta);
  pinky.update(delta);
  inky.update(delta);
  dave.update(delta);
}

void GhostState::checkCollision(GameState & gameState) {
  gameState.checkCollision(blinky);
  gameState.checkCollision(pinky);
  gameState.checkCollision(inky);
  gameState.checkCollision(dave);
}

void GhostState::reset(void) {
  blinky.reset();
  pinky.reset();
  inky.reset();
  dave.reset();
}

void GhostState::frighten(void) {
  blinky.frighten();
  pinky.frighten();
  inky.frighten();
  dave.frighten();
}

} // namespace pacman
