#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
bool recursion(int OGwinner, int loser);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (strcmp(name, candidates[j]) == 0)
            {
                ranks[rank] = j;
                return true;
            }
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    pair_count = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    int strength[pair_count]; // Defining an array that will store strength-of-victory according to the preferences array

    // Looping through each pair, storing the winner's strength-of-victory of it's corresponding loser
    for (int i = 0; i < pair_count; i++)
    {
        strength[i] = preferences[pairs[i].winner][pairs[i].loser];
    }

    // Define temp variables, prepare to sort the pairs array in decreasing order according to strength-of-victory
    int temp_strength, temp_win, temp_lose = 0;
    for (int out = 0; out < pair_count; out++)
    {
        for (int inn = out; inn < pair_count; inn++)
        {
            if (strength[inn] > strength[out]) // If value indexed +1 in the strength array is greater than the value at current index, swap
            {
                temp_strength = strength[inn];
                temp_win = pairs[inn].winner;
                temp_lose = pairs[inn].loser;
                strength[inn] = strength[out];
                pairs[inn].winner = pairs[out].winner;
                pairs[inn].loser = pairs[out].loser;
                strength[out] = temp_strength;
                pairs[out].winner = temp_win;
                pairs[out].loser = temp_lose;
            }
        }
    }
    return;
}

bool recursion(int OGwinner, int loser)
{
    for (int j = 0; j < candidate_count; j++)
    {
        if (locked[loser][j] == true && j != OGwinner)
        {
            if (locked[loser][j + 1] == true && j + 1 != OGwinner)
            {
                for (int k = 0; k < candidate_count; k++)
                {
                    if (locked[j + 1][k] && k != OGwinner)
                    {
                        return recursion(OGwinner, k);
                    }
                }
            }
            else if (locked[loser][j + 2] == true && j + 2 != OGwinner)
            {
                for (int k = 0; k < candidate_count; k++)
                {
                    if (locked[j + 2][k] && k != OGwinner)
                    {
                        return recursion(OGwinner, k);
                    }
                }
            }
            else if (locked[loser][j + 3] == true && j + 3 != OGwinner)
            {
                for (int k = 0; k < candidate_count; k++)
                {
                    if (locked[j + 3][k] && k != OGwinner)
                    {
                        return recursion(OGwinner, k);
                    }
                }
            }
            else
            {
                return recursion(OGwinner, j);
            }
        }
        else if (locked[loser][j] == true && j == OGwinner)
        {
            return true;
        }
    }
    return false;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    for (int i = 0; i < pair_count; i++)
    {
        if (!recursion(pairs[i].winner, pairs[i].loser))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{

    // Define struct
    typedef struct
    {
        int candidate;
        bool was_loser;
        bool was_winner;
    }
    losing;

    losing loser[MAX];

    // Initialize struct
    for (int i = 0; i < candidate_count; i++)
    {
        loser[i].candidate = i;
        loser[i].was_loser = false;
        loser[i].was_winner = false;
    }


    // Create a loop to count the number of "true" values that are locked in.
    int true_count = 0;
    for (int i = 0; i < pair_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[i][j] == true)
            {
                loser[j].was_loser = true;
                loser[i].was_winner = true;
            }
        }
    }

    for (int i = 0; i < candidate_count; i++)
    {
        if (loser[i].was_loser == false && loser[i].was_winner != false)
        {
            printf("%s\n", candidates[i]);
        }
    }

    return;
}