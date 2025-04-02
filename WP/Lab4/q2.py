class PairFinder:
    def __init__(self, nums):
        self.nums = nums

    def find_pair(self, target):
        index_map = {}  # Dictionary to store numbers and their indices
        for i, num in enumerate(self.nums):
            complement = target - num
            if complement in index_map:
                return [index_map[complement], i]  # Return indices of the two numbers
            index_map[num] = i
        return None  # Return None if no pair is found

# Example usage
nums = [2, 7, 11, 15]
target = 9
finder = PairFinder(nums)
result = finder.find_pair(target)

print("Indices of pair:", result)  # Output: [0, 1] (2 + 7 = 9)
