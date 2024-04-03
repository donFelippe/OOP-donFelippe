from src.Repository.expense_repository import MemoryRepository
from src.Repository.expense_repository import TextFileRepository
from src.Repository.expense_repository import BinaryFileRepository
from services.expense_service import ExpenseService
from ui.Console import Console
#from repository.expense_repository import BinaryFileRepository


#expense_repository = BinaryFileRepository('')
#expense_repository = TextFileRepository("D:\\UBB\\a7-donFelippe\\TextFIleRepository")
expense_repository = MemoryRepository()
expense_service = ExpenseService(expense_repository)
console = Console(expense_service)
console.run_console()

