/*
https://leetcode.com/problems/longest-consecutive-sequence/
128. Longest Consecutive Sequence
Medium

7203

336

Add to List

Share
Given an unsorted array of integers nums, return the length of the longest consecutive elements sequence.

You must write an algorithm that runs in O(n) time.

 

Example 1:

Input: nums = [100,4,200,1,3,2]
Output: 4
Explanation: The longest consecutive elements sequence is [1, 2, 3, 4]. Therefore its length is 4.
Example 2:

Input: nums = [0,3,7,2,5,8,4,6,0,1]
Output: 9
 

Constraints:

0 <= nums.length <= 105
-109 <= nums[i] <= 109
*/

//Runtime Error
//4 / 68 test cases passed.
//to do: merge interval
class DSU
{
public:
    vector<int> parent;

    DSU(int n)
    {
        parent = vector<int>(n);
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x)
    {
        if (parent[x] != x)
        {
            //the recursion stops when x == parent[x]
            parent[x] = find(parent[x]);
        }
        return parent[x];
    };

    int unite(int x, int y)
    {
        //merge y into x
        parent[y] = find(parent[x]);

        return parent[y];
    }
};

class Solution
{
public:
    unordered_map<int, int> group_head;
    unordered_map<int, int> group_size;
    int longestConsecutive(vector<int> &nums)
    {
        set<int> snums(nums.begin(), nums.end());
        nums = vector<int>(snums.begin(), snums.end());

        DSU dsu(nums.size());

        int ans = 0;

        for (int num : nums)
        {
            // cout << "num: " << num << endl;
            int h;
            if (group_head.find(num - 1) != group_head.end())
            {
                h = dsu.unite(num - 1, num);
                group_head[num] = h;
                ++group_size[h];
            }
            else if (group_head.find(num + 1) != group_head.end())
            {
                h = dsu.unite(num, num + 1);
                group_head[num] = h;
                ++group_size[h];
            }
            else
            {
                group_head[num] = num;
                h = num;
                ++group_size[h];
            }
            // cout << "head: " << h << endl;
            ans = max(ans, group_size[h]);
        }

        return ans;
    }
};

//Union Find
//https://leetcode.com/problems/longest-consecutive-sequence/discuss/41062/My-Java-Solution-using-UnionFound
//Runtime: 28 ms, faster than 38.15% of C++ online submissions for Longest Consecutive Sequence.
//Memory Usage: 12.6 MB, less than 5.01% of C++ online submissions for Longest Consecutive Sequence.
class DSU
{
public:
    vector<int> parent;

    DSU(int n)
    {
        parent = vector<int>(n);
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x)
    {
        if (x != parent[x])
        {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    void unite(int x, int y)
    {
        //merge y into x
        parent[y] = find(parent[x]);
    }

    int maxUnion()
    {
        unordered_map<int, int> groupSizes;
        int maxSize = 0;

        for (int i = 0; i < parent.size(); ++i)
        {
            ++groupSizes[find(i)];
            maxSize = max(maxSize, groupSizes[find(i)]);
        }

        return maxSize;
    }
};

class Solution
{
public:
    int longestConsecutive(vector<int> &nums)
    {
        int n = nums.size();

        DSU dsu(n);

        unordered_map<int, int> val2idx;

        for (int i = 0; i < n; ++i)
        {
            //ignore duplicate element
            if (val2idx.find(nums[i]) != val2idx.end())
                continue;

            val2idx[nums[i]] = i;

            if (val2idx.find(nums[i] - 1) != val2idx.end())
            {
                dsu.unite(val2idx[nums[i] - 1], i);
            }

            if (val2idx.find(nums[i] + 1) != val2idx.end())
            {
                dsu.unite(i, val2idx[nums[i] + 1]);
            }
        }

        return dsu.maxUnion();
    }
};

//Brute force
//TLE
//66 / 68 test cases passed.
//time: O(N^3), space: O(1)
class Solution
{
public:
    int longestConsecutive(vector<int> &nums)
    {
        int maxStreak = 0;

        for (int num : nums)
        { //O(n)
            int cur = num;
            while (find(nums.begin(), nums.end(), cur + 1) != nums.end())
            {
                //while loop: O(n)
                //find: O(n)
                ++cur;
            }
            //cur in nums, cur+1 not in nums
            maxStreak = max(maxStreak, cur - num + 1);
            // cout << num << ", " << cur << ", " << maxStreak << endl;
        }

        return maxStreak;
    }
};

//Sorting
//Runtime: 16 ms, faster than 93.81% of C++ online submissions for Longest Consecutive Sequence.
//Memory Usage: 11 MB, less than 59.85% of C++ online submissions for Longest Consecutive Sequence.
//time: O(NlogN), space: O(1) or O(N)
class Solution
{
public:
    int longestConsecutive(vector<int> &nums)
    {
        int maxStreak = 0;

        unordered_set<int> snums(nums.begin(), nums.end());
        nums = vector<int>(snums.begin(), snums.end());
        sort(nums.begin(), nums.end());

        int n = nums.size();
        for (int i = 0; i < n;)
        {
            int j = i;
            while (j + 1 < n && nums[j] + 1 == nums[j + 1])
            {
                ++j;
            }
            //nums[i...j] is a group
            maxStreak = max(maxStreak, j - i + 1);
            i = j + 1;
        }

        return maxStreak;
    }
};

//Sorting, with duplicate
//Runtime: 16 ms, faster than 93.81% of C++ online submissions for Longest Consecutive Sequence.
//Memory Usage: 9.8 MB, less than 98.38% of C++ online submissions for Longest Consecutive Sequence.
class Solution
{
public:
    int longestConsecutive(vector<int> &nums)
    {
        if (nums.empty())
            return 0;

        int curStreak = 1;
        int maxStreak = 1;

        sort(nums.begin(), nums.end());

        int n = nums.size();

        for (int i = 1; i < n; ++i)
        {
            if (nums[i] == nums[i - 1])
                continue;
            if (nums[i] == nums[i - 1] + 1)
            {
                //extend old group
                ++curStreak;
            }
            else
            {
                //start a new group
                maxStreak = max(maxStreak, curStreak);
                curStreak = 1;
            }
        }

        //update with last group
        maxStreak = max(maxStreak, curStreak);

        return maxStreak;
    }
};

//Approach 3: HashSet and Intelligent Sequence Building
//Runtime: 16 ms, faster than 93.81% of C++ online submissions for Longest Consecutive Sequence.
//Memory Usage: 11 MB, less than 49.83% of C++ online submissions for Longest Consecutive Sequence.
//time: O(N), space: O(N)
class Solution
{
public:
    int longestConsecutive(vector<int> &nums)
    {
        unordered_set<int> snums(nums.begin(), nums.end());

        int maxStreak = 0;

        for (const int num : snums)
        {
            if (snums.find(num - 1) == snums.end())
            {
                //that means num is the head of its group
                int cur = num;

                /*
                this can only run for n iterations,
                because the outside "if" only let the head of a group in
                */
                while (snums.find(cur + 1) != snums.end())
                {
                    ++cur;
                }

                //[num...cur] is a group
                maxStreak = max(maxStreak, cur - num + 1);
            }
        }

        return maxStreak;
    }
};