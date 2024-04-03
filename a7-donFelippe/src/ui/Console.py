class Console:

    commands = {
        "A   add transactions",
        "D   display transactions",
        "F   filter transactions",
        "U   undo transactions",
    }

    def read_command(self):
        command = input(">>>")
        command = command.upper()
        if 'A' == command or command == "D" or command == "F" or command == "U" or command == "E" or command == 'X':
            return command
        else:
            print("No such command has been implemented. Please choose A, D , F, U or E")
            return "Y"

    def print_options(self):
        print("Your option (type one letter): ")
        print(*list(self.commands), "E   exit", sep="\n")

    def __init__(self, expense_service):
        self.__expense_service = expense_service
        if self.__expense_service.get_count() == 0:
            self.__add_expenses()

    def run_console(self):
        command_option = ["A", "D", "F", "U", "E"]

        while True:
            self.print_options()
            try:
                command = self.read_command()
            except ValueError:
                command = "Y"
            if command == command_option[0]:
                try:
                    day = int(input("day:"))
                    amount = int(input("amount:"))
                    type = input("type:")
                    self.__expense_service.add_expense(day, amount, type)
                except:
                    print("wrong input")
            elif command == command_option[1]:
                self.__print_all_expenses()
            elif command == command_option[2]:
                try:
                    value = int(input("value:"))
                    self.__expense_service.filter_by_value(value)
                except:
                    print("value not good")
            elif command == command_option[3]:
                try:
                    self.__expense_service.undo()
                except:
                    print("Cant do undo!")
            elif command == command_option[4]:
                break


    def __add_expenses(self):
        self.__expense_service.add_expense(10, 1000, "pizza")
        self.__expense_service.add_expense(2, 200, "hot dog")
        self.__expense_service.add_expense(3, 10, "drytr")
        self.__expense_service.add_expense(5, 16, "dog")
        self.__expense_service.add_expense(16, 45, "hot")
        self.__expense_service.add_expense(7, 16, "hhhhh")
        self.__expense_service.add_expense(8, 20, "hot dog")
        self.__expense_service.add_expense(9, 30, "hot dog")
        self.__expense_service.add_expense(15, 16, "hot dog")
        self.__expense_service.add_expense(18, 8, "hot dog")
        self.__expense_service.add_expense(15, 4, "oana prajita")

    def __print_all_expenses(self):
        self.__expense_service.print_all_expenses()
