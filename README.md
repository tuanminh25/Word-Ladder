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

## **2. Understanding a Word Ladder Implementation**  

Finding a word ladder is a **shortest-path problem**, commonly seen in **packet routing, robot motion planning, social networks, and gene mutation studies**. To solve this efficiently, I use the **breadth-first search (BFS) algorithm**, which expands outward from the start word in layers until reaching the goal. Each "hop" represents a **single-letter change**, ensuring the shortest path is found.  

BFS is implemented using a **queue** that stores word ladders in increasing length order. At each step, I dequeue the shortest ladder, check if it reaches the target, and, if not, extend it by adding valid **one-letter transformations** before re-enqueuing. If no valid ladder is found, I conclude that no solution exists.  

To generate valid transformations, I systematically modify each letter of the word while ensuring that each transformation forms a valid dictionary word. Additionally, I prevent redundant computations by tracking used words, ensuring words are not revisited in longer ladders. This avoids **cycles** like `cat -> cot -> cog -> bog -> bat -> cat`.  

Since **multiple shortest paths** may exist, my implementation **returns all solutions in lexicographical order**, using `std::vector<std::vector<std::string>>` as the return type. Each word ladder is stored in a `std::vector<std::string>`, allowing efficient cloning and modifications through C++’s value semantics.  
