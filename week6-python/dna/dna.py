import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: Python [file.csv] [file.txt]")
        sys.exit()

    # TODO: Read database file into a variable
    # Creating an empty list which will serve as a list of dictionaries, each element a person in the database along with their STR stats
    strs = []

    with open(sys.argv[1], "r") as db_file:
        db_reader = csv.DictReader(db_file)
        for row in db_reader:
            strs.append(row)

    # Convert string values to int where applicable
    for person in strs:
        for key, value in person.items():
            if key != 'name':
                person[key] = int(value)

    # TODO: Read DNA sequence file into a variable
    with open(sys.argv[2], "r") as dna_file:
        dna_reader = csv.reader(dna_file)
        for line in dna_reader:
            sequence = ''.join(line)

    # TODO: Find longest match of each STR in DNA sequence
    # Duplicate strs list of dictionaries, initialize STR values to 0
    # Will copy strs dict, initialize values to 0
    temp = {}

    for person in strs:
        for key, value in person.items():
            if key != 'name':
                temp[key] = 0

    # Pass subsequences from values dict to longest_match, update values dictionary with longest match found for each provided subsequence
    for key in temp:
        temp[key] += longest_match(sequence, key)

    count, LENGTH = 0, len(person) - 1

    # TODO: Check database for matching profiles
    for person in strs:
        for key, value in person.items():
            if key != 'name' and person[key] == temp[key]:
                    count += 1
                    if count == LENGTH:
                        print(person['name'].title())
                        sys.exit()
            else:
                count = 0

    print("No match")

    return


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
