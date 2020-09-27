#include <memory>
#include <vector>

#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using std::unique_ptr;
using std::vector;

auto inorder(std::unique_ptr<BinaryTreeNode<int>>                     const & node
            ,std::vector<const std::unique_ptr<BinaryTreeNode<int>>*>       & res)
    -> void
{
    if( node == nullptr )
        return;
    
    if( node->left == nullptr && node->right == nullptr )
        res.emplace_back(&node);

    inorder(node->left , res);
    inorder(node->right, res);
}

auto create_list_of_leaves(std::unique_ptr<BinaryTreeNode<int>> const & tree)
    -> std::vector<const std::unique_ptr<BinaryTreeNode<int>> *>
{
    auto result = std::vector<const std::unique_ptr<BinaryTreeNode<int>>*>{};
    inorder(tree, result);
    return result;
}

vector<const unique_ptr<BinaryTreeNode<int>>*> CreateListOfLeaves(
    const unique_ptr<BinaryTreeNode<int>>& tree) {
  return create_list_of_leaves(tree);
}
vector<int> CreateListOfLeavesWrapper(
    TimedExecutor& executor, const unique_ptr<BinaryTreeNode<int>>& tree) {
  auto result = executor.Run([&] { return CreateListOfLeaves(tree); });

  if (std::any_of(std::begin(result), std::end(result),
                  [](const unique_ptr<BinaryTreeNode<int>>*& x) {
                    return !x || !*x;
                  })) {
    throw TestFailure("Result list can't contain nullptr");
  }

  vector<int> extracted_result;
  for (const auto& x : result) {
    extracted_result.push_back(x->get()->data);
  }
  return extracted_result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "tree"};
  return GenericTestMain(args, "tree_connect_leaves.cc",
                         "tree_connect_leaves.tsv", &CreateListOfLeavesWrapper,
                         DefaultComparator{}, param_names);
}
