#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <random>
#include <set>
#include <vector>

#include "bstset.h"

using namespace std;
using namespace testing;

namespace {

class Random {
 private:
  static mt19937 rng;

 public:
  static void seed(int s) {
    Random::rng.seed(s);
  }

  /**
   * Generate a random integer in the range 0 (inclusive) to `max` (exclusive)
   */
  static int randInt(int max) {
    // Even though mt19937 is standardized, STL distributions aren't!
    // So, unfortunately, even though this is biased, we're forced to
    // do something like this. Technically uint32_fast_t isn't...
    // totally consistent across platforms? But within reason it works.
    return rng() % (max + 1);
  }
};

std::mt19937 Random::rng;

template <typename T>
void shuffle_vec(vector<T>& values) {
  for (size_t i = values.size(); i > 1; --i) {
    const size_t j =
        static_cast<size_t>(Random::randInt(static_cast<int>(i - 1)));
    swap(values[i - 1], values[j]);
  }
}

// TEST(FakeTest, PleaseDeleteOnceYouWriteSome) {
//   // If no tests exist, GoogleTest fails to compile with a fairly confusing
//   // message. We have this empty test that does nothing to allow an empty
//   // autograder submission to compile and regularly fail. Once you write your
//   // own tests for the project, you can delete this one.
//   EXPECT_THAT(1, Eq(1));
// }

}  // namespace

TEST(BSTSetCore, ConstructorTest) {
  // empty BSTSet test
  BSTSet<int> defaultBST;
  EXPECT_EQ(size_t{0}, defaultBST.size());
  EXPECT_TRUE(defaultBST.empty());
}

TEST(BSTSetCore, EmptyTest) {
  BSTSet<int> testbst;
  EXPECT_TRUE(testbst.empty());

  testbst.insert(1);
  EXPECT_FALSE(testbst.empty());

  testbst.insert(10);
  EXPECT_FALSE(testbst.empty());

  testbst.insert(100);
  EXPECT_FALSE(testbst.empty());

  testbst.insert(10);
  EXPECT_FALSE(testbst.empty());

  testbst.clear();
  EXPECT_TRUE(testbst.empty());
}

TEST(BSTSetCore, SizeTest) {
  BSTSet<int> testbst;
  EXPECT_EQ(size_t{0}, testbst.size());

  testbst.insert(1);
  EXPECT_EQ(size_t{1}, testbst.size());

  testbst.insert(10);
  EXPECT_EQ(size_t{2}, testbst.size());

  testbst.insert(100);
  EXPECT_EQ(size_t{3}, testbst.size());

  testbst.insert(10);
  EXPECT_EQ(size_t{3}, testbst.size());

  testbst.clear();
  EXPECT_EQ(size_t{0}, testbst.size());
}

TEST(BSTSetCore, InsertTest) {
  BSTSet<int> testbst;

  testbst.insert(1);
  EXPECT_EQ(size_t{1}, testbst.size());
  EXPECT_TRUE(testbst.contains(1));

  testbst.insert(10);
  EXPECT_EQ(size_t{2}, testbst.size());
  EXPECT_TRUE(testbst.contains(1));
  EXPECT_TRUE(testbst.contains(10));

  testbst.insert(100);
  EXPECT_EQ(size_t{3}, testbst.size());
  EXPECT_TRUE(testbst.contains(1));
  EXPECT_TRUE(testbst.contains(10));
  EXPECT_TRUE(testbst.contains(100));

  testbst.insert(10);
  EXPECT_EQ(size_t{3}, testbst.size());
  EXPECT_TRUE(testbst.contains(10));
}

TEST(BSTSetCore, ContainsTest) {
  BSTSet<int> testbst;
  EXPECT_FALSE(testbst.contains(1));

  testbst.insert(1);
  EXPECT_TRUE(testbst.contains(1));
  EXPECT_FALSE(testbst.contains(10));

  testbst.insert(10);
  EXPECT_TRUE(testbst.contains(1));
  EXPECT_TRUE(testbst.contains(10));
  EXPECT_FALSE(testbst.contains(100));

  testbst.insert(100);
  EXPECT_TRUE(testbst.contains(1));
  EXPECT_TRUE(testbst.contains(10));
  EXPECT_TRUE(testbst.contains(100));

  testbst.clear();
  EXPECT_FALSE(testbst.contains(1));
  EXPECT_FALSE(testbst.contains(10));
  EXPECT_FALSE(testbst.contains(100));
}

TEST(BSTSetCore, ClearTest) {
  BSTSet<int> testbst;
  testbst.insert(1);
  testbst.insert(10);
  testbst.insert(100);

  testbst.clear();
  EXPECT_EQ(size_t{0}, testbst.size());
  EXPECT_TRUE(testbst.empty());
  EXPECT_FALSE(testbst.contains(1));
  EXPECT_FALSE(testbst.contains(10));
  EXPECT_FALSE(testbst.contains(100));
}

TEST(BSTSetCore, DestructorTest) {
  {
    BSTSet<int> testbst;
    testbst.insert(1);
    testbst.insert(10);
  }
}

TEST(BSTSetCore, CopyConstructorTest) {
  BSTSet<int> blank;
  BSTSet<int> blank_copy(blank);
  EXPECT_TRUE(blank_copy.empty());
  EXPECT_EQ(size_t{0}, blank_copy.size());

  BSTSet<int> testbst;
  testbst.insert(1);
  testbst.insert(10);

  BSTSet<int> copy(testbst);
  EXPECT_EQ(size_t{2}, copy.size());
  EXPECT_FALSE(copy.empty());
  EXPECT_TRUE(copy.contains(1));
  EXPECT_TRUE(copy.contains(10));
  EXPECT_FALSE(copy.contains(100));
}

TEST(BSTSetCore, AssignmentOperatorTest) {
  BSTSet<int> blank;

  BSTSet<int> testbst;
  testbst.insert(1);
  testbst.insert(10);

  // self assignment check
  BSTSet<int> copy = testbst;
  testbst = copy;
  EXPECT_FALSE(testbst.empty());
  EXPECT_TRUE(testbst.contains(1));
  EXPECT_TRUE(testbst.contains(10));
  EXPECT_FALSE(testbst.contains(100));
  EXPECT_EQ(size_t{2}, testbst.size());

  // copying empty bst check
  BSTSet<int> empty_copy = blank;
  EXPECT_TRUE(empty_copy.empty());
  EXPECT_EQ(size_t{0}, empty_copy.size());

  // Assign empty to non-empty.
  testbst = blank;
  EXPECT_TRUE(testbst.empty());
  EXPECT_EQ(size_t{0}, testbst.size());
  EXPECT_FALSE(testbst.contains(1));
  EXPECT_FALSE(testbst.contains(10));

  // Assign sets of different sizes.
  BSTSet<int> larger;
  larger.insert(2);
  larger.insert(3);
  larger.insert(4);

  testbst.insert(1);
  testbst = larger;
  EXPECT_EQ(size_t{3}, testbst.size());
  EXPECT_TRUE(testbst.contains(2));
  EXPECT_TRUE(testbst.contains(3));
  EXPECT_TRUE(testbst.contains(4));
  EXPECT_FALSE(testbst.contains(1));

  // Actual self-assignment.
  BSTSet<int>& same_set = testbst;
  testbst = same_set;
  EXPECT_EQ(size_t{3}, testbst.size());
  EXPECT_TRUE(testbst.contains(2));
  EXPECT_TRUE(testbst.contains(3));
  EXPECT_TRUE(testbst.contains(4));
}

/**
 * Converts the `BSTSet` to a string representation, with the values
 * in-order by value.
 *
 * Example:
 *
 * c++
 * BSTSet<string> names;
 * names.insert("Gwen");
 * names.insert("Jen");
 * names.insert("Ben");
 * names.insert("Sven");
 *
 * Calling `names.to_string()` would return the following
 * string: `{Ben, Gwen, Jen, Sven}`
 *
 * Runs in O(N), where N is the number of elements.
 */
TEST(BSTSetCore, ToString) {
  BSTSet<string> names;
  names.insert("Gwen");
  names.insert("Jen");
  names.insert("Ben");
  names.insert("Sven");

  EXPECT_EQ("{Ben, Gwen, Jen, Sven}", names.to_string());
}

TEST(BSTSetAugmented, RemoveMinFromEmptyThrows) {
  BSTSet<int> bst;
  EXPECT_THROW(bst.remove_min(), runtime_error);
  EXPECT_TRUE(bst.empty());
  EXPECT_EQ(size_t{0}, bst.size());
}

TEST(BSTSetAugmented, RemoveMinFromSingletonEmptiesTree) {
  BSTSet<int> bst;
  bst.insert(6);

  EXPECT_EQ(6, bst.remove_min());
  EXPECT_TRUE(bst.empty());
  EXPECT_EQ(size_t{0}, bst.size());
  EXPECT_FALSE(bst.contains(6));
  EXPECT_THROW(bst.remove_min(), runtime_error);
}

TEST(BSTSetAugmented, RemoveMinHandlesMinimumWithRightChild) {
  BSTSet<int> bst;
  for (int value : {5, 3, 7, 4, 2}) {
    bst.insert(value);
  }

  EXPECT_EQ(2, bst.remove_min());
  EXPECT_EQ(3, bst.remove_min());
  EXPECT_TRUE(bst.contains(4));
  EXPECT_TRUE(bst.contains(5));
  EXPECT_TRUE(bst.contains(7));
  EXPECT_FALSE(bst.contains(2));
  EXPECT_FALSE(bst.contains(3));
  EXPECT_EQ(size_t{3}, bst.size());
}

TEST(BSTSetAugmented, RemoveMinMatchesReferenceForSeededTrees) {
  Random::seed(42);

  for (int trial = 0; trial < 30; ++trial) {
    BSTSet<int> bst;
    set<int> reference;

    const int count = 1 + Random::randInt(9);
    while (static_cast<int>(reference.size()) < count) {
      reference.insert(Random::randInt(100));
    }

    vector<int> insertion_order(reference.begin(), reference.end());
    shuffle_vec(insertion_order);
    for (int value : insertion_order) {
      bst.insert(value);
    }

    while (!reference.empty()) {
      const int expected_min = *reference.begin();
      EXPECT_EQ(expected_min, bst.remove_min());
      reference.erase(reference.begin());
      EXPECT_EQ(reference.size(), bst.size());
      EXPECT_EQ(reference.empty(), bst.empty());

      for (int value = 0; value <= 100; ++value) {
        EXPECT_EQ(reference.count(value) != 0, bst.contains(value));
      }
    }

    EXPECT_THROW(bst.remove_min(), runtime_error);
  }
}

TEST(BSTSetAugmented, BeginAndNextTraverseSeededTreesInOrder) {
  Random::seed(251);

  BSTSet<int> empty_bst;
  empty_bst.begin();
  int value = 0;
  EXPECT_FALSE(empty_bst.next(value));

  for (int trial = 0; trial < 30; ++trial) {
    BSTSet<int> bst;
    set<int> reference;

    const int count = Random::randInt(10);
    while (static_cast<int>(reference.size()) < count) {
      reference.insert(Random::randInt(100));
    }

    vector<int> insertion_order(reference.begin(), reference.end());
    shuffle_vec(insertion_order);

    for (int inserted : insertion_order) {
      bst.insert(inserted);
    }

    bst.begin();
    for (int expected : reference) {
      ASSERT_TRUE(bst.next(value));
      EXPECT_EQ(expected, value);
    }
    EXPECT_FALSE(bst.next(value));

    if (!reference.empty()) {
      bst.begin();
      ASSERT_TRUE(bst.next(value));
      EXPECT_EQ(*reference.begin(), value);
    }
  }
}

TEST(BSTSetErase, EraseMissingValueThrowsWithoutChangingSet) {
  BSTSet<int> empty_bst;
  EXPECT_THROW(empty_bst.erase(5), out_of_range);
  EXPECT_TRUE(empty_bst.empty());
  EXPECT_EQ(size_t{0}, empty_bst.size());

  BSTSet<int> bst;
  for (int value : {8, 4, 12}) {
    bst.insert(value);
  }

  EXPECT_THROW(bst.erase(6), out_of_range);
  EXPECT_EQ(size_t{3}, bst.size());
  EXPECT_TRUE(bst.contains(4));
  EXPECT_TRUE(bst.contains(8));
  EXPECT_TRUE(bst.contains(12));
}

TEST(BSTSetErase, EraseHandlesLeafAndNodesWithOneChild) {
  BSTSet<int> leaf_tree;
  for (int value : {8, 4, 12}) {
    leaf_tree.insert(value);
  }
  EXPECT_EQ(4, leaf_tree.erase(4));
  EXPECT_EQ(size_t{2}, leaf_tree.size());
  EXPECT_FALSE(leaf_tree.contains(4));
  EXPECT_TRUE(leaf_tree.contains(8));
  EXPECT_TRUE(leaf_tree.contains(12));

  BSTSet<int> left_child_tree;
  for (int value : {8, 4, 12, 2}) {
    left_child_tree.insert(value);
  }
  EXPECT_EQ(4, left_child_tree.erase(4));
  EXPECT_EQ(size_t{3}, left_child_tree.size());
  EXPECT_FALSE(left_child_tree.contains(4));
  EXPECT_TRUE(left_child_tree.contains(2));
  EXPECT_TRUE(left_child_tree.contains(8));
  EXPECT_TRUE(left_child_tree.contains(12));

  BSTSet<int> right_child_tree;
  for (int value : {8, 4, 12, 6}) {
    right_child_tree.insert(value);
  }
  EXPECT_EQ(4, right_child_tree.erase(4));
  EXPECT_EQ(size_t{3}, right_child_tree.size());
  EXPECT_FALSE(right_child_tree.contains(4));
  EXPECT_TRUE(right_child_tree.contains(6));
  EXPECT_TRUE(right_child_tree.contains(8));
  EXPECT_TRUE(right_child_tree.contains(12));
}

TEST(BSTSetErase, EraseHandlesRootAndTwoChildren) {
  BSTSet<int> root_with_left_child;
  root_with_left_child.insert(8);
  root_with_left_child.insert(4);
  EXPECT_EQ(8, root_with_left_child.erase(8));
  EXPECT_EQ(size_t{1}, root_with_left_child.size());
  EXPECT_TRUE(root_with_left_child.contains(4));
  EXPECT_FALSE(root_with_left_child.contains(8));

  BSTSet<int> root_with_right_child;
  root_with_right_child.insert(8);
  root_with_right_child.insert(12);
  EXPECT_EQ(8, root_with_right_child.erase(8));
  EXPECT_EQ(size_t{1}, root_with_right_child.size());
  EXPECT_TRUE(root_with_right_child.contains(12));
  EXPECT_FALSE(root_with_right_child.contains(8));

  BSTSet<int> immediate_successor_tree;
  for (int value : {8, 4, 12, 14}) {
    immediate_successor_tree.insert(value);
  }
  EXPECT_EQ(8, immediate_successor_tree.erase(8));
  EXPECT_EQ(size_t{3}, immediate_successor_tree.size());
  EXPECT_FALSE(immediate_successor_tree.contains(8));
  EXPECT_TRUE(immediate_successor_tree.contains(4));
  EXPECT_TRUE(immediate_successor_tree.contains(12));
  EXPECT_TRUE(immediate_successor_tree.contains(14));

  BSTSet<int> deeper_successor_tree;
  for (int value : {8, 4, 12, 10, 14, 11}) {
    deeper_successor_tree.insert(value);
  }
  EXPECT_EQ(8, deeper_successor_tree.erase(8));
  EXPECT_EQ(size_t{5}, deeper_successor_tree.size());
  EXPECT_FALSE(deeper_successor_tree.contains(8));
  for (int value : {4, 10, 11, 12, 14}) {
    EXPECT_TRUE(deeper_successor_tree.contains(value));
  }

  BSTSet<int> internal_two_children_tree;
  for (int value : {20, 10, 30, 5, 15}) {
    internal_two_children_tree.insert(value);
  }
  EXPECT_EQ(10, internal_two_children_tree.erase(10));
  EXPECT_EQ(size_t{4}, internal_two_children_tree.size());
  EXPECT_FALSE(internal_two_children_tree.contains(10));
  for (int value : {5, 15, 20, 30}) {
    EXPECT_TRUE(internal_two_children_tree.contains(value));
  }
}

TEST(BSTSetErase, EraseMatchesReferenceForSeededTreesAndRemovalOrders) {
  Random::seed(421);

  for (int trial = 0; trial < 40; ++trial) {
    BSTSet<int> bst;
    set<int> reference;

    const int count = Random::randInt(10);
    while (static_cast<int>(reference.size()) < count) {
      reference.insert(Random::randInt(100));
    }

    vector<int> insertion_order(reference.begin(), reference.end());
    shuffle_vec(insertion_order);
    for (int value : insertion_order) {
      bst.insert(value);
    }

    EXPECT_THROW(bst.erase(101), out_of_range);

    vector<int> removal_order(reference.begin(), reference.end());
    shuffle_vec(removal_order);
    for (int value : removal_order) {
      ASSERT_EQ(value, bst.erase(value));
      reference.erase(value);
      EXPECT_EQ(reference.size(), bst.size());
      EXPECT_EQ(reference.empty(), bst.empty());
      for (int candidate = 0; candidate <= 100; ++candidate) {
        EXPECT_EQ(reference.count(candidate) != 0, bst.contains(candidate));
      }
    }

    EXPECT_THROW(bst.erase(101), out_of_range);
    EXPECT_TRUE(bst.empty());
    EXPECT_EQ(size_t{0}, bst.size());
  }
}
