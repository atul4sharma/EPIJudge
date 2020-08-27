#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
vector<int> MatrixInSpiralOrder(const vector<vector<int>>& square_matrix) {
    auto result = std::vector<int>{};
    result.reserve(square_matrix.size() * square_matrix.size());
    for(auto i = 0, j = static_cast<int>(square_matrix.size()) - 1
       ;i <= j
       ;++i, --j)
    {
        if( i == j )
        {
            result.emplace_back(square_matrix[i][j]);
            break;
        }

        for(auto k = i; k <= j - 1; ++k)
            result.emplace_back(square_matrix[i][k]);

        for(auto k = i; k <= j - 1; ++k)
            result.emplace_back(square_matrix[k][j]);

        for(auto k = j; k >= i + 1; --k)
            result.emplace_back(square_matrix[j][k]);

        for(auto k = j; k >= i + 1; --k)
            result.emplace_back(square_matrix[k][i]);
    }
    return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"square_matrix"};
  return GenericTestMain(args, "spiral_ordering.cc", "spiral_ordering.tsv",
                         &MatrixInSpiralOrder, DefaultComparator{},
                         param_names);
}
