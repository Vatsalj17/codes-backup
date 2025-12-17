class Car:
    totalCars = 0
    def __init__(self, brand, model):
        self.__brand = brand # adding underscore made it private (encapsulation)
        self.__model = model
        Car.totalCars += 1
    def getBrand(self):
        return self.__brand
    def fullName(self):
        return f"{self.__brand} {self.__model}"
    def fuelType(self) -> str:
        return "Petrol or Diesel"

    @staticmethod
    def generalDescription():
        return "Cars are means of Transport"
    
    @property
    def model(self):
        return self.__model

#inheritance
class ElectricCar(Car):
    def __init__(self, brand, model, battery_size):
        super().__init__(brand, model)
        self.battery_size = battery_size
    #polymorphism
    def fuelType(self) -> str:
        return "Electricity"

my_car = Car("Toyota", "Supra")
print(my_car.fullName())
# print(my_car.__brand)
print(my_car.getBrand())
my_car.__model = "city"
print(my_car.__model)
print(my_car.model)

my_tesla = ElectricCar("Tesla", "Model S", "85kWh")
print(my_tesla.fullName())

print(Car.totalCars)
