#include <iostream>
#include <vector>

std::vector<int> parse_input(int argc, char *argv[])
{
	/* Check to see if the number of rolls are within the limits of a
	 * valid game before we bother to parse it.
	 */
	if (argc < 13)
		throw std::invalid_argument("too few rolls entered");

	if (argc > 22)
		throw std::invalid_argument("too many rolls entered");

	/* Parse the input into integers with error checking. */
	int n_rolls = argc - 1;
	std::vector<int> rolls(n_rolls);
	for (int i = 0; i < n_rolls; i++) {
		char *end;
		auto n_pins = strtol(argv[i + 1], &end, 10);
		if (*end != '\0' || n_pins > 10 || n_pins < 0) {
			throw std::invalid_argument("# of pins knocked down must be"
				" valid base 10 integer between 0 and 10");
		}
		rolls[i] = n_pins;
	}
	return rolls;
}

/* Add up rolls from start to end indices to score the frame. */
int score_frame(const std::vector<int>& rolls, int start, int end)
{
	int score = 0;
	/* Make sure we don't overrun the rolls vector. */
	if (end >= rolls.size()) throw std::invalid_argument("too few rolls entered");
	if (end <= start) throw std::invalid_argument("frame should include at least 2 rolls");
	for (int i = start; i <= end; i++) score += rolls[i];
	return score;
}

int score_game(const std::vector<int>& rolls)
{
	int n_rolls = rolls.size();
	int total = 0;

	/* Starting and ending indices for rolls in the current frame. */
	int start = 0, end = 1;

	std::cout << "Scorecard: ";
	/* Expect 10 frames, process one frame at a time, looking at a sliding window from start to end. */
	for (int iframe = 0; iframe < 10; iframe++) {
		/* At start of new frame, we should have at least two rolls left to process. */
		if (start + 1 >= n_rolls) throw std::invalid_argument("too few rolls entered");
		bool is_strike = rolls[start] == 10;
		bool is_spare = rolls[start] + rolls[start + 1] == 10;
		if (is_strike || is_spare) {
			end = start + 2;
			total += score_frame(rolls, start, end);
		}
		else {
			end = start + 1;
			int score = score_frame(rolls, start, end);
			if (score > 10) throw std::invalid_argument("Two rolls in the same frame"
				" cannot add up to more than 10 pins");
			total += score;
		}
		/* Determine start of next frame. */
		if (is_strike) start += 1;
		else start += 2;
		std::cout << "[" << total << "]";
	}
	/* Should have processed all rolls. */
	if (end != n_rolls - 1) throw std::invalid_argument("too many rolls entered");
	std::cout << " --> " << total << std::endl;
	return total;
}

int main(int argc, char** argv)
try {
	auto rolls = parse_input(argc, argv);
	int total = score_game(rolls);
	return 0;
}
catch (std::exception& e) {
	std::cout << "Error: " << e.what() << std::endl;
	return 1;
}

catch (...) {
	std::cout << "Error: unexpected exception" << std::endl;
	return 1;
}


