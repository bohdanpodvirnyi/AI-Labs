if __name__ == "__main__":
    ups = 0
    rights = 0
    commands = input()
    destination = input()
    for command in commands:
        if command == "R":
            rights += 1
        elif command == "U":
            ups += 1
    dest = destination.split()
    x = dest[0]
    y = dest[1]
    if x.isdigit() and y.isdigit():
        if ups >= int(y) and rights >= int(x):
            print("YES")
        else:
            print("NO")
    else:
        print("NO")
