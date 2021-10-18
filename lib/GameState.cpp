#include "GameState.hpp"

namespace pacman {

constexpr int GHOST_POINTS = 200;
constexpr int NORMAL_PELLET_POINTS = 10;
constexpr int POWER_PELLET_POINTS = 50;

void GameState::step(std::chrono::milliseconds delta) {
  pacManAI.update(pacMan, pellets);
  pacMan.update(delta, inputState.enableAI ? pacManAI.suggestedDirection() : inputState.direction());

  if (isPacManDying()) {
    handleDeathAnimation(delta);
    return;
  }

  if (!pacMan.hasDirection())
    return;

  ghosts.setTarget(pacMan.positionInGrid(), pacMan.currentDirection());
  ghosts.update(delta);

  fruit.update(delta, score.eatenPellets);
  ghosts.checkCollision(*this);

  eatPellets();
  eatFruit();
}

void GameState::checkCollision(Ghost & ghost) {
  if (isPacManDying() || ghost.isEyes())
    return;

  // TODO: hitboxes based collision
  if (ghost.positionInGrid() != pacMan.positionInGrid())
    return;

  if (ghost.isFrightened()) {
    ghost.die();
    score.points += GHOST_POINTS;
  } else {
    killPacMan();
  }
}

void GameState::handleDeathAnimation(std::chrono::milliseconds delta) {
  timeSinceDeath += delta;

  if (timeSinceDeath.count() > 1000) {
    ghosts.reset();
    pacMan.reset();
    pacManAI.reset();
    timeSinceDeath = std::chrono::milliseconds(0);
  }
}

void GameState::eatPellets() {
  const auto pos = pacMan.positionInGrid();
  if (pellets.eatPelletAtPosition(pos)) {
    score.eatenPellets++;
    score.points += NORMAL_PELLET_POINTS;
  }

  if (superPellets.eatPelletAtPosition(pos)) {
    score.eatenPellets++;
    score.points += POWER_PELLET_POINTS;
    ghosts.frighten();
  }
}

void GameState::eatFruit() {
  const auto pos = pacMan.positionInGrid();
  const auto fruitpos = positionToGridPosition(fruit.position());

  // TODO: hitboxes based collision
  if (fruit.isVisible() && pos == fruitpos) {
    score.points += fruit.eat();
    score.eatenFruits++;
  }
}

void GameState::killPacMan() {
  pacMan.die();
  score.lives--;
  timeSinceDeath = std::chrono::milliseconds(1);
}

bool GameState::isPacManDying() const {
  return timeSinceDeath.count() != 0;
}

} // namespace pacman
