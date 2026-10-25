#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <random>

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

TEST(BSTSetCore, EmptyAndSizeAndInsertAndContainsTest) {
  BSTSet<int> testbst;
  ASSERT_EQ(size_t{0}, testbst.size());
  ASSERT_TRUE(testbst.empty());
  ASSERT_FALSE(testbst.contains(1));

  testbst.insert(1);
  ASSERT_EQ(size_t{1}, testbst.size());
  ASSERT_FALSE(testbst.empty());
  ASSERT_TRUE(testbst.contains(1));
  ASSERT_FALSE(testbst.contains(10));

  testbst.insert(10);
  ASSERT_EQ(size_t{2}, testbst.size());
  ASSERT_FALSE(testbst.empty());
  ASSERT_TRUE(testbst.contains(1));
  ASSERT_TRUE(testbst.contains(10));
  ASSERT_FALSE(testbst.contains(100));

  testbst.insert(100);
  ASSERT_EQ(size_t{3}, testbst.size());
  ASSERT_FALSE(testbst.empty());
  ASSERT_TRUE(testbst.contains(1));
  ASSERT_TRUE(testbst.contains(10));
  ASSERT_TRUE(testbst.contains(100));

  testbst.insert(10);
  ASSERT_EQ(size_t{3}, testbst.size());
  ASSERT_FALSE(testbst.empty());

  testbst.clear();
  ASSERT_EQ(size_t{0}, testbst.size());
  ASSERT_TRUE(testbst.empty());
  ASSERT_FALSE(testbst.contains(1));
  ASSERT_FALSE(testbst.contains(10));
  ASSERT_FALSE(testbst.contains(100));
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
  ASSERT_TRUE(blank_copy.empty());
  ASSERT_EQ(size_t{0}, blank_copy.size());

  BSTSet<int> testbst;
  testbst.insert(1);
  testbst.insert(10);

  BSTSet<int> copy(testbst);
  ASSERT_EQ(size_t{2}, copy.size());
  ASSERT_FALSE(copy.empty());
  ASSERT_TRUE(copy.contains(1));
  ASSERT_TRUE(copy.contains(10));
  ASSERT_FALSE(copy.contains(100));
}

TEST(BSTSetCore, SmoothOperator) {
  BSTSet<int> blank;

  BSTSet<int> testbst;
  testbst.insert(1);
  testbst.insert(10);

  // self assignment check
  BSTSet<int> copy = testbst;
  testbst = copy;
  ASSERT_FALSE(testbst.empty());
  ASSERT_TRUE(testbst.contains(1));
  ASSERT_TRUE(testbst.contains(10));
  ASSERT_FALSE(testbst.contains(100));
  ASSERT_EQ(size_t{2}, testbst.size());

  // copying empty bst check
  BSTSet<int> empty_copy = blank;
  ASSERT_TRUE(empty_copy.empty());
  ASSERT_EQ(size_t{0}, empty_copy.size());

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