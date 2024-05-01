"""- [x] Creating a binary search tree with n number of items
- [x] Navigating through a binary search tree
- [x] Locating an item in a binary search tree
- [x] Removing selected items from the binary search tree
- [x] Removing all items from the binary search tree
- [x] Describe implementation strategies for a balanced binary search tree
- [x] Destroying a binary search tree
"""

from dataclasses import dataclass, field
from enum import Enum

class Traversal(Enum):
    """BST Traversal Enum"""
    IN_ORDER = 0
    PRE_ORDER = 1
    POST_ORDER = 2

@dataclass
class BSTNode:
    """Base node data class"""
    value: int
    left: 'BSTNode' = field(init=False)
    right: 'BSTNode' = field(init=False)
    count: int = field(init=False)

    def __post_init__(self) -> None:
        self.left = None
        self.right = None
        self.count = 1


class BinarySearchTree:
    """Binary search tree manager class object"""
    def __init__(self, values: list[int] = None) -> None:
        self._root: BSTNode = None
        if values:
            if all(isinstance(x, int) for x in values):
                values.sort()
                unique_values = set()
                duplicate_values = []

                for v in values:
                    if v in unique_values:
                        duplicate_values.append(v)
                    else:
                        unique_values.add(v)

                self._root = self._sorted_array_to_bst(list(unique_values))

                for v in duplicate_values:
                    self.add_node(v)
            else:
                raise ValueError('Error - List provided to BSTRoot contains non-integer value(s).')

    # - [ ] Removing selected items from the binary search tree
    def _delete(self, node: BSTNode, value: int) -> BSTNode:
        """Removes a node with matching value

        Constructs the command line list before calling the parent class's run_test() method.

        Args:
            node: Node to process.
            value: The value to be removed from the tree.
        """
        if node is None:
            return node

        if node.value > value:
            node.left = self._delete(node.left, value)
        elif node.value < value:
            node.right = self._delete(node.right, value)
        else:
            if node.left is None:
                return node.right
            elif node.right is None:
                return node.left

            node.value = self._min_value(node.right)
            node.right = self._delete(node.right, node.value)

        return node

    def _clear(self, node: BSTNode) -> None:
        """Clears every child node of a specified node"""
        if node:
            self._clear(node.left)
            self._clear(node.right)
            node.left = None
            node.right = None

    def _reduce(self, node: BSTNode, value: int) -> BSTNode:
        """Reduces a nodes count
        
        Attempts to reduce a nodes count attribute by 1. Deletes the node if
        the count reaches 0.

        Args:
            node: Node to process.
            value: The value to be reduced.
        """
        if node is None:
            return node

        if node.value > value:
            node.left = self._delete(node.left, value)
        elif node.value < value:
            node.right = self._delete(node.right, value)
        else:
            node.count -= 1
            if node.count <= 0:
                return self._delete(self._root, value)

        return node

    def _min_value(self, node) -> int:
        """Get the lowest value in the tree
        
        Args:
            node: The node to process.
        """
        min_value = node.value
        while node.left:
            min_value = node.left.value
            node = node.left
        return min_value

    def _insert(self, node: BSTNode, value: int) -> BSTNode:
        """Insert a node with the specified value

        Args:
            node: The node to process.
            value: The value to be inserted.
        """
        if node is None:
            return BSTNode(value)
        else:
            if node.value == value:
                node.count += 1
            elif node.value < value:
                node.right = self._insert(node.right, value)
            else:
                node.left = self._insert(node.left, value)
        return node

    # - [ ] Navigating through a binary search tree
    # - [ ] Locating an item in a binary search tree
    def _search(self, node: BSTNode, value: int) -> BSTNode:
        """Find a node with specified value
        
        Args:
            node: The node to process.
            value: The value to search for.
        """
        if node is None or node.value == value:
            return node

        if node.value < value:
            return self._search(node.right, value)

        return self._search(node.left, value)

    # - [ ] Creating a binary search tree with n number of items
    def _sorted_array_to_bst(self, values):
        if not values:
            return None

        mid = len(values) // 2
        n = BSTNode(values[mid])
        n.left = self._sorted_array_to_bst(values[:mid])
        n.right = self._sorted_array_to_bst(values[(mid + 1):])
        return n

    def add_node(self, value: int) -> BSTNode:
        """Add a node to the tree with specified value."""
        return self._insert(self._root, value)

    # - [ ] Removing all items from the binary search tree
    def clear_tree(self) -> None:
        """Remove all nodes from the tree."""
        self._clear(self._root)
        self._root = None

    def delete_node(self, value: int, ignore_count: bool = False) -> int:
        """Finds and deletes or reduces a node's count
        
        Args:
            ignore_count: If True will delete a node regardless of the count.
                Otherwise it will reduce the count by 1 and remove it if count is 0.
        """
        if ignore_count:
            self._delete(self._root, value)
        else:
            n = self._reduce(self._root, value)
            if n:
                return n.count

        return 0

    def find_node(self, value: int) -> BSTNode | None:
        """Returns a node with the matching value.
        
        Args:
            value: The value to search for.
            
        Returns:
            The specified node or None if value is not found.
        """
        return self._search(self._root, value)

    def print_traversal(self, traversal_method: Traversal = Traversal.IN_ORDER) -> None:
        """Simple print of the tree in the specified method.
        
        Args:
            traversal_method: the method of traversal to use.
        """
        def _inorder(node: BSTNode) -> None:
            if node:
                _inorder(node.left)
                print(f'{node.value}:{node.count}', end=' ')
                _inorder(node.right)

        def _preorder(node: BSTNode) -> None:
            if node:
                print(f'{node.value}:{node.count}', end=' ')
                _preorder(node.left)
                _preorder(node.right)

        def _postorder(node: BSTNode) -> None:
            if node:
                _postorder(node.left)
                _postorder(node.right)
                print(f'{node.value}:{node.count}', end=' ')

        match traversal_method:
            case Traversal.PRE_ORDER:
                _preorder(self._root)
            case Traversal.POST_ORDER:
                _postorder(self._root)
            case _:
                _inorder(self._root)
        print()

    def print_tree(self, node, level=0):
        """Print the tree structure."""
        if node:
            self.print_tree(node.left, level + 1)
            print(' ' * 4 * level + '-> ' + str(node.value) + ':' + str(node.count))
            self.print_tree(node.right, level + 1)

    @property
    def root_node(self) -> BSTNode:
        """Getter for the root node of the tree."""
        return self._root


if __name__ == '__main__':
    node_list = [4, 2, 3, 7, 8, 10, 7, 2, 11]
    print(f'Convert list to BST: {node_list}')
    bst = BinarySearchTree(node_list)
    print('In order traversal, number following the colon is the count:')
    bst.print_traversal()
    print('Tree view, number following the colon is the count:')
    bst.print_tree(bst.root_node)
    print('Add nodes with values of 22, 13, 1, 5')
    bst.add_node(22)
    bst.add_node(13)
    bst.add_node(1)
    bst.add_node(5)
    bst.print_tree(bst.root_node)
    print('Remove a single 7')
    bst.delete_node(7)
    bst.print_tree(bst.root_node)
    print('Completely remove 11')
    bst.delete_node(11, True)
    bst.print_tree(bst.root_node)
    print('Clear the tree')
    bst.clear_tree()
    bst.print_tree(bst.root_node)
    # - [ ] Destroying a binary search tree
    del bst

# - [ ] Describe implementation strategies for a balanced binary search tree
# There are three primary ways to create a self balancing BST
# AVL Trees
#     Each node has a balance criteria which is the difference in height of the left and right
#     subtrees. After insertion or deletion if the balance goes out of range(greater than 1 or
#     less than -1) rotations are performed to rebalance.
# Red-Black Trees
#     Each noe is either red or black. Balance is checked by ensuring there are no adjacent red
#     nodes and each path from the root node to a lead contains the same number of black nodes.
#     By using color flipping and rotations during insertion and deletion balance can be maintained.
# Splay Trees
#     Uses splay operations to move the most recently accessed node to the root. This reduces access
#     time for frequently accessed nodes. Also performs rotations during insertion, deletion, and
#     accesses restructuring the tree to maintain balance.
