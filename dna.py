# Identifies to whom a sequence of DNA belongs

import csv
import sys
import random


def main():
    # Ensure correct usage
    if len(sys.argv) != 3:
        print("error")
        sys.exit("Usage: python dna.py FILENAME sequence-string")

    # Read sequences into memory from file
    sequences = []
    with open(sys.argv[1]) as file:
        reader = csv.DictReader(file)
        person = reader.fieldnames
        for row in reader:
            sequences.append(row)

    # generate a dictionary for the sequence
    person.pop(0)
    person_dict = dict.fromkeys(person, 0)
    
    # read sequence into memory
    sequence = open(sys.argv[2])
    data = sequence.read()
    
    # Compare against database
    for seq in person_dict.keys():
        person_dict[seq] = find_sequence(seq, data)
    
    # Find fit in database
    find_person(person_dict, sequences)
    
# goes over a sequence and finds the maximum of repetitions


def find_sequence(sequence, string):
    consecutive = 0
    for i in range(len(string)):
        counter = find_consecutive(sequence, string, i, 0)
        if (counter > consecutive):
            consecutive = counter
    return consecutive

# finds the amount of times the sequence repeats at that point


def find_consecutive(sequence, string, i, count):
    if(string[i:i+len(sequence)] == sequence):
        count += 1
        count = find_consecutive(sequence, string, i+len(sequence), count)
    return count

# finds a person that matches or gives that no one was found


def find_person(person, db):
    for entry in db:
        matches = 0
        for seq in person:
            if (person[seq] == int(entry[seq])):
                matches += 1
        if matches == len(person):
            print(entry['name'])
            sys.exit()
    
    print('No match')
    
    
if __name__ == "__main__":
    main()
