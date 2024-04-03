import pickle

from src.domain.entities import Expense


class MemoryRepository:

    def __init__(self):
        self.__all_expenses = []
        self.__number_of_all_expenses = 0
        self.history_of_expenses = [[]]

    def add_to_history(self):
        self.history_of_expenses.append(self.__all_expenses.copy())

    def undo_step(self):
        self.history_of_expenses.pop()
        self.__all_expenses = self.history_of_expenses[-1]

    def find_all_expenses(self):

        return list(self.__all_expenses)

    def get_count(self):
        return self.__number_of_all_expenses

    def get_at(self, i):
        return self.__all_expenses[i - 1]

    def get_all(self):
        return self.__all_expenses

    def add(self, expense):
        # self.__all_expenses[self.__nr] = expense
        self.__all_expenses.append(expense)
        self.__number_of_all_expenses = self.__number_of_all_expenses + 1
        #self.history_of_expenses.append(self.__all_expenses.copy())

    def delete_by_id(self, index):
        if index < self.__number_of_all_expenses:
            del self.__all_expenses[index]
            self.__number_of_all_expenses = self.__number_of_all_expenses - 1
        #self.history_of_expenses.append(self.__all_expenses.copy()


class TextFileRepository:
    def __init__(self, filename):
        self.__filename = filename
        self.__length_line = 75
        self.__number_of_lines_in_file = 0
        list_of_all_lines_from_file = []
        # read file

        with open(filename, 'r') as file_repository:
            list_of_all_lines_from_file = file_repository.readlines()
            self.__number_of_lines_in_file = len(list_of_all_lines_from_file)
            file_repository.close()

    def find_all(self):
        return list(self.__all_expenses.amount())

    def get_count(self):
        return self.__number_of_lines_in_file

    def get_at(self, i):
        if i < self.__number_of_lines_in_file:
            lines = []
            with open(self.__filename, 'r') as file_repository:
                lines = file_repository.readlines()
                if len(lines) > i:
                    line_i = lines[i]
                    line_i = line_i.strip()
                    day = int(line_i[0:2])
                    amount = int(line_i[3:23])
                    type = line_i[24:]
                    type = type.strip()
                    expense = Expense(day, amount, type)
                else:
                    expense = Expense(0, 0, '')
                file_repository.close()
                return expense

    def add(self, expense):
        file = open(self.__filename, 'a')
        file.write('%02d %20s %50s\n' % (expense.get_day(), str(expense.get_amount()), expense.get_type()))
        file.close()
        self.__number_of_lines_in_file = self.__number_of_lines_in_file + 1

    def delete_by_id(self, id):
        if id == self.__number_of_lines_in_file - 1:
            file = open(self.__filename, 'r+')
            file.seek(-self.__length_line, 2)
            file.truncate()
            file.close()
            self.__number_of_lines_in_file = self.__number_of_lines_in_file - 1


class BinaryFileRepository:
    def __init__(self, filename):
        self.__filename = filename
        self.__all_expenses = []
        self.__number_of_expenses = 0
        for p in self.read_binary_file():
            self.add(p)

    def read_binary_file(self):
        try:
            file = open(self.__filename, "rb")
            return pickle.load(file)
        except EOFError:
            return []
        except IOError as error:
            raise error

    def write_binary_file(self):
        file = open(self.__filename, "wb")
        pickle.dump(self.__all_expenses, file)
        file.close()

    def find_all(self):
        return list(self.__all_expenses)

    def get_count(self):
        return self.__number_of_expenses

    def get_at(self, i):
        return self.__all_expenses[i]

    def add(self, expense):
        # self.__all_expenses[self.__nr] = expense
        self.__all_expenses.append(expense)
        self.__number_of_expenses = self.__number_of_expenses + 1
        self.write_binary_file()

    def delete_by_id(self, index):
        if index < self.__number_of_expenses:
            del self.__all_expenses[index]
            self.__number_of_expenses = self.__number_of_expenses - 1
            self.write_binary_file()
