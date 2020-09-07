#include "binary_tree_node.h"
#include "test_framework/generic_test.h"

struct height_and_balance
{
    bool const is_balanced;
    int  const height;

    height_and_balance(bool b, int h)
        : is_balanced{std::move(b)}
        , height{std::move(h)}
    {}
};


auto is_balanced_impl(std::unique_ptr<BinaryTreeNode<int>> const & tree) 
    -> height_and_balance
{
    if( tree == nullptr)
        return {true, -1};

    auto const left_height  = is_balanced_impl(tree->left);
    if( !left_height.is_balanced )
        return {false, 0};

    auto const right_height = is_balanced_impl(tree->right);
    if( !right_height.is_balanced )
        return {false, 0};

    bool const is_balanced = std::abs(left_height.height - right_height.height) <= 1;
    int  const height      = std::max(left_height.height, right_height.height) + 1;

    return {is_balanced, height};
}

bool IsBalanced(const unique_ptr<BinaryTreeNode<int>>& tree) {
  return is_balanced_impl(tree).is_balanced;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "is_tree_balanced.cc", "is_tree_balanced.tsv",
                         &IsBalanced, DefaultComparator{}, param_names);
}
