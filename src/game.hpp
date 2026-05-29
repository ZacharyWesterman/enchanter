namespace enchanter {

/**
 * @brief The main game loop.
 */
class game {
public:
	/// @brief Load any files and perform any setup needed before launching.
	game();

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
