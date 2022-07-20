import csv
import sys


def main():
    # Check for command-line usage
    if len(sys.argv) == 3:
        # database = csv.reader(sys.argv[1])  # 这个还要关闭
        with open(sys.argv[1]) as database:
            reader = csv.reader(database)
            # 当用next()函数读取文件时，如果只执行一次默认读取第一行
            all_subseq = next(reader)[1:]

            # 在文件1打开的情况下打开文件2，不然就是I/O operation on closed file.
            # sequence = open(sys.argv[2], "r")
            with open(sys.argv[2]) as sequence:
                s = sequence.read()
                # Find longest match of each STR in DNA sequence
                # two methods: get_maximum_length_substring or longest_match
                actual = [get_maximum_length_substring(s, sub) for sub in all_subseq]

            # Check database for matching profiles
            print_match(reader, actual)

    else:
        print("Usage: python dna.py data.csv sequence.txt")
        exit(1)
    return


def print_match(reader, actual):
    for line in reader:
        person = line[0]
        values = [int(val) for val in line[1:]]
        if values == actual:
            print(person)
            return
    print("No match")


# answer 1: from the cs50
def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


# answer 2: reference to https://www.youtube.com/watch?v=5Cv-5_zfo_Y
def get_maximum_length_substring(s, sub):
    ans = [0] * len(s)
    for i in range(len(s)-len(sub), -1, -1):
        if s[i:i+len(sub)] == sub:
            if i + len(sub) > len(s) - 1:
                ans[i] = 1
            else:
                ans[i] = ans[i + len(sub)] + 1
    return max(ans)


main()