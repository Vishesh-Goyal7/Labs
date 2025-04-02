import math

def mean(nums):
    return (sum(nums)/len(nums))

def variance(nums):
    mn = mean(nums)
    return (sum((x - mn)**2 for x in nums)/len(nums))

def deviation(nums):
    return math.sqrt(variance(nums))

def main():

    n = int(input("Enter number of element in the list : "))
    nums = [float(input(f"Enter {i+1} list element : ")) for i in range(n)]

    mn = mean(nums)
    var = variance(nums)
    dev = deviation(nums)

    print(f"Mean of numbers : {mn}")
    print(f"Variance of numbers : {var}")
    print(f"Deviation of numbers : {dev}")

if __name__ == "__main__":
    main()