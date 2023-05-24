import re
from dataclasses import dataclass, field
import uuid
import copy

@dataclass(frozen=True)
class CustomerId:
    value: str

    @staticmethod
    def validated(value):
        if not isinstance(value, str):
            raise ValueError("Customer ID must be a string")
        if not re.match(value,r"^[A-Za-z]{3}\d{5}[A-Za-z]{2}-[AQ]$"): # 3 letters, 5 digits, 2 letters, -A or -Q
            raise ValueError("Customer ID must be formatted correctly")
        return value

@dataclass(frozen=True)
class SKU:
    code: str

    @staticmethod
    def validated(code):
        if not isinstance(code, str):
            raise ValueError("SKU must be a string")
        if not re.match(r"^[A-Z]{3}_[A-Z]{3}_\d{2}$", code):
            raise ValueError("SKU must be formatted correctly")
        return code

@dataclass(frozen=True)
class Quantity:
    value: int

    @staticmethod
    def validated(value):
        if not isinstance(value, int):
            raise ValueError("Quantity must be an integer")
        if value <= 0:
            raise ValueError("Quantity must be greater than 0")
        return value

@dataclass(frozen=True)
class Catalog:
    sku: str
    description: str
    price: float

def validate_has_sku(catalog, sku):
    if sku not in catalog:
        raise ValueError(f"Invalid SKU: {sku}")

class Cart:
    id: str
    customer_id: CustomerId
    items: dict = field(default_factory=dict)

    def __init__(self, customer_id, catalog, inventory):
        self.id = str(uuid.uuid4())
        self.customer_id = CustomerId.validated(customer_id)
        self.items = {}
        self.catalog = catalog
        self.inventory = inventory

    def add_items(self, sku, quantity):
        sku = SKU.validated(sku)
        self.catalog.validate_has(sku)
        quantity = Quantity.validated(quantity)
        if sku in self.items:
            current_quantity = self.items[sku]
            new_quantity = current_quantity + quantity.value
            if new_quantity <= self.inventory[sku].quantity:
                self.items = copy.deepcopy(self.items)
                self.items[sku] = new_quantity
            else:
                raise ValueError(f"Not enough inventory for SKU: {sku}")
        else:
            if quantity.value <= self.inventory[sku].quantity:
                self.items = copy.deepcopy(self.items)
                self.items[sku] = quantity.value
            else:
                raise ValueError(f"Not enough inventory for SKU: {sku}")

    def remove_item(self, sku):
        SKU.validated(sku)
        self.items = copy.deepcopy(self.items)
        if sku in self.items:
            del self.items[sku]

    def update_item_quantity(self, sku, quantity):
        SKU.validated(sku)
        self.catalog.validate_has(sku)
        quantity = Quantity.validated(quantity)
        if quantity.value <= self.inventory[sku].quantity:
            self.items = copy.deepcopy(self.items)
            self.items[sku] = quantity.value
        else:
            raise ValueError(f"Not enough inventory for SKU: {sku}")

    def total_cost(self):
        total = 0
        for sku, quantity in self.items.items():
            item = self.catalog[sku]
            total += item.price * quantity
        return total

    def get_items_copy(self):
        return copy.deepcopy(self.items)

catalog = {
    "ABC_DEF_21": Catalog("ABC_DEF_21", "Widget", 10.0),
    "ZZZ_BOB_77": Catalog("ZZZ_BOB_77", "Gadget", 20.0),
    "XXX_ROB_77": Catalog("XXX_ROB_77", "Cosa", 15.0),
    "YYY_JIL_77": Catalog("YYY_JIL_77", "Stuff", 200.0),
    "WWW_BIL_77": Catalog("WWW_BIL_77", "Cool stuff", 0.1),
}

inventory = {
    "ABC_DEF_21": Quantity.validated(100),
    "ZZZ_BOB_77": Quantity.validated(200),
    "XXX_ROB_77": Quantity.validated(300),
    "YYY_JIL_77": Quantity.validated(400),
    "WWW_BIL_77": Quantity.validated(500),
}

Catalog.validate_has = validate_has_sku

cart = Cart("ABC12345DE-A", catalog, inventory)
assert isinstance(cart.id, str)
assert isinstance(cart.customer_id, CustomerId)
assert cart.items == {}

cart.add_items("ABC_DEF_21", 2)
cart.add_items("ZZZ_BOB_77", 555551)
cart.add_items("ABC_DEF_21", 1)
assert cart.items == {"ABC_DEF_21": 3, "ZZZ_BOB_77": 1}

cart.remove_item("ABC_DEF_21")
assert cart.items == {"ZZZ_BOB_77": 1}

cart.update_item_quantity("ZZZ_BOB_77", 10)
assert cart.items == {"ZZZ_BOB_77": 10}

cart.update_item_quantity("ZZZ_BOB_77", 3)
assert cart.items == {"ZZZ_BOB_77": 3}

assert cart.total_cost() == 60.0

print("All tests passed successfully!")
