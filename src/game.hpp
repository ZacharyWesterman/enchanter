#pragma once

#include "world.hpp"

namespace enchanter {

/**
 * @brief The main game loop.
 */
class game {
	world game_world;

public:
	void update();

	/**
	 * @brief Run the game until the user closes it.
	 */
	void run();

	/**
	 * @brief Render a single frame to the window.
	 */
	void draw() const;
};

} // namespace enchanter
