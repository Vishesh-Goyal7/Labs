def sorter(inputf, outputf):
    with open(inputf, "r", encoding = "utf-8") as file:
        lines = [line.strip() for line in file.readlines() if line.strip()]
        sorted_line = sorted(lines)

    with open(outputf, "w", encoding="utf-8") as file:
        file.writelines((line + "\n") for line in sorted_line)

    print(f"{inputf} sorted and saved to {outputf}")

ipf = input("Enter input file name : ")
opf = input("Enter output file name : ")

sorter(ipf, opf)