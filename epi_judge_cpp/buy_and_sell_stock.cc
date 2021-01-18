#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

auto max_profit(std::vector<double> const & diffs)
{
    auto max_profit  = std::numeric_limits<double>::min();
    auto current_sum = double{0};
    for(auto const & i : diffs)
    {
        current_sum = std::max(double{0}, current_sum + i);
        max_profit  = std::max(max_profit, current_sum);
    }
    return max_profit;
}

auto buy_and_sell_stock_once_impl(std::vector<double> const & prices)
{
    auto diffs = std::vector<double>{};
    std::adjacent_difference(prices.begin()
                            ,prices.end()
                            ,std::back_inserter(diffs));
    diffs.front() = 0;
    return max_profit(diffs);
}

double BuyAndSellStockOnce(const vector<double>& prices) {

  return buy_and_sell_stock_once_impl(prices);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"prices"};
  return GenericTestMain(args, "buy_and_sell_stock.cc",
                         "buy_and_sell_stock.tsv", &BuyAndSellStockOnce,
                         DefaultComparator{}, param_names);
}
