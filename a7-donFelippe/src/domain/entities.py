class Expense:

    def __init__(self, day, amount, type):
        # Constructor
        self.__day = day
        self.__amount = amount
        self.__type = type

    def get_day(self):
        return self.__day

    def set_day(self, new_day):
        self.__day = new_day

    def get_amount(self):
        return self.__amount

    def set_amount(self, new_amount):
        self.__amount = new_amount

    def get_type(self):
        return self.__type

    def set_type(self, new_type):
        self.__type = new_type

    def __str__(self):
        return f"Day:{self.__day};  Amount: {self.__amount};  Type:{self.__type};"
