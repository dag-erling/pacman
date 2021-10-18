#pragma once

#include "Ghost.hpp"

namespace pacman {

class Dave final : public Ghost {
public:
  Dave();
  void setTarget(Position pacManPos);

protected:
  double speed() const override;
  Position initialPosition() const override;

private:
  Position scatterTarget() const;
};

} // namespace pacman
