#pragma once

#include "entities/entity.hpp"
#include "world.hpp"
#include <vector>

namespace enchanter {

/**
 * @brief The main game loop.
 */
class game {
	world game_world;

	std::vector<entity *> entities;

public:
	/// @brief Load any files and perform any setup needed before launching.
	game();

	~game();

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
