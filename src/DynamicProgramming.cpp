#include "project/DynamicProgramming.hpp"
#include <algorithm>
#include <limits>
#include <stdexcept>

std::string buildParenthesization(
    const std::vector<std::vector<int>> &split,
    int i,
    int j)
{
    // Base case: a single matrix is returned without parentheses.
    if (i == j)
    {
        return "A" + std::to_string(i + 1);
    }
    // Find the split point for the current range.
    const int k = split[i][j];
    // Recursively build the parenthesized expression.
    return "(" + buildParenthesization(split, i, k) + " x " + buildParenthesization(split, k + 1, j) + ")";
}

MatrixChainResult matrixChainOrder(
    const std::vector<int> &dimensions)
{
    // Validate the input dimensions.
    if (dimensions.size() < 2)
    {
        throw std::invalid_argument("dimensions must contain at least two values");
    }

    for (const int dimension : dimensions)
    {
        if (dimension <= 0)
        {
            throw std::invalid_argument("dimensions must be positive");
        }
    }
    // Number of matrices.
    const int n = static_cast<int>(dimensions.size()) - 1;
    // Initialize the cost and split tables.
    std::vector<std::vector<long long>> cost(n, std::vector<long long>(n, 0));
    std::vector<std::vector<int>> split(n, std::vector<int>(n, 0));
    // Evaluate each chain length.
    for (int length = 2; length <= n; ++length)
    {
        for (int i = 0; i <= n - length; ++i)
        {
            const int j = i + length - 1;
            cost[i][j] = std::numeric_limits<long long>::max();
            // Evaluate each possible split point.
            for (int k = i; k < j; ++k)
            {
                const long long candidate =
                    cost[i][k] +
                    cost[k + 1][j] +
                    1LL * dimensions[i] * dimensions[k + 1] * dimensions[j + 1];
                // Keep the split with the minimum cost.
                if (candidate < cost[i][j])
                {
                    cost[i][j] = candidate;
                    split[i][j] = k;
                }
            }
        }
    }
    // Return the minimum cost, split and parenthesized expression.
    return {
        cost[0][n - 1],
        split,
        buildParenthesization(split, 0, n - 1)};
}

AlignmentResult globalSequenceAlignment(
    const std::string &first,
    const std::string &second,
    int matchScore,
    int mismatchScore,
    int gapScore)
{
    const int rows = static_cast<int>(first.size());
    const int columns = static_cast<int>(second.size());
    // Create the DP table
    std::vector<std::vector<int>> dp(
        rows + 1, std::vector<int>(columns + 1, 0));
    // initialize the first colume
    for (int i = 1; i <= rows; ++i)
    {
        dp[i][0] = i * gapScore;
    }
    // initialize the first row
    for (int j = 1; j <= columns; ++j)
    {
        dp[0][j] = j * gapScore;
    }
    // Fill the DP table.
    for (int i = 1; i <= rows; ++i)
    {
        // check if characters match
        for (int j = 1; j <= columns; ++j)
        {
            const int score =
                first[i - 1] == second[j - 1] ? matchScore : mismatchScore;
            // calculate three possible scores
            const int diagonalScore = dp[i - 1][j - 1] + score;
            const int upScore = dp[i - 1][j] + gapScore;
            const int leftScore = dp[i][j - 1] + gapScore;
            // highest score
            dp[i][j] = std::max({diagonalScore, upScore, leftScore});
        }
    }
    // start at the bottom-right corner of the DP table
    int i = rows;
    int j = columns;
    // store the aligned strings
    std::string alignedFirst;
    std::string alignedSecond;
    // backtrack through the DP table to reconstruct the alignment
    while (i > 0 && j > 0)
    {
        const int score =
            (first[i - 1] == second[j - 1]) ? matchScore : mismatchScore;
        // check if the current cell came from the diagonal
        if (dp[i][j] == dp[i - 1][j - 1] + score)
        {
            alignedFirst += first[i - 1];
            alignedSecond += second[j - 1];
            --i;
            --j;
        }
        // check up
        else if (dp[i][j] == dp[i - 1][j] + gapScore)
        {
            alignedFirst += first[i - 1];
            alignedSecond += '-';
            --i;
        }
        // check left
        else
        {
            alignedFirst += '-';
            alignedSecond += second[j - 1];
            --j;
        }
    }
    // add remaining characters from the first string if any
    while (i > 0)
    {
        alignedFirst += first[i - 1];
        alignedSecond += '-';
        --i;
    }
    // add remaining characters from the second string if any
    while (j > 0)
    {
        alignedFirst += '-';
        alignedSecond += second[j - 1];
        --j;
    }
    // reverse both aligned strings
    std::reverse(alignedFirst.begin(), alignedFirst.end());
    std::reverse(alignedSecond.begin(), alignedSecond.end());
    // return the alignment score and the aligned strings
    return {
        dp[rows][columns],
        alignedFirst,
        alignedSecond};
};
