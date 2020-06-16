#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

#if 0
auto operator<<(std::ostream & out, std::vector<int> const & v)
    -> std::ostream &
{
    std::copy(v.begin(), v.end(), std::ostream_iterator<int>(out, ""));
    return out;
}
#endif

inline auto constexpr individual_multiply(int const a, int const b, int const carry)
{
    auto const result = (a * b) + carry;
                                   // carry    , remainder
    return std::make_pair<int, int>(result / 10, result % 10);
}

inline auto remove_leading_zeros(std::vector<int> & result)
{
    auto zero_end = std::find_if(result.begin(), result.end(), [] (int const i){ return i > 0; });
    if( zero_end == result.end() )
        std::advance(zero_end, -1);
    result.erase(result.begin(), zero_end);
}

auto vector_into_num(std::vector<int> const & vec, int const num)
{
    //std::cout << __func__ << " " << vec << " * " << num << '\n';

    if( num == 0 )
        return std::vector<int>{0};

    auto carry = 0;
    auto result = std::vector<int>{};
    std::transform(vec.rbegin()
                  ,vec.rend()
                  ,std::back_inserter(result)
                  ,[&carry, &num] (auto const & x) {
                      auto res = individual_multiply(x, num, carry);
                      carry = std::get<0>(res);
                      return std::get<1>(res);
                  });
    while(carry)
    {
        result.emplace_back(carry %10);
        carry /= 10;
    }
    std::reverse(result.begin(), result.end());
    return result;
}

auto vector_add(std::vector<int> const & a, std::vector<int> const & b)
{
    //std::cout << __func__ << " " << a << " + " << b << '\n';

    auto result = std::vector<int>{};
    auto i      = static_cast<long long>(a.size() - 1);
    auto j      = static_cast<long long>(b.size() - 1);
    auto carry  = 0;
    auto rem    = 0;
    auto sum    = 0;

    for( ; i >= 0 and j >= 0; --i, --j)
    {
        sum   = a[i] + b[j] + carry;
        carry = int{sum/10};
        rem   = sum % 10;
        result.emplace_back(rem);
    }

    for(; i >= 0; --i)
    {
        sum = a[i] + carry;
        carry = int{sum/10};
        rem   = sum % 10;
        result.emplace_back(rem);
    }

    for(; j >=0; --j)
    {
        sum = b[j] + carry;
        carry = int{sum/10};
        rem   = sum % 10;
        result.emplace_back(rem);
    }

    while(carry)
    {
        result.emplace_back(carry %10);
        carry /= 10;
    }

    std::reverse(result.begin(), result.end());
    return result;
}

auto multiply_impl(std::vector<int> const & num1, std::vector<int> const & num2)
{
    //std::cout << "multiplying " << num1 << " * " << num2 << "\n";
    long long i = 0;
    return std::accumulate(num1.rbegin()
                          ,num1.rend()
                          ,std::vector<int>{0}
                          ,[&num2, &i](std::vector<int> const & total, int const num){
                               auto res = vector_into_num(num2, num);
                               auto temp = std::vector<int>(i++, 0);
                               res.insert(res.end(), temp.begin(), temp.end());
                               remove_leading_zeros(res);
                               return vector_add(total, res);
                          });
}

// TODO: Can be improved
vector<int> Multiply(vector<int> num1, vector<int> num2) {

  auto resulting_sign = (num1.front() * num2.front()) > 0;
  num1.front() = std::abs(num1.front());
  num2.front() = std::abs(num2.front());

  auto result = multiply_impl(num1, num2);
  if( ! resulting_sign )
      result.front() = -1 * result.front();
  return result;
}



int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"num1", "num2"};
  return GenericTestMain(args, "int_as_array_multiply.cc",
                         "int_as_array_multiply.tsv", &Multiply,
                         DefaultComparator{}, param_names);
}
