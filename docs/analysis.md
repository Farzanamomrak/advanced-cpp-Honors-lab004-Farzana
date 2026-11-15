# Matrix Chain Product and Sequence Alignment

In this lab, I learned how dynamic programming can be used to solve problems by breaking them into smaller subproblems. Instead of solving the same problems multiple times, dynamic programming stores previous results and uses them to solve larger problems. I implemented two algorithms: Matrix Chain-Product and Global Sequence Alignment. Both algorithms use a table to store results and help find an optimal solution.

## 1. Matrix Chain-Product

Matrix Chain-Product finds the most efficient order for multiplying a chain of matrices. The order of the matrices cannot change, but the parentheses can be placed differently. Different multiplication orders can produce the same mathematical result but require different numbers of scalar multiplications.

My implementation uses bottom-up dynamic programming with two tables:

- The cost table stores the minimum multiplication cost for each matrix chain.
- The split table stores the best position to divide each chain.

The algorithm checks different possible split positions and keeps the one with the lowest multiplication cost. After calculating the tables buildParenthesization() uses the split table to recursively reconstruct the optimal multiplication order This also also checks that there are at least two dimensions and that all dimensions are positive. Invalid dimensions cause an invalid_argument exception.

## 2. Matrix Chain-Product Complexity

The time Complexity for matrix chain product is O(n^3) becasue the algorithm uses three nested loops. The first loop considers different chain lengths, the second selects the starting position, and the third tries every possible split position. As the number of matrices increases, the number of calculations grows approximately with the cube of n.

The space Complexity is O(n^2) becasue the algorithm stores two tables: the cost table and the split table. Both tables contain n times n entries, so the space complexity is O(n^2).

## 3. Global Sequence Alignment

Global Sequence Alignment compares two sequences and finds an alignment with the highest possible score. Characters can be matched, mismatched, or aligned with a gap. The default scoring system is:

- Match: +1
- Mismatch: -1
- Gap: -2

My implementation uses a two-dimensional dynamic programming table with dimensions (m+1) times (n+1), where m and n are the lengths of the two input sequences. The first row and first column are initialized using the gap score. The remaining cells are filled by considering three possible transitions:

1. Diagonal: Align two characters and add the match or mismatch score.
2. Vertical: Align a character from the first sequence with a gap.
3. Horizontal: Align a gap with a character from the second sequence.

The algorithm chooses the highest score from these three possibilities. After filling the table, the algorithm starts at the bottom-right corner and works backward to reconstruct the alignment. It uses a hyphen (`-`) to represent gaps. Finally, both aligned strings are reversed because they were constructed backward. The function also supports custom match, mismatch, and gap scores.

## 4. Sequence Alignment Complexity

The time Complexity for sequence alignment complexity is O(mn), where algorithm fills a table containing (m+1)(n+1) cells. Each cell considers three possible transitions, which take constant time. Therefore, the overall time complexity is O(mn). The backtracking process takes at most O(m+n) additional time, which does not change the overall complexity.

The space Complexity is O(mn) where the dynamic programming table stores approximately mn values. The aligned output strings require up to O(m+n) additional space. Therefore, the overall space complexity is O(mn). As the sequence lengths increase, the number of table entries increases based on the product of the two lengths. If both sequences double in length, the table grows to approximately four times its original size.

## 5. Discussion Questions

1. Why does Matrix Chain-Product have optimal substructure?

Matrix Chain-Product has optimal substructure because the best solution to a larger problem depends on the best solutions to smaller subproblems. If we divide a matrix chain into two smaller chains, each smaller chain must also have an optimal multiplication order to produce the best overall result.

2. Why would trying every possible parenthesization become impractical?

The number of possible parenthesizations grows very quickly as the number of matrices increases. Checking every possibility would require a lot of time for larger chains. Dynamic programming avoids repeating calculations by storing the results of smaller subproblems.

3. What information must be stored to reconstruct the optimal parenthesization?

We need to store the best split position for each subproblem. The split table contains this information and allows us to recursively reconstruct the optimal multiplication order.

4. What are the dimensions of the sequence-alignment dynamic programming table?

The table has (m+1) rows and (n+1) columns, where m and n are the lengths of the two sequences. The extra row and column represent empty sequences.

5. Why must the first row and first column be initialized before filling the table?

Because the first row and column represent aligning a sequence with an empty sequence. Each character must be aligned with a gap, so the cells are initialized using the gap penalty. These values are also needed when calculating the other cells.

6. What do the diagonal, vertical, and horizontal transitions represent?

- Diagonal represents aligning two characters, either a match or a mismatch.
- Vertical represents aligning a character from the first sequence with a gap.
- Horizontal represents aligning a gap with a character from the second sequence.

7. How can different match, mismatch, and gap scores change the resulting alignment?

Changing the scoring values can change which alignment is considered optimal. A higher match score rewards matching characters, while a more negative mismatch or gap score discourages those choices. The algorithm uses the scoring values to determine the alignment with the highest total score.

8. Why are DNA sequence alignment and ordinary text comparison structurally similar dynamic programming problems?

Both problems compare two sequences of characters and use similar operations: matching characters, handling mismatches, and inserting gaps. Both can use a dynamic programming table to store the best results for smaller portions of the sequences and then reconstruct an optimal alignment.



This lab helped me understand how dynamic programming can solve optimization problems more efficiently by storing results from smaller subproblems. Matrix Chain-Product uses a cost table and a split table to find the minimum multiplication cost and reconstruct the best order. Global Sequence Alignment uses a scoring table to find the highest-scoring alignment between two sequences.