#include "binary_tree_with_parent_prototype.h"
#include "test_framework/binary_tree_utils.h"
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"

auto get_depth(BinaryTreeNode<int> const * node)
{
    int depth = 0;
    while( node->parent != nullptr)
    {
        ++depth;
        node = node->parent;
    }
    return depth;
}

auto lca_impl(const unique_ptr<BinaryTreeNode<int>>& node0,
              const unique_ptr<BinaryTreeNode<int>>& node1)
    -> BinaryTreeNode<int>*
{
    auto *iter_0 = node0.get(), *iter_1 = node1.get();
    int depth_0 = get_depth(iter_0), depth_1 = get_depth(iter_1);

    if( depth_1 > depth_0)
        std::swap(iter_0, iter_1);

    int depth_diff = std::abs(depth_0 - depth_1);
    while(depth_diff--)
        iter_0 = iter_0->parent;

    while(iter_0 != iter_1)
    {
        iter_0 = iter_0->parent, iter_1 = iter_1->parent;
    }
    return iter_0;
}

BinaryTreeNode<int>* Lca(const unique_ptr<BinaryTreeNode<int>>& node0,
                         const unique_ptr<BinaryTreeNode<int>>& node1) {
  return lca_impl(node0, node1);
}

int LcaWrapper(TimedExecutor& executor,
               const unique_ptr<BinaryTreeNode<int>>& tree, int key0,
               int key1) {
  const unique_ptr<BinaryTreeNode<int>>& node0 = MustFindNode(tree, key0);
  const unique_ptr<BinaryTreeNode<int>>& node1 = MustFindNode(tree, key1);

  auto result = executor.Run([&] { return Lca(node0, node1); });

  if (!result) {
    throw TestFailure("Result can not be nullptr");
  }
  return result->data;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "tree", "key0", "key1"};
  return GenericTestMain(args, "lowest_common_ancestor_with_parent.cc",
                         "lowest_common_ancestor.tsv", &LcaWrapper,
                         DefaultComparator{}, param_names);
}
