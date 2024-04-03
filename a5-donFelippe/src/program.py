#
# Write the implementation for A5 in this file

def _arrays_adding_a_complex_number(real_part, complex_part, a, b):
    real_part.append(a)
    complex_part.append(b)


def adding_a_complex_number(dictionary, a, b, index):
    complex_number=_dictionary_create_a_complex_number(a,b)
    dictionary.append(complex_number)

def _dictionary_create_a_complex_number(real_part, complex_part):
    return {'real_part': real_part, 'complex_part': complex_part}

def _list_create_a_complex_number(real_part, complex_part):
    return [real_part, complex_part]

def _dictionary_get_real_part(complex_number):
    return complex_number['real_part']

def _dictionary_get_complex_part(complex_number):
    return complex_number['complex_part']
 #get functions-returneaza partea reala si imaginara
# array
def array_modulus_of_a_complex_number(real_part, complex_part):
    return (real_part ** 2 + complex_part ** 2) ** (1 // 2)


def array_print_a_complex_number(real_part, complex_part):
    print(real_part, "+", complex_part, "i", end=" ")


def longest_subarray_of_equal_elements(array, n, first_element, last_element, constant):
    first_element = 0
    last_element = 0
    count = 0
    for i in range(n):
        if array[i] == constant:
            count += 1
            last_element += 1
        else:
            length = max(last_element - first_element + 1, count)
            count = 0
            constant = array[i]
            first_element = last_element + 1
            last_element += 1
    if count > 0:
        length = max(last_element - first_element + 1, count)


def arrays_longest_subrray_of_same_modulus(real_part, complex_part):
    moduluses = []
    for i in range(0, len(real_part)):
        moduluses[i] = array_modulus_of_a_complex_number(real_part[i], complex_part[i])
    first_element = 0
    last_element = 0
    longest_subarray_of_equal_elements(moduluses, len(moduluses), first_element, last_element, moduluses[0])
    print("The longest subarray of equal elements with the same modulus is:")
    for i in range(first_element, last_element):
        array_print_a_complex_number(real_part[i], complex_part[i])


def menu():
    problem = int(input(
        "1.Read a list of complex numbers from the console.\n' 2.Display the entire list of numbers on the console.\n 3.Display on the console the sequence, subarray or numbers required by the properties that were assigned to you. Each student will receive one property from Set A and another one from Set B.\n 4.Exit the application."))
    if problem == 1:
        number_of_elements = int(input("How many elements do you want to input?"))
        for i in range(0, number_of_elements):
            a = int(input('\033[F'))
            print("+")
            b = int(input())
            print("i")
            _arrays_adding_a_complex_number(real_part, complex_part, a, b)
            adding_a_complex_number(dictionary_complex_numbers, a, b, i)
        menu()

    if problem == 2:
        # print form lists
        for i in range(0, len(real_part)):
            print(real_part[i], "+", complex_part[i], "i", '\n')
        # print form dictionary
        for key in dictionary_complex_numbers:

        menu()
    # if problem == 3:

    if problem == 4:
        return 0


#
if __name__ == "__main__":
    real_part = []
    complex_part = []
    dictionary_complex_numbers = [{
    }]
    dictionary_index = 0
    # _dictionary_adding_a_complex_number(dictionary_complex_numbers, real_part[dictionary_index],complex_part[dictionary_index], dictionary_index)
    menu()
