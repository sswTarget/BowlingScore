#include <iostream>
#include <vector>

std::vector<int> parse_input(int argc, char *argv[])
{
  /* Check to see if the number of throws are within the limits of a
   * valid game before we bother to parse it.
   */
  if(argc < 13)
    throw std::invalid_argument("too few throws entered");
 
  if(argc > 22)
    throw std::invalid_argument("too many throws entered");

  /* Parse the input into integers with error checking. */
  int n_throws = argc - 1;
  std::vector<int> pins_per_throw(n_throws);
  for(int i=0;i< n_throws;i++) {
    char *end;
    auto n_pins = strtol(argv[i + 1], &end, 10);
    if(*end != '\0' || n_pins > 10 || n_pins < 0) {
      throw std::invalid_argument("# of pins knocked down must be"
        " valid base 10 integer between 0 and 10");
    }
	pins_per_throw[i] = n_pins;
  }
  return pins_per_throw;
}

int main(int argc, char** argv)
try{
  auto pins_per_throw = parse_input(argc, argv);
  int frames_scored = 0;
  int i = 0;
  int total = 0;
  int last_frame = 0;
  bool last_was_strike = false;
  int n_throws = pins_per_throw.size();
  std::cout << "Scorecard: ";

  /* Look at a sliding window of up to 3 throws at a time to 
   * score a frame.
   *
   * Note: if there was no strike or spare on the last frame,
   * this will exit before the last frame has been tallied.
   */
  while(i < (n_throws - 2)) {
	last_was_strike = false;
    /* This should never reach 10 since i > n_throws-2
	 * if we've scored all the way through the 10th frame
	 * for a valid number of throws. */
    if(frames_scored > 9)
      throw std::invalid_argument("too many throws entered");
    /* Look at the first throw and see if it's a strike. */
    int first = pins_per_throw[i];
    /* Add the next two throws and score the frame. */
    if(first == 10) {
      last_frame = first + pins_per_throw[i + 1] + pins_per_throw[i + 2];
      /* There was only one throw in this frame, set i to the
       * first throw in the next frame. */
      i += 1;
	  last_was_strike = true;
    }
    else {
      /* We don't have a strike, so at least two throws count
       * in this frame (which can't add up to more than 10), and
       * the start of the next frame is i+2.*/
		last_frame = first + pins_per_throw[i + 1];
      if(last_frame > 10)
        throw std::invalid_argument("Two throws in the same frame"
          " cannot add up to more than 10 pins");
      if(last_frame == 10) last_frame += pins_per_throw[i + 2];
      i += 2;
    }
    total += last_frame;
    std::cout << "[" << total << "] ";
    frames_scored++;
  }
  /* Handle last frame if it was a non-spare/strike
   * and finish checking for invalid number of throws. */
  if(frames_scored < 9) {
    /* We should have either processed all frames or all but
     *  the last frame. */
    throw std::invalid_argument("too few throws entered");
  }
  if(frames_scored == 9) {
    /* No strike or spare on the last frame, so we should have
     *  exactly two throws left to process. */
    if(i != n_throws - 2)
      throw std::invalid_argument("too few throws entered");
    /* Go ahead and add up the last frame. */
	int first_ball = pins_per_throw[i];
	int second_ball = pins_per_throw[i + 1];
    last_frame = first_ball + second_ball;
    total += last_frame;
	if (first_ball == 10 || last_frame == 10)
		throw std::invalid_argument("too few throws entered");
	else if(last_frame > 10)
		throw std::invalid_argument("Two throws in the same frame"
			" cannot add up to more than 10 pins");
	std::cout << "[" << total << "] ";
  }
  else {
	  /* Check to see if there were extra throws after
	   * scoring the final strike/spare. */
	  if (last_was_strike && i != n_throws - 2)
		throw std::invalid_argument("too many throws entered");
	  if(!last_was_strike && i != n_throws - 1)
		throw std::invalid_argument("too many throws entered");
  }
  std::cout << " --> " << total;
  return 0;
}
catch(std::exception& e) {
  std::cout << "Error: " << e.what() << std::endl;
  return 1;
}

catch(...) {
  std::cout << "Error: unexpected exception" << std::endl;
  return 1;
}


