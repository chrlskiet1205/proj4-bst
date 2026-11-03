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
    this->curr = nullptr;
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

  BSTNode* ctor_helper(BSTNode* par, BSTNode* otherNode) {
    if (otherNode == nullptr) {
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
    // protect against self-assignment
    if (this == &other) {
      return *this;
    }
    this->clear();
    this->root = nullptr;
    this->curr = nullptr;
    this->sz = other.sz;
    this->root = ctor_helper(nullptr, other.root);

    return *this;
  }

  // end of milestone 1
  // =========================================================================

  // helper function: fetch value from the tree
  void inorder_append(BSTNode* curr, ostringstream& val, bool& isFirst) const {
    if (curr == nullptr) {
      return;
    }
    inorder_append(curr->left, val, isFirst);

    if (!isFirst) {
      val << ", ";
    }
    val << curr->value;
    isFirst = false;
    // val << curr->value << ", ";
    inorder_append(curr->right, val, isFirst);
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
    ostringstream ss;
    ss << "{";
    BSTNode* curr = this->root;
    bool isFirst = true;
    inorder_append(curr, ss, isFirst);

    ss << "}";
    return ss.str();
  }

  BSTNode* find_min(BSTNode* node, BSTNode*& parent) const {
    if (node == nullptr) {
      return nullptr;
    }

    while (node->left != nullptr) {
      parent = node;
      node = node->left;
    }
    return node;
  }

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
    BSTNode* parent = nullptr;
    BSTNode* curr = find_min(this->root, parent);

    if (curr == nullptr) {
      throw runtime_error("tree is empty!");
    }
    T removed = curr->value;
    BSTNode* next = curr->right;
    // edge case: remove root
    if (parent == nullptr) {
      this->root = next;
    } else {
      parent->left = next;
    }

    // set parent for the child node if it is not null
    if (next != nullptr) {
      next->parent = parent;
    }
    delete curr;
    // minus size
    (this->sz)--;
    return removed;
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
    if (this->root == nullptr) {
      this->curr = nullptr;
      return;
    }
    this->curr = this->root;
    while (this->curr->left != nullptr) {
      this->curr = this->curr->left;
    }
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

    if (this->curr == nullptr) {
      return false;
    }
    BSTNode* node = curr;
    value = node->value;

    if (curr->right != nullptr) {
      node = node->right;
      while (node->left != nullptr) {
        node = node->left;
      }
      curr = node;
    } else {
      while (node->parent != nullptr && node->parent->right == node) {
        node = node->parent;
      }
      curr = node->parent;
      // value = curr->value;
    }

    return true;
  }

  // =========================================================================
  bool isRightChild(BSTNode* curr) {
    return curr->parent != nullptr && curr->parent->right == curr;
  }

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
    BSTNode* toDelete = root;
    while (toDelete != nullptr && toDelete->value != value) {
      toDelete = value < toDelete->value ? toDelete->left : toDelete->right;
    }
    if (toDelete == nullptr) {
      throw out_of_range("value does not exist!");
    }

    T erased = toDelete->value;
    BSTNode* parent = toDelete->parent;

    if (toDelete->left == nullptr || toDelete->right == nullptr) {
      BSTNode* child =
          toDelete->left != nullptr ? toDelete->left : toDelete->right;
      if (parent == nullptr) {
        root = child;
      } else if (parent->left == toDelete) {
        parent->left = child;
      } else {
        parent->right = child;
      }
      if (child != nullptr) {
        child->parent = parent;
      }
    } else {
      BSTNode* successor = toDelete->right;
      while (successor->left != nullptr) {
        successor = successor->left;
      }

      if (successor->parent != toDelete) {
        successor->parent->left = successor->right;
        if (successor->right != nullptr) {
          successor->right->parent = successor->parent;
        }
        successor->right = toDelete->right;
        successor->right->parent = successor;
      }

      successor->parent = parent;
      if (parent == nullptr) {
        root = successor;
      } else if (parent->left == toDelete) {
        parent->left = successor;
      } else {
        parent->right = successor;
      }
      successor->left = toDelete->left;
      successor->left->parent = successor;
    }

    if (curr == toDelete) {
      curr = nullptr;
    }
    delete toDelete;
    --sz;
    return erased;
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
