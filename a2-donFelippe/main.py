import random
import timeit


def nRandomNumbers(howmany, array):
    for i in range(0, howmany):
        array.append(random.randint(0, 100))


def bubbleSort(array, step):
    n = len(array)
    step_count=0
    swapped = False
    for i in range(n - 1):
        for j in range(0, n - i - 1):
            if array[j] > array[j + 1]:
                swapped = True
                array[j], array[j + 1] = array[j + 1], array[j]
                step_count += 1
                if (step_count % step == 0):
                    print(array)
        if not swapped:
            print("Finished:", array)


def gnomeSort(arr, length, step):
    index = 0
    step_count=0
    while index < length:
        if index == 0:
            index = index + 1
        if arr[index] >= arr[index - 1]:
            index = index + 1
        else:
            arr[index], arr[index - 1] = arr[index - 1], arr[index]
            index = index - 1
            step_count+=1
            if(step_count%step==0):
                print(array)
    print ("Finished: ", array)


# def selectionSort(array, length):
#     print("selection sort: \n")
#     for i in range(0, length - 1):
#         for j in range(i, length):
#             if array[i] > array[j]:
#                 array[i], array[j] = array[j], array[i]
#     return array


def cases(complexity, sortAlgorithm):
    if sortAlgorithm == 1:
        return 0


def menuChoice(array):
    if array == []:
        problem = int(input(
            "what do you desire: \n 1.Generation of a random array \n 2.Sorting with the help of bubble sort \n 3. Sorting using gnome sort \n 4. Quit the program(with style) \n"))
    else:
        problem = int(input("Any other problem?"))
    if problem == 1:
        howmany = int(input("How many numbrers:"))
        nRandomNumbers(howmany, array)
        menuChoice(array)
    if problem == 2:
        step=int(input("Wich steps do you want to see?"))
        bubbleSort(array, step)
    if problem == 3:
        step=int(input("Wich steps do you want to see?"))
        gnomeSort(array, len(array), step)

    if problem == 4:
        print("Aigth I'm out nerds")
        return 0
    array=[]
    menuChoice(array)
array=[]
menuChoice(array)
