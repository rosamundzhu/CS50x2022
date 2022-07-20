def main():
    try:
        num = int(input("Height: "))
    except:
        num = int(input("Height: "))

    if 0 < num <= 8:
        for i in range(num):
            print(" " * (num - i - 1) + "#" * (i + 1), end=("  "))
            print("#" * (i + 1))
    else:
        main()

main()  


