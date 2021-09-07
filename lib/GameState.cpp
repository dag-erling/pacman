#include "GameState.hpp"

namespace pacman {

constexpr int GHOST_POINTS = 200;
constexpr int NORMAL_PELLET_POINTS = 10;
constexpr int POWER_PELLET_POINTS = 50;

void GameState::step(std::chrono::milliseconds delta) {
  pacMan.update(delta, inputState.direction());

  if (isPacManDying()) {
    handleDeathAnimation(delta);
    return;
  }

  if (!pacMan.hasDirection())
    return;

  blinky.update(delta, *this); // waage: urgh, I wanna remove this
  pinky.update(delta, *this); // ghosts know what they want, which is usually pacman's location
  inky.update(delta, *this);
  clyde.update(delta, *this);

  checkCollision(blinky);
  checkCollision(pinky);
  checkCollision(inky);
  checkCollision(clyde);

  eatPellets();
}

void GameState::checkCollision(Ghost & ghost) {
  if (isPacManDying() || ghost.isEyes())
    return;

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
    blinky.reset();
    pinky.reset();
    inky.reset();
    clyde.reset();
    pacMan.reset();
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

    blinky.frighten();
    pinky.frighten();
    inky.frighten();
    clyde.frighten();
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

}