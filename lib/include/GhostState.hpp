#pragma once

#include "Blinky.hpp"
#include "Dave.hpp"
#include "Inky.hpp"
#include "Pinky.hpp"

namespace pacman {

class GameState;

class GhostState {
public:
  void setTarget(GridPosition pacManPosition, Direction pacManDirection);
  void update(std::chrono::milliseconds delta);
  void checkCollision(GameState & gameState);
  void reset();
  void frighten();

  Blinky blinky;
  Pinky pinky;
  Inky inky;
  Dave dave;
};

} // namespace pacman
