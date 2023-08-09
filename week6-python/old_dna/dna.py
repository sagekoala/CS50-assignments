import csv
import sys
import string
import re

def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: python dna.py [file.csv] [file.txt]")
        sys.exit()

    # Declaring empty list-of-dictionaries for database file, and DNA sequence file, respectively.
    database_list = []

    # Declaring empty list to store dictionaries from database into
    people = []

    # TODO: Read database file into a variable
    count = 0
    with open(sys.argv[1], "r") as csvfile:
        csv_reader = csv.DictReader(csvfile)
        for row in csv_reader:
            people.append(row)

    # TO BE COMPLETED LATER #
    # Want to filter out duplicate dictionaries in people list
    seen = set()
    new_list = []
    for d in people:
        t = tuple(d.items())
        if not t[0] in seen:
            seen.add(t)
            new_list.append(d)

    print(new_list)


    # TODO: Read DNA sequence file into a variable
    str_dna = ""
    with open(sys.argv[2], "r") as txtfile:
        for line in txtfile:
            str_dna = line

    """
    # TODO: Find longest match of each STR in DNA sequence
    # First create patterns
    agat = "^AGAT"
    aatg = "^AATG"
    tatc = "^TATC"

    # Loop for AGAT
    count = 0
    repeats_agat = []
    repeats_aatg = []
    repeats_tatc = []

    # initialize repeats lists to have 0 values
    for i in range(len(str_dna)):
        repeats_agat.append(0)
        repeats_aatg.append(0)
        repeats_tatc.append(0)


    for i in range(len(str_dna)):
        for j in range(i, len(str_dna)):
            if re.match(agat, str_dna[j:j+4]):
                count += 1
            else:
                repeats_agat[i] = count
                count = 0
                break

    for i in range(len(str_dna)):
        for j in range(i, len(str_dna)):
            if re.match(aatg, str_dna[j:j+4]):
                count += 1
            else:
                repeats_aatg[i] = count
                count = 0
                break

    for i in range(len(str_dna)):
        for j in range(i, len(str_dna)):
            if re.match(tatc, str_dna[j:j+4]):
                count += 1
            else:
                repeats_tatc[i] = count
                count = 0
                break

    print("REPEATS TATC")
    print(repeats_agat)

    print("REPEATS AATG")
    print(repeats_aatg)

    print("REPEATS TATC")
    print(repeats_tatc)
    """


    # TODO: Check database for matching profiles

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

main()
