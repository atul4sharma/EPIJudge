#include <string>
#include <vector>

#include "test_framework/generic_test.h"
using std::string;
using std::vector;

auto phone_numbers_impl(std::string                       const & number
                       ,std::map<char, std::vector<char>> const & mapping
                       ,int                               const   current_index
                       ,std::size_t                       const   size
                       ,std::vector<std::string>          const & till_now)
    -> std::vector<std::string>
{
    // TODO: better approach in solutions
    if( current_index >= size )
        return till_now;

    auto const lhs = mapping.at(number.at(current_index));
    auto       n_till_now = std::vector<std::string>{};
    for( auto const row : till_now)
    {
        for( auto const ch : lhs )
            n_till_now.emplace_back(row+ch);
    }
    
    return phone_numbers_impl(number, mapping, current_index+1, size, n_till_now);
}

auto phone_numbers(std::string number)
    -> std::vector<std::string>
{
    if( number.empty() )
        return {};
    auto const size = number.size();
    auto const mapping = std::map<char, std::vector<char>>{
                                                         {'0', {'0'}}
                                                        ,{'1', {'1'}}
                                                        ,{'2', {'A', 'B', 'C'}}
                                                        ,{'3', {'D', 'E', 'F'}}
                                                        ,{'4', {'G', 'H', 'I'}}
                                                        ,{'5', {'J', 'K', 'L'}}
                                                        ,{'6', {'M', 'N', 'O'}}
                                                        ,{'7', {'P', 'Q', 'R', 'S'}}
                                                        ,{'8', {'T', 'U', 'V'}}
                                                        ,{'9', {'W', 'X', 'Y', 'Z'}}
                                                   };
    auto const first_row = mapping.at(number.at(0));
    auto till_now = std::vector<std::string>{};
    std::transform(first_row.begin()
                  ,first_row.end()
                  ,std::back_inserter(till_now)
                  ,[] (char const ch) {return std::string{ch};});

    return phone_numbers_impl(number, mapping, 1, size, till_now);
}

vector<string> PhoneMnemonic(const string& phone_number) {
  return phone_numbers(phone_number);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"phone_number"};
  return GenericTestMain(args, "phone_number_mnemonic.cc",
                         "phone_number_mnemonic.tsv", &PhoneMnemonic,
                         UnorderedComparator{}, param_names);
}
