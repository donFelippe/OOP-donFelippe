import unittest

from src.domain.entities import Expense
from src.services.expense_service import ExpenseService


class ServiceTest(unittest.TestCase):
    def test_add_to_memory_repository_correct_params(self):
        for repository_type in ['memory', 'binary', 'file']:
            initial = ExpenseService(repository_type)
            transaction = Expense(1, 150, "credit")
            initial.add_expense(1, 2, "a")
            self.assertEqual(initial, [transaction])

    def test_add_to_memory_repository_missing_params(self):
        for repository_type in ['memory', 'binary', 'file']:
            initial = ExpenseService(repository_type)
            with self.assertRaises(NameError):
                initial.add_expense(1, 2, '')

    def test_add_to_memory_repository_invalid_params(self):
        for repository_type in ['memory', 'binary', 'file']:
            initial = ExpenseService(repository_type)
            with self.assertRaises(ValueError):
                initial.add_expense(0, 2, "credit")
            with self.assertRaises(ValueError):
                initial.add_expense(32, 2, "credit")
            with self.assertRaises(ValueError):
                initial.add_expense(3, 2 / 5, "water")

    def test_add_to_memory_repository_duplicate_entry(self):
        for repository_type in ['memory', 'binary', 'file']:
            initial = ExpenseService(repository_type)
            initial.add_expense(1, 2, "water")
            with self.assertRaises(NameError):
                initial.add_expense(1, 2, "water")


service_test = ServiceTest()
service_test.test_add_to_memory_repository_correct_params()
service_test.test_add_to_memory_repository_missing_params()
service_test.test_add_to_memory_repository_invalid_params()
service_test.test_add_to_memory_repository_duplicate_entry()
