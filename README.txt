 Write a program called trees that does the following:

    It takes a single integer parameter: the number n of data points in the tree.
    It reads n points from standard input. Each point has three integer components, which we call X, Y, and Z.
    As it reads those points, it places them in an initially empty binary tree T1 sorted on the X value. It resolves ties by going to the left.
    It traverses T1 in symmetric order, printing each point to standard output on a separate line in this format:

    (342, 512, 56311232)

    It traverses T1 in preorder, placing each node in an initially empty binary tree T2 sorted on the Y value. It resolves ties by going to the left.
    It traverses T2 in postorder, printing each point on a separate line in the same format as before.
    It reads one more integer from standard input: the probe p, a Y value. It searches for p in T2, printing the last point it encounters as it descends through T2, which might have p itself as its Y value, or its Y value might just be close to p. 
