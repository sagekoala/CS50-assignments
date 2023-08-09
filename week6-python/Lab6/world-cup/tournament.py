# Simulate a sports tournament

import csv
import sys
import random

# Number of simluations to run
N = 1000


def main():

    # Ensure correct usage
    if len(sys.argv) != 2:
        sys.exit("Usage: python tournament.py FILENAME")

    # Defining an empty list
    teams = []

    # Read teams into memory from file
    # Converting key-values to int then appending dictionary to teams list
    with open(sys.argv[1], "r") as file:
        reader = csv.DictReader(file)
        for dictionary in reader:
            for row in dictionary:
                if len(dictionary[row]) <= 4:
                    dictionary[row] = int(dictionary[row])

            teams.append(dictionary)

    counts = {}
    # Simulate N tournaments and keep track of win counts
    # Populating counts dictionary with teams list, initializing each team to 0
    for t in teams:
        team = t["team"]
        wins = 0
        counts[team] = wins

    simulations = 0
    while simulations != N + 1:
        winner = simulate_tournament(teams)
        for c in counts:
            if c == winner:
                counts[c] += 1
        simulations += 1

    # Print each team's chances of winning, according to simulation
    print("*** Final Results ***")
    print(f"Out of {N} simulations of The World Cup: ")
    for team in sorted(counts, key=lambda team: counts[team], reverse=True):
        print(f"{team}: {counts[team] * 100 / N:.1f}% chance of winning")


def simulate_game(team1, team2):
    """Simulate a game. Return True if team1 wins, False otherwise."""
    rating1 = team1["rating"]
    rating2 = team2["rating"]
    probability = 1 / (1 + 10 ** ((rating2 - rating1) / 600))
    return random.random() < probability


def simulate_round(teams):
    """Simulate a round. Return a list of winning teams."""
    winners = []

    # Simulate games for all pairs of teams
    for i in range(0, len(teams), 2):
        print(f"Simulating round: {teams[i]} v. {teams[i + 1]}")
        if simulate_game(teams[i], teams[i + 1]):
            winners.append(teams[i])
        else:
            winners.append(teams[i + 1])

    print(f"Winner(s): {winners}")
    return winners


def simulate_tournament(teams):
    """Simulate a tournament. Return name of winning team."""
    # TODO
    winner = []
    winner_count = len(teams)

    while winner_count != 1:
        return simulate_tournament(simulate_round(teams))

    for t in teams:
        winning_team = t["team"]
        return winning_team


if __name__ == "__main__":
    main()
