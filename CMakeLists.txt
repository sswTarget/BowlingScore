cmake_minimum_required(VERSION 2.6)
project(BowlingScore)
add_executable(BowlingScore bowling_score.cpp)

include(CTest)

add_test (BowlingScorePerfect BowlingScore 10 10 10 10 10 10 10 10 10 10 10 10)
set_tests_properties(BowlingScorePerfect PROPERTIES PASS_REGULAR_EXPRESSION "--> 300")

add_test (BowlingScoreNormal1 BowlingScore 1 2 3 4 5 1 2 3 4 5 1 2 3 4 5 1 2 3 4 5)
set_tests_properties(BowlingScoreNormal1 PROPERTIES PASS_REGULAR_EXPRESSION "--> 60")

add_test (BowlingScoreNormal2 BowlingScore 1 4 3 2 6 3 10 5 5 1 4 3 2 6 3 1 4 10 5 5)
set_tests_properties(BowlingScoreNormal2 PROPERTIES PASS_REGULAR_EXPRESSION "--> 94")

add_test (BowlingScoreNormal3 BowlingScore 4 5 6 4 10 10 9 1 0 7 8 1 2 3 5 3 10 1 0)
set_tests_properties(BowlingScoreNormal3 PROPERTIES PASS_REGULAR_EXPRESSION "--> 128")

add_test (BowlingScoreNormal4 BowlingScore 2 7 6 4 3 2 3 4 5 3 4 5 6 4 3 4 10 9 1 6)
set_tests_properties(BowlingScoreNormal4 PROPERTIES PASS_REGULAR_EXPRESSION "--> 107")

add_test (BowlingScoreBadInput1 BowlingScore 10 10 10 10 10 10 10 10 10 10 10 1a)
set_tests_properties(BowlingScoreBadInput1 PROPERTIES PASS_REGULAR_EXPRESSION "must be valid base 10 integer")

add_test (BowlingScoreBadInput2 BowlingScore 10 10 10 10 10 10 10 10 10 10 10 )
set_tests_properties(BowlingScoreBadInput2 PROPERTIES PASS_REGULAR_EXPRESSION "too few throws")

add_test (BowlingScoreBadInput3 BowlingScore 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10)
set_tests_properties(BowlingScoreBadInput3 PROPERTIES PASS_REGULAR_EXPRESSION "too many throws")

add_test (BowlingScoreBadInput4 BowlingScore 1 2 3 4 5 1 2 3 4 5 1 2 3 9 5 1 2 3 4 5)
set_tests_properties(BowlingScoreBadInput4 PROPERTIES PASS_REGULAR_EXPRESSION "cannot add up to more than 10 pins")

add_test (BowlingScoreBadInput5 BowlingScore 1 2 10 5 6 2 3 4 5 1 2 3 4 5 1 2 3 4 5)
set_tests_properties(BowlingScoreBadInput5 PROPERTIES PASS_REGULAR_EXPRESSION "cannot add up to more than 10 pins")
# fix these two tests
add_test (BowlingScoreBadInput6 BowlingScore 1 4 3 2 6 3 10 5 5 1 4 3 2 6 3 10 5 4 3 3 )
set_tests_properties(BowlingScoreBadInput6 PROPERTIES PASS_REGULAR_EXPRESSION "too many throws entered")

add_test (BowlingScoreBadInput7 BowlingScore 1 4 3 2 6 3 10 5 5 1 4 3 2 6 3 10 5 4 3 3 )
set_tests_properties(BowlingScoreBadInput7 PROPERTIES PASS_REGULAR_EXPRESSION "too many throws entered")

add_test (BowlingScoreBadInput7 BowlingScore 1 4 3 2 6 3 10 5 5 1 4 3 2 6 3 1 4 10 5)
set_tests_properties(BowlingScoreBadInput7 PROPERTIES PASS_REGULAR_EXPRESSION "too few throws entered")
