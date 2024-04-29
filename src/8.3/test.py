from dataclasses import dataclass

class BSTRoot:
    """"""

    def __init__(self, values: list[int] = None) -> None:
        self._node: "BSTNode" = None
        if values:
            if all(isinstance(x, int) for x in values):
                values.sort()
                self._node = self._populate_from_list(values)
            else:
                raise ValueError('Error - List provided to BSTRoot contains non-integer value(s).')
            

    def _populate_from_list(self, values) -> "BSTNode":
        """"""
        if len(values) == 1:
            return BSTNode(values[0])
        
        middle = len(values) // 2
        n = BSTNode(values[middle])
        n.left = self._populate_from_list(values[:middle])
        n.right = self._populate_from_list(values[middle + 1:])

        return n
    
    def print(self) -> None:
        """"""
        # assumed is balanced
        l = self._node.left
        count = 0
        while l is not None:
            count += 1
            l = l.left

    @property.getter
    def _node(self) -> "BSTNode":
        """"""
        return self._node
    
    @property.setter
    def _node

    @classmethod
    def delete_node(self, value: int, preserve_duplicates: bool = True) -> None:
        """"""
        n = find_node_by_value(value)
        if not preserve_duplicates:
            # remove and rebuild
            pass

    @classmethod
    def find_node_by_value(self, value: int) -> "BSTNode":
        """"""


class BSTNode:
    """"""
    value: int
    count: int = 0
    left:"BSTNode" = None
    right:"BSTNode" = None

    def __init__(self, value:int):
        self.value = value
        self.count += 1

    @classmethod
    def append_node(self, node:"BSTNode"):
        """"""
        if node.value < self.value:
            if self.left is None:
                self.left = node
            else:
                self.left.append_node(node)

    @classmethod
    def delete_node(self) -> "BSTNode"|None:
        """"""
