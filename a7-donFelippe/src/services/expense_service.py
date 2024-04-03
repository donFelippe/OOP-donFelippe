from src.domain.entities import Expense


class ExpenseService:
    def __init__(self, expense_repository):
        self.__expense_repository = expense_repository

    def add_expense(self, day, value, type):
        expense = Expense(day, value, type)
        self.validate_expense(expense)
        self.__expense_repository.add(expense)
        self.__expense_repository.add_to_history()

    def validate_expense(self, expense):
        max_day = 31
        if expense.get_amount() < 0:
            raise ValueError
        if expense.get_day() > max_day or expense.get_day() <= 0:
            raise ValueError

    def print_all_expenses(self):
        i = 0
        while i < self.__expense_repository.get_count():
            print(self.__expense_repository.get_at(i))
            i = i + 1

    def undo(self):
        if len(self.__expense_repository.history_of_expenses) >= 2:
            self.__expense_repository.undo_step()
        else:
            return False

    def filter_by_value(self, value):
        i = 0
        while i < self.__expense_repository.get_count():
            expense = self.__expense_repository.get_at(i)
            if expense.get_amount() < value:
                self.__expense_repository.delete_by_id(i - 1)
            else:
                i = i + 1
        self.__expense_repository.add_to_history()

    def get_count(self):
        return self.__expense_repository.get_count()
