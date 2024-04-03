# Given an given_set_of_numbers of integers A, maximize the value of the expression A[m] - A[n] + A[p] - A[q], where m, n, p, q are given_set_of_numbers indices with
# m > n > p > q. For A = [30, 5, 15, 18, 30, 40], the maximum value is 32, obtained as 40 - 18 + 15 - 5.
# Display both the maximum value as well as the expression used to calculate it.
def that_one_weird_sum(given_set_of_numbers, i, j, k, l):
    return given_set_of_numbers[l] - given_set_of_numbers[k] + given_set_of_numbers[j] - given_set_of_numbers[i]


def naive_maximum_value_weird_way_of_calculating_sums(given_set_of_numbers):
    maximumSum = that_one_weird_sum(given_set_of_numbers, 0, 1, 2, 3)
    operand1 = given_set_of_numbers[3]
    operand2 = given_set_of_numbers[2]
    operand3 = given_set_of_numbers[1]
    operand4 = given_set_of_numbers[0]
    for i in range(0, len(given_set_of_numbers) - 3):
        for j in range(i + 1, len(given_set_of_numbers) - 2):
            for k in range(j + 1, len(given_set_of_numbers) - 1):
                for l in range(k + 1, len(given_set_of_numbers)):
                    if maximumSum < that_one_weird_sum(given_set_of_numbers, i, j, k, l):
                        maximumSum = that_one_weird_sum(given_set_of_numbers, i, j, k, l)
                        operand1 = given_set_of_numbers[i]
                        operand2 = given_set_of_numbers[j]
                        operand3 = given_set_of_numbers[k]
                        operand4 = given_set_of_numbers[l]
    print("the maximum sum possible is ", maximumSum, "=", operand4, "-", operand3, "+", operand2, "-", operand1)


# def thiswillgetthebignamemabe(initial_given_set_of_numbers, i, j, k, l, given_set_of_numbers_of_solutions):
#     if i >= len(given_set_of_numbers):
#         thiswillgetthebignamemabe(initial_given_set_of_numbers)
# 2,9
def max1(given_set_of_numbers):
    l = len(given_set_of_numbers)
    if l < 4:
        return False
    maximum = that_one_weird_sum(given_set_of_numbers, 0, 1, 2, 3)
    mat = [[0 for _ in range(l + 1)] for _ in range(l + 1)]
    mat1 = [[0 for _ in range(l + 1)] for _ in range(l + 1)]
    for i in range(1, l + 1):
        for j in range(1, l + 1):
            mat[i][j] = max(mat[i - 1][j], mat[i][j - 1])
            # print(mat[i-1][j],mat[i][j-1])
        if j > i:
            mat[i][j] = max(given_set_of_numbers[j - 1] - given_set_of_numbers[i - 1], mat1[i][j])
            mat1[i][j] = given_set_of_numbers[j - 1] - given_set_of_numbers[i - 1] + mat[i - 1][i - 1]
            print(mat1[i][j])
            if mat1[i][j] >= maximum and i >= 3:
                maximum = mat1[i][j]
    return maximum


def find_maximum(given_set_of_numbers, range_inf, range_sup, index):
    maximum = given_set_of_numbers[range_inf]
    for i in range(range_inf, range_sup):
        maximum = max(maximum, given_set_of_numbers[i])
        index = i
    return maximum


def find_minimum(given_set_of_numbers, range_inf, range_sup, index):
    minimum = given_set_of_numbers[range_inf]
    for i in range(range_inf, range_sup):
        minimum = max(minimum, given_set_of_numbers[i])
        index = i
    return minimum

#lists of complex numbers
def longest_subarray_of_same_modulus_numbers(real_part, complex_part, )

def dynamic_maximum_value_weird_way_of_calculating_sums(given_set_of_numbers):
    index1 = 0
    index2 = 0
    index3 = 0
    index4 = 0
    operand1 = find_maximum(given_set_of_numbers, 3, len(given_set_of_numbers), index1)
    operand2 = find_minimum(given_set_of_numbers, 2, index1, index2)
    operand3 = find_maximum(given_set_of_numbers, 1, index2, index3)
    operand4 = find_minimum(given_set_of_numbers, 0, index3, index4)
    sum = operand1 - operand2 + operand3 - operand4
    print("The maximum weird sum is obtained by computing ", operand1, "-", operand2, "+", operand3, "-", operand4, "=",
          sum)


dynamic_maximum_value_weird_way_of_calculating_sums([30, 5, 15, 18, 30, 40])
naive_maximum_value_weird_way_of_calculating_sums([30, 5, 15, 18, 30, 40])
given_set_of_numbers = [30, 5, 15, 18, 30, 40]
print(max1(given_set_of_numbers))
