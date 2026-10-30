#pragma once

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>

using namespace std;

template <typename T>
class BSTSet {
 private:
  struct BSTNode {
    // These two members should never change after initialization!
    const T value;
    BSTNode* parent;
    BSTNode* left;
    BSTNode* right;

    // This is fancy constructor syntax
    // Don't worry too much about it -- it's just necesssary for the const
    // member.
    BSTNode(T value, BSTNode* parent)
        : value(value), parent(parent), left(nullptr), right(nullptr) {
    }
  };

  BSTNode* root;
  size_t sz;

  // Utility pointer for begin and next.
  BSTNode* curr;

  // TODO_STUDENT: add private helper function definitions here

  // FIXME: add ctor_size, dtor
 public:
  /**
   * Creates an empty `BSTSet`. Runs in O(1).
   */
  BSTSet() {
    // TODO_STUDENT
    this->root = nullptr;
    this->sz = size_t{0};
    this->curr = root;
  }

  /**
   * Checks if the `BSTSet` is empty. Runs in O(1).
   */
  bool empty() const {
    // TODO_STUDENT
    return (!(this->sz));
  }

  /**
   * Returns the number of elements in the `BSTSet`. Runs in O(1).
   */
  size_t size() const {
    // TODO_STUDENT
    return (this->sz);
  }

  /**
   * Adds the `value` to the `BSTSet`. If the value already
   * exists in the set, does not do anything.
   *
   * Uses the `value` to determine the location in the underlying BST.
   * Creates exactly one new node.
   *
   * Runs in O(H), where H is the height of the tree.
   */

  // inexistent/uinitialized node
  void insert(T value) {
    // TODO_STUDENT
    if (contains(value)) {
      return;
    }
    if (root == nullptr) {
      root = new BSTNode(value, nullptr);
      (this->sz)++;
      return;
    }
    BSTNode* temp = root;
    while (true) {
      if (value < temp->value) {
        if (temp->left == nullptr) {
          temp->left = new BSTNode(value, temp);
          break;
        }
        temp = temp->left;
      } else {
        if (temp->right == nullptr) {
          temp->right = new BSTNode(value, temp);
          break;
        }
        temp = temp->right;
      }
    }
    (this->sz)++;
  }

  /**
   * Returns `true` if the `value` is present in the set,
   * and `false` otherwise.
   *
   * Runs in O(H), where H is the height of the tree.
   */
  bool contains(const T& value) const {
    // TODO_STUDENT
    BSTNode* temp = this->root;

    while (temp != nullptr) {
      if (value == temp->value) {
        return true;
      }

      else if (value < temp->value) {
        temp = temp->left;
      } else if (value > temp->value) {
        temp = temp->right;
      }
    }
    return false;
  }

  void dtor_helper(BSTNode*& curr) {
    if (curr == nullptr) {
      return;
    }
    dtor_helper(curr->left);
    dtor_helper(curr->right);
    delete curr;
    curr = nullptr;
  }

  /**
   * Empties the `BSTSet`, freeing all memory it controls.
   *
   * Runs in O(N), where N is the number of elements in the set.
   */
  void clear() {
    // TODO_STUDENT
    dtor_helper(this->root);

    // this->curr = nullptr;
    // this->root = nullptr;
    this->sz = size_t{0};
    this->curr = nullptr;
  }

  /**
   * Destructor, cleans up the `BSTSet`.
   *
   * Runs in O(N), where N is the number of elements in the set.
   */
  ~BSTSet() {
    // TODO_STUDENT
    dtor_helper(this->root);
    // this->curr = nullptr;
    // this->root = nullptr;
    this->sz = size_t{0};
    this->curr = nullptr;
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
  string to_string() const {
    // TODO_STUDENT
    return "";
  }

  BSTNode* ctor_helper(BSTNode* par, BSTNode* otherNode){

    if (otherNode == nullptr){
      return nullptr;
    }

    BSTNode* temp = new BSTNode(otherNode->value, par);
    par = temp;
    temp->left = ctor_helper(temp, otherNode->left);
    temp->right = ctor_helper(temp, otherNode->right);
    return temp;
  }

  /**
   * Copy constructor.
   *
   * Copies the elements from the provided `BSTSet`.
   * The internal tree structure must be copied exactly.
   *
   * Runs in O(N), where N is the number of elements in `other`.
   */
  BSTSet(const BSTSet& other) {
    // TODO_STUDENT
    this->root = nullptr;
    this->sz = other.sz;
    this->curr = nullptr;
    // edge case: empty tree
    this->root = ctor_helper(nullptr, other.root);

    // not empty
  }

  /**
   * Assignment operator; `operator=`.
   *
   * Clears this tree, and copies the elements from the provided `BSTSet`.
   * The internal tree structure must be copied exactly.
   *
   * Runs in O(N + O), where N is the number of elements in `this`, and O is
   * the number of elements in `other`.
   */
  BSTSet& operator=(const BSTSet& other) {
    // TODO_STUDENT
    return *this;
  }

  // end of milestone 1
  // =========================================================================

  /**
   * Locates the smallest element in the BSTSet, and removes it
   * from the `BSTSet`. If the `BSTSet` is empty, throws a
   * `runtime_error`.
   *
   * Creates no new nodes, and does not update any
   * existing nodes.
   *
   * Runs in O(H), where H is the height of the tree.
   */
  T remove_min() {
    // TODO_STUDENT
    return T{};
  }

  /**
   * Resets internal state for an iterative inorder traversal.
   *
   * See `next` for usage details. Modifies nothing except for `curr`.
   *
   * O(H), where H is the maximum height of the tree.
   */
  void begin() {
    // TODO_STUDENT
  }

  /**
   * Uses the internal state to return the next in-order element
   * by reference, and advances the internal state. Returns `true`
   * if the reference was set, and `false` otherwise.
   *
   * Example usage:
   *
   * c++
   * BSTSet<string> bst;
   * bst.begin();
   * string val;
   * while (bst.next(val)) {
   *   cout << val << endl;
   * }
   * ```
   *
   * Modifies nothing except for `curr`.
   *
   * Runs in worst-case O(H) where H is the height of the tree.
   */
  bool next(T& value) {
    // TODO_STUDENT
    return false;
  }

  // =========================================================================

  /**
   * Removes the given element from the `BSTSet`, and returns the
   * value.
   *
   * Throws `out_of_range` if the value is not present in the set.
   * Creates no new nodes, and does not update the value of any
   * existing nodes.
   *
   * Runs in worst-case O(H) where H is the height of the tree.
   */
  T erase(const T& value) {
    // TODO_STUDENT
    return T{};
  }

  // =========================================================================

  /**
   * Returns a pointer to the root node of the `BSTSet`. For autograder testing
   * purposes only.
   */
  void* getRoot() const {
    return this->root;
  }
};
