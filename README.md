# Assignment 1 - Word Ladder


## 1. Overview

This project implements the **Word Ladder** problem, a classic algorithmic challenge where a word is transformed into another by changing one letter at a time, ensuring that each intermediate word is valid. The solution is designed for **efficiency and scalability**, leveraging **Breadth-First Search (BFS)** for optimal pathfinding and carefully selecting **data structures** to enhance performance.  

Key optimizations include the use of **`std::vector`**, **`std::queue`**, and **`std::unordered_set`** to efficiently store and process words while minimizing redundant computations. Additionally, **pass-by-reference** is utilized where necessary to improve performance and reduce unnecessary copies.  

A **word ladder** is a connection from one word to another, formed by changing one letter at a time, with the constraint that each transformation yields a valid dictionary word. For example, a word ladder connecting `"code"` to `"data"` might look like:  

The project includes:  
- **Test cases** for validating correctness  
- **Benchmarking methods** to measure performance  
- **Main driver (`main.cpp`)** for compiling and running the solution  

The implementation is structured to allow easy extension, enabling users to **add more test cases, measure performance, and experiment with different optimizations**.  


```txt
code -> cade -> cate -> date -> data
```

Many word ladders will have multiple solutions, such as connecting "work" to "play".

```txt
work fork form foam flam flay play
work pork perk peak pean plan play
work pork perk peak peat plat play
work pork perk pert peat plat play
work pork porn pirn pian plan play
work pork port pert peat plat play
work word wood pood plod ploy play
work worm form foam flam flay play
work worn porn pirn pian plan play
work wort bort boat blat plat play
work wort port pert peat plat play
work wort wert pert peat plat play
```

Example:

```cpp
word_ladder::generate("awake", "sleep", english_words);
// returns {
//   {"awake","aware","sware","share","sharn","shawn","shewn","sheen","sheep","sleep"}
//   {"awake","aware","sware","share","shire","shirr","shier","sheer","sheep","sleep"}
// }
word_ladder::generate("airplane", "tricycle", engish_words);
// returns {}
```

## 2. Understanding a Word Ladder Implementation

Finding a word ladder is a specific instance of a [shortest-path problem][ssp], where the challenge
is to find the shortest path from a starting position to a goal. Shortest-path problems come up in a
variety of situations, such as packet routing, robot motion planning, social networks, and studying
gene mutations. One approach for finding a shortest path is the classic breadth-first search
algorithm. A breadth-first search searches outward from the start in a radial fashion, until it hits
the goal. For our word ladder, this means examining those ladders that represent one hop from the
start. A “hop” is a change in letter. One “hop” from the start means one changed letter, two “hops”
means two changed letters, and so on. It’s possible for the same position in a word to have letter changes
across multiple non-adjacent hops. If any of these reach the destination, we’re done. If not, the
search now examines all the ladders that add one more hop. By expanding the search at each step, all
one-hop ladders are examined before two-hop ladders, and three-hop ladders are only taken into
consideration if none of the one-hop or two-hop ladders work out; thus the algorithm is guaranteed
to find the shortest successful ladder.

Breadth-first searches are typically implemented using a queue. The queue stores partial ladders
that represent possibilities to explore. The ladders are enqueued in order of increasing length. The
first elements enqueued are all the one-hop ladders, followed by the two-hop ladders, and so on. Due
to FIFO handling, ladders will be dequeued in order of increasing length. The algorithm operates by
dequeuing the front ladder from the queue and determining if it reaches the goal. If it does, then
you have a complete ladder, and it is the shortest. If not, you take that partial ladder and extend
it to reach words that are one more hop away, and enqueue those ladders onto the queue, to be
examined later. If you exhaust the queue of possibilities without having found a completed ladder,
you can conclude that no ladder exists.

A few of these tasks deserve a bit more explanation. For example, you’ll need to find all the _valid_ words
that differ by one letter from a given word. You might reach for a raw loop to change each letter to
all the other letters in the alphabet. You may try something more targetted. Either way, repeat this for each letter position in the word and you will have discovered all the words that are one letter away.

Another, more subtle issue, is the restriction that you shouldn’t reuse words that have been
included in a previous ladder. This is an optimisation that avoids exploring redundant paths. For
example, if you previously tried the ladder `cat->cot->cog` and are now processing `cat->cot->con`,
you would find that the word `cog` is one letter away from `con`, which looks like a potential
candidate to extend this ladder. However, `cog` has already been reached in an earlier (and thus
shorter) ladder, so there is no point in reconsidering it in a longer ladder. The simplest way to
ensure this is to keep track of the words that have been used in any ladder, and ignore them when
they resurface. This is also necessary to avoid getting trapped in circular, non-terminating ladders
such as `cat->cot->cog->bog->bat->cat`. Since you need linear access to all of the items in a
word ladder when time comes to return it, it makes sense to model an individual word ladder using
`std::vector<std::string>`. Remember that because C++ has value semantics, you’re able to copy
vectors via copy construction (e.g. `auto word_ladder_clone = word_ladder;`) and copy assignment
(e.g. `word_ladder_clone = word_ladder`).

**If there are multiple shortest paths, your implementation must return all the solutions, sorted in
lexicographical (alphabetical) order. Thus, the return type for your word ladder generator will be
`std::vector<std::vector<std::string>>`.**
