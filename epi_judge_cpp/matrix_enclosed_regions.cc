#include <stdexcept>
#include <string>
#include <vector>

#include "test_framework/generic_test.h"
#include "test_framework/timed_executor.h"
using std::string;
using std::vector;

struct Coordinate { int x, y; };

void MarkBoundaryRegion(std::vector<std::vector<char>> & board, int x, int y)
{
    std::queue<Coordinate> q;
    q.push(Coordinate{x,y});
    while(!q.empty())
    {
        auto const vertex = q.front(); q.pop();
        const int a = vertex.x; const int b = vertex.y;
        if( a >= 0 && a < board.size()
          &&
            b >= 0 && b < board[a].size()
          &&
            board[a][b] == 'W')
        {
            board[a][b] = 'T';
            q.emplace(Coordinate{a  ,b+1});
            q.emplace(Coordinate{a  ,b-1});
            q.emplace(Coordinate{a+1,b  });
            q.emplace(Coordinate{a-1,b  });
        }

    }
}

void FillSurroundedRegions(vector<vector<char>>* board_ptr) {
    auto & board = *board_ptr;

    if(board.empty())
        return;

    for(int i = 0; i < board.size(); ++i) {
        MarkBoundaryRegion(board, i, 0);
        MarkBoundaryRegion(board, i, board.front().size() - 1);
    }

    for(int j = 0; j < board.front().size(); ++j) {
        MarkBoundaryRegion(board, 0, j);
        MarkBoundaryRegion(board, board.size() - 1, j);
    }

    for(auto & row: board)
        for(char & c : row)
            c = c != 'T' ? 'B' : 'W';

    return;
}
vector<vector<string>> FillSurroundedRegionsWrapper(
    TimedExecutor& executor, vector<vector<string>> board) {
  vector<vector<char>> char_vector;
  char_vector.resize(board.size());
  for (int i = 0; i < board.size(); i++) {
    for (const string& s : board[i]) {
      if (s.size() != 1) {
        throw std::runtime_error("String size is not 1");
      }
      char_vector[i].push_back(s[0]);
    }
  }

  executor.Run([&] { FillSurroundedRegions(&char_vector); });

  board.clear();
  board.resize(char_vector.size(), {});
  for (int i = 0; i < board.size(); i++) {
    for (char c : char_vector[i]) {
      board[i].emplace_back(1, c);
    }
  }

  return board;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "board"};
  return GenericTestMain(
      args, "matrix_enclosed_regions.cc", "matrix_enclosed_regions.tsv",
      &FillSurroundedRegionsWrapper, DefaultComparator{}, param_names);
}
