from cs50 import get_string
number = get_string("Number: ")
while True:
    try:
        trynum = int(number)
        break
    except:
        number = get_string("Number: ")

sum = 0
length = len(number)
if length % 2 == 0:
    for i in range(0, len(number), 2):
        num = int(number[i]) * 2
        if num >= 10:
            sum += int(str(num)[0])
            sum += int(str(num)[1])
        else:
            sum += int(num)
        sum += int(number[i+1])
else:
    sum += int(number[0])
    for i in range(1, len(number), 2):
        num = int(number[i]) * 2
        if num >= 10:
            sum += int(str(num)[0])
            sum += int(str(num)[1])
        else:
            sum += num
        sum += int(number[i+1])
if str(sum)[1] != "0":
    print("INVALID")
elif int(number[0:2]) in [34, 37] and len(number) == 15:
    print("AMEX")
elif int(number[0:2]) in [51, 52, 53, 54, 55] and len(number) == 16:
    print("MASTERCARD")
elif int(number[0]) == 4 and len(number) in [13, 16]:
    print("VISA")
else:
    print("INVALID")