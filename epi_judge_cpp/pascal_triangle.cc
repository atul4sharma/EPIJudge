#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

auto generate_row(std::vector<std::vector<int>> const & till_now
                 ,int                           const   nth_row)
    -> std::vector<int>
{
    if( nth_row == 1 )
        return {1};
    if( nth_row == 2 )
        return {1,1};

    auto row = std::vector<int>{1};
    for( auto i = 0; i < nth_row - 2; ++i)
    {
        auto & n_minus_one_row = till_now[nth_row -2];
        row.emplace_back( n_minus_one_row[i] + n_minus_one_row[i+1]);
    }
    row.emplace_back(1);
    return row;
}

vector<vector<int>> GeneratePascalTriangle(int num_rows) {
    auto result = std::vector<std::vector<int>>{};
    for(auto i = 1; i <= num_rows; ++i)
    {
        result.emplace_back(generate_row(result, i));
    }
    return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"num_rows"};
  return GenericTestMain(args, "pascal_triangle.cc", "pascal_triangle.tsv",
                         &GeneratePascalTriangle, DefaultComparator{},
                         param_names);
}
