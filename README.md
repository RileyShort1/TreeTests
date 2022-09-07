# TreeTests
Testing Splay V. AVL Tree under specific find distributions:

A Splay tree is a variation of the Binary Search Tree that restructures itself upon insert, remove and find operations, moving the element in 
question to the root of the tree with a series of rotations called Splaying. It is commonly cited that with the properties aforementioned it can achieve faster find times of recently searched for elements, as they are structured closer to the root of the tree. While this is certainly true for repeat accesses, which achieve O(1) time complexity due to being moved to the root, it is unclear at what standard deviation the Splay loses its competitive restructuring edge. To test this, the times of the Splay tree find operation is compared to the find operation in an AVL tree. Both trees are filled with identical random numbers of uniform nature and tested with a find pool of normally distributed numbers. The standard deviation of the find pool is increased to locate the point at which the Splay tree loses its edge to the AVL.

RESULTS:

xfun::embed_file("graphStddevCompare.pdf")
