# TreeTests
Testing Splay V. AVL Tree under specific search distributions:

A Splay tree is a variation of the Binary Search Tree that restructures itself upon insert, remove and find operations, moving the element in 
question to the root of the tree with a series of rotations called Splaying. It is commonly cited that with the properties aforementioned it can achieve faster find times of recently searched for elements, as they are structured closer to the root of the tree. While this is certainly true for repeat accesses, which achieve O(1) time complexity due to being moved to the root, it is unclear at what search frequency the Splay tree loses its competitive restructuring edge. To test this, the times of the Splay tree search operation is compared to the search operation in an AVL tree. Both trees are filled with identical random numbers of uniform nature and tested with a find pool of normally distributed numbers to simulate varying degrees of access frequency. The standard deviation of the find pool is increased to locate the point at which the Splay tree loses its edge to the AVL.

RESULTS:

The final standard deviation value of the find pool at which Splay still outperforms AVL is 5. At a stddev value of 5 the difference is minimal, but Splay is still marginally faster, after that point, the difference begins to grow considerably with AVL being faster. 
