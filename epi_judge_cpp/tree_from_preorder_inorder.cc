#include <vector>

#include "binary_tree_node.h"
#include "test_framework/binary_tree_utils.h"
#include "test_framework/generic_test.h"
using std::vector;

unique_ptr<BinaryTreeNode<int>> binary_tree_from_preorder_inorder(
    const vector<int>& preorder, const vector<int>& inorder)
{
    if( preorder.empty() )
        return nullptr;

    auto const value = preorder.front();
    auto root_ptr = std::make_unique<BinaryTreeNode<int>>(value);

    auto const inorder_root    = std::find(inorder.begin(), inorder.end(), value);
    auto const left_inorder_v  = std::vector<int>{inorder.begin(), inorder_root};

    auto const preorder_left   = std::next(preorder.begin()) + left_inorder_v.size();
    auto const left_preorder_v = std::vector<int>{std::next(preorder.begin()), preorder_left};
    root_ptr->left             = binary_tree_from_preorder_inorder(left_preorder_v, left_inorder_v);

    auto const right_inorder_v  = std::vector<int>{std::next(inorder_root), inorder.end()};
    auto const right_preorder_v = std::vector<int>{preorder_left          , preorder.end()};
    root_ptr->right             = binary_tree_from_preorder_inorder(right_preorder_v, right_inorder_v);

    return std::move(root_ptr);
}

unique_ptr<BinaryTreeNode<int>> BinaryTreeFromPreorderInorder(
    const vector<int>& preorder, const vector<int>& inorder) {
  return binary_tree_from_preorder_inorder(preorder, inorder);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"preorder", "inorder"};
  return GenericTestMain(
      args, "tree_from_preorder_inorder.cc", "tree_from_preorder_inorder.tsv",
      &BinaryTreeFromPreorderInorder, DefaultComparator{}, param_names);
}
