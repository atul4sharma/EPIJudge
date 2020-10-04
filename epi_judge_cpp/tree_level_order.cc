#include <memory>
#include <vector>

#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
using std::unique_ptr;
using std::vector;

auto binary_tree_depth_order(std::unique_ptr<BinaryTreeNode<int>> const & tree)
    -> std::vector<std::vector<int>>
{
    if( tree == nullptr )
        return {};

    auto result = std::vector<std::vector<int>>{};

    auto current_level = std::vector<BinaryTreeNode<int> *>{tree.get()};
    while(!current_level.empty())
    {
        auto next_level = std::vector<BinaryTreeNode<int> *>{};
        auto current_v  = std::vector<int>{};

        for(auto const & processing_node : current_level)
        {
            current_v.emplace_back(processing_node->data);

            if( processing_node->left.get() != nullptr )
                next_level.emplace_back(processing_node->left.get());
            if( processing_node->right.get() != nullptr )
                next_level.emplace_back(processing_node->right.get());
        }
        result.emplace_back(current_v);
        current_level = std::move(next_level);
    }

    return result;
}

vector<vector<int>> BinaryTreeDepthOrder(
    const unique_ptr<BinaryTreeNode<int>>& tree) {
  return binary_tree_depth_order(tree);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "tree_level_order.cc", "tree_level_order.tsv",
                         &BinaryTreeDepthOrder, DefaultComparator{},
                         param_names);
}
