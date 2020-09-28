#include <iterator>
#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

struct building
{
    int const height;
    int const index;

    building(int h, int i)
        : height(h)
        , index(i)
    {}
};

auto operator <= (building const & obj, int x)
    -> bool
{
    return obj.height <= x;
}

vector<int> examine_building_with_sunset(
    vector<int>::const_iterator sequence_begin,
    const vector<int>::const_iterator& sequence_end)
{
    auto can_view_sunset = std::stack<building>{};
    auto counter = 0;
    while(sequence_begin != sequence_end)
    {
        auto const val = *sequence_begin;
        while( (!can_view_sunset.empty()) && (can_view_sunset.top() <= val) )
            can_view_sunset.pop();
        can_view_sunset.emplace(val, counter);
        std::advance(sequence_begin, 1); ++counter;
    }

    auto result = std::vector<int>{};
    while(!can_view_sunset.empty())
    {
        result.emplace_back(can_view_sunset.top().index);
        can_view_sunset.pop();
    }
    return result;
}

vector<int> ExamineBuildingsWithSunset(
    vector<int>::const_iterator sequence_begin,
    const vector<int>::const_iterator& sequence_end) {
  return examine_building_with_sunset(sequence_begin, sequence_end);
}
vector<int> ExamineBuildingsWithSunsetWrapper(const vector<int>& sequence) {
  return ExamineBuildingsWithSunset(cbegin(sequence), cend(sequence));
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"sequence"};
  return GenericTestMain(args, "sunset_view.cc", "sunset_view.tsv",
                         &ExamineBuildingsWithSunsetWrapper,
                         DefaultComparator{}, param_names);
}
