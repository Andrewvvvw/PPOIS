**Reservation** 5 5 → Customer

**Table** 4 4 →

**DiningSession** 5 5 → Customer Table

**Guest** 4 4 → 

**RegularCustomer** 1 2 →

**VIPCustomer** 3 3 →

**Customer** 3 1 → 

**Accountant** 4 5 → Employee

**Bartender** 4 5 → Employee Drink

**Chef** 4 4 → Employee MenuItem

**Cleaner** 4 4 → Employee

**DeliveryPerson** 4 4 → Employee

**Host** 2 5 → Employee

**Manager** 5 5 → Employee

**SousChef** 4 5  → Employee

**Waiter** 4 5 → Employee

**Employee** 5 2 → 

**Delivery** 5 2 → PurchaseOrder

**StockItem** 5 3 → 

**Inventory** 5 5 → StockItem

**PurchaseOrder** 5 4 → StockItem

**Supplier** 5 4 → 

**Event** 7 5 → Employee

**Feedback** 6 3 → 

**Promotion** 8 5 → Discount

**Survey** 7 5 → 

**AllergenInfo** 5 4 → 

**Appetizer** 4 3 → MenuItem Recipe

**Dessert** 6 5 → MenuItem Recipe

**Drink** 4 1 → MenuItem Recipe Ingredient

**Ingredient** 5 4 → 

**MainCourse** 6 5 → MenuItem Recipe Ingredient

**Recipe** 5 4 → 

**MenuItem** 4 6 → AllergenInfo

**Menu** 3 3 → 

**BillSplitter** 4 5 → Customer

**Discount** 4 3 → 

**Invoice** 5 4 → Order

**LoyaltyProgram** 1 4 →

**OrderItem** 3 1 →

**CardPayment** 5 6 → Invoice

**CashPayment** 4 5 → Invoice

**OnlinePayment** 4 4 → Invoice

**Payment** 5 4 → Invoice

**Order** 8 14 → Customer OrderItem Discount BillSplitter LoyaltyProgram

**Report** 4 2 →

**EmployeePerfomanceReport** 4 5 → 

**FinanceReport** 4 6 →

**SalesReport** 5 5 →

**InventoryReport** 4 5 →

Классы: 50
Поля: 221
Поведения: 146
Ассоциации: 39
Исключения: 12

Исключения:

Exception 1 1 →

ExceptionNegativeCapacity 0 0 →

ExceptionEmptyOrder 0 0 →

ExceptionEmptyPhoneNumber 0 0 →

ExceptionNegativeBillTotal 0 0 →

ExceptionNegativeItemAmount 0 0 →

ExceptionNegativeStockMinimum 0 0 →

ExceptionIncorrectDiscountAmount 0 0 →

ExceptionNegativeQuantity 0 0 →

ExceptionNegativeServiceCharge 0 0 →

ExceptionIncorrectItemPrice 0 0 →

ExceptionIncorrectCustomerAmount 0 0 →

ExceptionEmptyName 0 0 →