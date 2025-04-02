# from itertools import combinations

# class SubsetGenerator:
#     def __init__(self, nums):
#         self.nums = nums

#     def get_subsets(self):
#         subsets = []
#         for i in range(len(self.nums)):
#             subsets.extend(combinations(self.nums, i))
#         return [list(subset) for subset in subsets]

# nums = [1, 2, 3]
# generator = SubsetGenerator(nums)
# unique_subsets = generator.get_subsets()

# print("Unique subsets:", unique_subsets)


from itertools import combinations

class subsetGenerator:
    def __init__(self, nums):
        self.nums = nums
    def generatre(self):
        subsets = []
        for i in range(len(self.nums)+1):
            subsets.extend(combinations(self.nums, i))
        return [list(subset) for subset in subsets]

nums = list(map(int, input("Enter numbers : ").split()))

generator = subsetGenerator(nums)
subsets = generator.generatre()
print(subsets)