#include <deque>
#include <vector>

#include "test_framework/generic_test.h"
#include "test_framework/timed_executor.h"
using std::deque;
using std::vector;

bool is_flippable(int const x, int const y, bool const to_color, std::vector<deque<bool>> const & image)
{
    return x >= 0 && x < image.size()
        && y >= 0 && y < image[x].size()
        && image[x][y] != to_color;
}

void flip_color_impl(int x, int y, bool const to_color, std::vector<deque<bool>> & image)
{
    auto constexpr shifts = std::array<std::array<int,2>, 4>{
         std::array<int, 2>{ 0, 1}
        ,std::array<int, 2>{ 1, 0}
        ,std::array<int, 2>{ 0,-1}
        ,std::array<int, 2>{-1, 0}
    };
    for(auto const & shift : shifts)
    {
        int next_x = x + shift[0];
        int next_y = y + shift[1];
        if( is_flippable(next_x, next_y, to_color, image) )
        {
            image[next_x][next_y] = !image[next_x][next_y];
            flip_color_impl(next_x, next_y, to_color, image);
        }
    }
    return;
}

void FlipColor(int x, int y, vector<deque<bool>>* image_ptr) {
  auto & image = *image_ptr;
  image[x][y] = !image[x][y];
  bool to_color = image[x][y];
  flip_color_impl(x, y, to_color, image);
  return;
}
vector<vector<int>> FlipColorWrapper(TimedExecutor& executor, int x, int y,
                                     vector<vector<int>> image) {
  vector<deque<bool>> b;
  b.reserve(image.size());
  for (const vector<int>& row : image) {
    deque<bool> tmp;
    tmp.resize(row.size());
    for (int i = 0; i < row.size(); ++i) {
      tmp[i] = static_cast<bool>(row[i]);
    }
    b.push_back(tmp);
  }

  executor.Run([&] { FlipColor(x, y, &b); });

  image.resize(b.size());

  for (int i = 0; i < image.size(); ++i) {
    image[i].resize(b.size());
    for (int j = 0; j < image[i].size(); ++j) {
      image[i][j] = b[i][j];
    }
  }
  return image;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "x", "y", "image"};
  return GenericTestMain(args, "matrix_connected_regions.cc", "painting.tsv",
                         &FlipColorWrapper, DefaultComparator{}, param_names);
}
