cmake_minimum_required(VERSION 3.9)
project(Reversi)

set(CMAKE_CXX_STANDARD 11)

add_executable(Reversi main.cpp MCTS/MCTS.cpp MCTS/MCTS.h MCTS/Modules/TreeNode.cpp MCTS/Modules/TreeNode.h MCTS/Modules/Board.cpp MCTS/Modules/Board.h MCTS/Modules/Action.h MCTS/Modules/State.h MCTS/Modules/Simulator/Simulator.h MCTS/Modules/Simulator/SimulRand.cpp MCTS/Modules/Simulator/SimulRand.h)