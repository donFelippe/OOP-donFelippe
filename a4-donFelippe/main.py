# backtracking: 12
import sys


def decimalToBinary(decimal):
    return "{0:b}".format(int(decimal))


def backtrack_iterative(array):
    length = len(array)
    for i in range(2 ** (length - 1), 2 ** length):
        operation_order = int(decimalToBinary(i)) % (10 ** (length - 1))
        sum = 0
        type_array = []
        for j in range(length, 0, -1):
            if operation_order % 10 == 0:
                sum += array[j - 1]
                type_array.append("+")
                type_array.append(str(array[j - 1]))
                # print("+",array[j-1], end=" ")
            else:
                sum -= array[j - 1]
                type_array.append("-")
                type_array.append(str(array[j - 1]))
                # print("-", array[j-1], end=" ")
            operation_order //= 10
        if sum >= 0:
            # sys.stdout.write("\033[K") - pot sterge ultima linie din consola
            for i in range(0, len(type_array)):
                print(type_array[i], end="")
            print("=", sum)


def backtrack_recursive(array, index, totalSum, typeArray):
    if index == 0:
        if totalSum >= 0:
            for j in range (0, len(typeArray)):
                print(typeArray[j], end="")
            print('=', totalSum)
        return -1
    typeArray.append("+")
    typeArray.append(array[index])
    backtrack_recursive(array, index - 1, totalSum + array[index], typeArray)
    typeArray.pop()
    typeArray.pop()
    typeArray.append("-")
    typeArray.append(array[index])
    backtrack_recursive(array, index - 1, totalSum - array[index], typeArray)
    typeArray.pop()
    typeArray.pop()
# dynamic: 6


array = [4, 2, 5, 3]
print("Iterative backtracking:")
backtrack_iterative(array)
print("Recursive backtracking:")
backtrack_recursive(array, len(array) - 1, array[0], [array[0]])
