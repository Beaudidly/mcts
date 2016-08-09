# Monte Carlo tree search solver

This is a perfect information game solver. What this means is that it can make a decision on what it finds to be the best possible move from the given state. Such games that meet the criteria of 'perfect information' are tic-tac-toe, othello, checkers, chess, and Go.  

### How it works

##### Anatomy of a Monte Carlo tree
Like any other tree, it consists of nodes. A node needs to store information such as total tracked back to this node, total number of wins from this node, a list of moves to create children from, references to it's children, and a backwards reference to it's parent.

##### Process
The basic steps of a Monte Carlo Tree Search are:
1) Selection - choose the most favored leaf node based off some metric
2) Expansion - generate a child node from the selected leaf's remaining moves
3) Simulation - play out a game where both sides moves are randomly picked by (pseudo)randomness
4) Backpropagation - after the game has been played out and finished, increment the playcount and add the score to each node up the chain by parent reference until the root is reached.

These steps can be repeated cycle limit, or a time limit. More iterrations means more confidence in the decision.

The part that is tricky is the metric that the Selection phase uses. In this implementation, the metric used is the algorithm Upper Confidence Bound 1 applied to trees or UCT for short.
```
(node play count)/(node win count) + C*(ln(root play count)/(node win count))^(0.5)
C = some constant to play with (2^(0.5) seems to be the go to)
```
The idea behind this metric when selecting a node to expand off of is trying to find the right balance between exploring new paths on the tree, and exploiting a move that has a better track record than the rest. The balance can be hard to achieve but important to get right, as too much exploition results in better opportunites being unexplored. And too much exploration causes less tree depth on some moves that could have been exploited, causing less confidence for a decision.

More can be read [here](https://www.wikiwand.com/en/Monte_Carlo_tree_search)


### Software notes:
As of now:

Only tested on Linux using GCC 6.1.1, GNU Make 4.2.1, and C11
