#pragma once

namespace enchanter {

/**
 * @brief The main game loop.
 */
class game {
	int pos_x = 0;
	int pos_y = 0;

public:
	/// @brief Load any files and perform any setup needed before launching.
	game();

	void update();

	/**
	 * @brief Run the game until the user closes it.
	 */
	void run();

	/**
	 * @brief Render a single frame to the window.
	 */
	void draw();
};

} // namespace enchanter
