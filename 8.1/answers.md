# 8.1 Describe the concepts and terms associated with key data structures

### Objectives

- [ ] Circularly linked list
- [ ] Hash table
- [ ] Weighted graph
- [ ] Common pitfalls when using linked lists, trees, and graphs
- [ ] The effect of First In First Out (FIFO) and Last In First Out (LIFO)
- [ ] Stack
- [ ] Tree vs Binary search tree
- [ ] Linked list
- [ ] Double linked list
- [ ] Queue vs Priority Queue

### Answers

**Circularly linked list**   
> A linked list where all nodes are connected in such a way as to form a circle. IE the last node points to the first node.

**Hash table**
> A lookup table where the index is a hash of some key.

**Weighted graph**
> A graph with nodes and edges where each edge has a numerical weight. This weight indicates some relationship between the connected nodes.
IE roads connecting cities; where the cities are nodes and the roads are edges with the length of the road being its weight.

**Common pitfalls when using linked lists, trees, and graphs**
> Challenges with traversal efficiency of the structures; increased memory usage due to having to store pointers, and variable efficiency in
insertion and deletion.

**The effect of First In First Out (FIFO) and Last In First Out (LIFO)**
> Common methods of managing data structures particularly stacks and queues. FIFO will operate on the items in the order recieved
whereas LIFO will will process the most recent first. The choice of which to use depends on the situation. FIFO is appropriate when the order of processing matters and LIFO where handling the most recent data is most important.

**Stack**
> LIFO based method of storing data (generally srquential in a single block of memory). With a pointer to the stop of the stack where operations take place such as push (to add to the stack), pop (to remove from the stack) and peek (to look at the item without removing it)

**Tree vs Binary search tree**
> Heirarchal structures both composed of nodes. Trees are composed of edges connecting nodes where each node can have 0 or more child nodes with a root node at the top. Binary search trees are a more specific type of tree structure where each node has at most 2 child nodes and the nodes are organized such that the left nodes are less than the parent node by some metric and right nodes are greater. this allows for efficient and fast searching, insertion and deletion.

**Linked list**
> Data is not stored sequentionally in memory instead each node contains the data and a pointer to the next node in the list with the final
node generally pointing to null. Unlike arrays a linked list can dynamically grow and shrink but is slower as pointer lookups have to be preformed to traverse the list and it is not possible to jump to a specific node.

**Double linked list**
> Same as a list but the ndoes also contain a pointer to the previous node allowing for bi-directional traversal of the list which can improve insertion and deletion times as well as traversal in some cases.

**Queue vs Priority Queue**
> A queue is linear and follows FIFO, whereas a priority queue stores an associated priority allowing retrieval of the highest priority element. Both have enqueue, dequeue and peek operations. Essentially a queue just inserts the items as it recieves them but a priority queue will orignaize thsoe items based on the priority.
