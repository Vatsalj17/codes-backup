age = int(input("Enter you age: "))

if age < 13:
    print("Child")
elif age < 20:
    print("Teenager")
elif age < 60:
    print("Adult")
else:
    print("Senior")

day = input("Enter the day: ")
day = day.lower()
print(day)
price = 12 if age >= 18 else 8
if day == "wednesday":
    price -= 2

print("Your Ticket price: ", price)

year = int(input("Enter the year: "))
leapYear = True;
# if year % 4 == 0:
#     if year % 100 == 0:
#         if year % 400 == 0:
#             leapYear = True
#         else:
#             leapYear = False
#     else:
#         leapYear = True
# else:
#     leapYear = False

if (year % 400 == 0) or (year % 4 == 0 and year % 100 != 0):
    leapYear = True
else:
    leapYear = False

if leapYear:
    print("It's a leapyear")
else:
    print("It's not a leapyear")
