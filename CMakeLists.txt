cmake_minimum_required(VERSION 3.9)
project(Reversi)

set(CMAKE_CXX_COMPILER /usr/local/bin/g++-8)
set(CMAKE_C_COMPILER /usr/local/bin/gcc-8)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fopenmp -O3")

add_executable(Reversi main.cpp httpd.cpp common.h MCTS/MCTS.cpp MCTS/MCTS.h MCTS/Modules/TreeNode.cpp MCTS/Modules/TreeNode.h MCTS/Modules/Board.cpp MCTS/Modules/Board.h MCTS/Modules/Action.h MCTS/Modules/State.h MCTS/Modules/Simulator/Simulator.h MCTS/Modules/Simulator/SimulRand.cpp MCTS/Modules/Simulator/SimulRand.h MCTSPlayer.h MCTS/Modules/Simulator/SimulMinMax.cpp MCTS/Modules/Simulator/SimulMinMax.h MCTS/Modules/Simulator/SimulGreedy.cpp MCTS/Modules/Simulator/SimulGreedy.h)