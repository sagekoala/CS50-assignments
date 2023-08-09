-- Keep a log of any SQL queries you execute as you solve the mystery.
-- Searching crime_scene_reports table based on street name and date provided
-- Description of 1 entry cites CS50 duck robbery, 10:15 am and the bakery on Humphrey Street
SELECT * FROM crime_scene_reports
WHERE month = 7
AND year = 2021
AND day = 28
AND street = 'Humphrey Street';

-- Searching interviews database based on crime date, keyword thief in the transcript
-- Discovered that thief left parking lot in a car within 10 minutes after the crime (check security footage of parking lot if exists)
-- Bakery is called Emma's Bakery (or a bakery owned by Emma)
-- Note: Eugene recognized the thief but does not know his name
-- Thief was withdrawing money at ATM on Leggett Street
-- Planning to take earliest flight out of Fiftyville tomorrow (July 29, 2021)
SELECT * FROM interviews
WHERE month = 7
AND year = 2021
AND day = 28
AND transcript LIKE ("%thief%");

-- Searching FLIGHTS table for earliest flight on July 29
-- Earliest flight at 8:20 from origin airport 8, destination airport 4
-- id in flights is primary key, and is the related to foreign key(flight_id in passengers)
SELECT id FROM flights
WHERE day = 29 AND year = 2021 AND month = 7
ORDER BY hour, minute
LIMIT 1;

-- Using the destination airport from earliest flight in found in the query above
-- Can calculate where the robber fled to
SELECT * FROM airports WHERE id = (SELECT destination_airport_id FROM flights
WHERE day = 29 AND year = 2021 AND month = 7
ORDER BY hour, minute
LIMIT 1);

-- Going to search passengers based on passport number
-- This provides us with passport number from all passengerss on that took the earliest flight
-- on July 29 (the day after the robbery)
SELECT * FROM PASSENGERS
WHERE flight_id = (SELECT id FROM flights
WHERE day = 29 AND year = 2021 AND month = 7
ORDER BY hour, minute
LIMIT 1);

-- The people table has a column for passport number
-- Can return subquery of passport numbers from passengers table for all passengers on earliest flight
-- Can return data for all people that correspond to that list of passport numbers
-- Returns a person id (can be used in bank_accounts table) AND
-- phone_number can be used in phone_calls table (caller or receiver)
-- Recall from the interviews database that ((-- Thief was withdrawing money at ATM on Leggett Street --))
SELECT * FROM people
WHERE passport_number IN
    (SELECT passport_number FROM PASSENGERS
    WHERE flight_id = (SELECT id FROM flights
    WHERE day = 29 AND year = 2021 AND month = 7
    ORDER BY hour, minute
    LIMIT 1))
ORDER BY passport_number;

-- Pay attention to call duration -- from crime scene interviews (the thief called someone for less than a minute)
-- note thief called the other person "caller", then asked the other person "receiver" to purchase the plane tickets
-- maybe can search the bank accounts
-- Going to write a subquery to provide list of phone_numbers corresponding
-- to the passengers that were on the first flight the morning after the robbery
SELECT * FROM phone_calls
WHERE caller IN
    (SELECT phone_number FROM people
    WHERE passport_number IN
    (SELECT passport_number FROM PASSENGERS
    WHERE flight_id = (SELECT id FROM flights
    WHERE day = 29 AND year = 2021 AND month = 7
    ORDER BY hour, minute
    LIMIT 1)))
AND month = 7
AND day = 28
AND duration < 60;

-- List of all account numbers for customers that withdrew money
-- The day of the crime from an ATM on 'Leggett Street'
SELECT account_number FROM atm_transactions
WHERE atm_location LIKE "%Leggett%"
AND transaction_type = "withdraw"
AND month = 7
AND day = 28;

-- List of all of the person_id for all of the people
-- that withdrew money from ATM on 'Leggett Street' the
-- day of the crime
SELECT person_id from bank_accounts
WHERE account_number IN (SELECT account_number FROM atm_transactions
WHERE atm_location LIKE "%Leggett%"
AND transaction_type = "withdraw"
AND month = 7
AND day = 28);

-- List of person / phone_number / passport_number / license_plate
-- That has person id corresponding to an account number that was used to withdraw money the day
-- of the crime
-- Bruce is the robber
SELECT * FROM people WHERE id = (SELECT person_id from bank_accounts
WHERE account_number IN (SELECT account_number FROM atm_transactions
WHERE atm_location LIKE "%Leggett%"
AND transaction_type = "withdraw"
AND month = 7
AND day = 28));

-- Idea #1 from above:
-- Use license_plate number in security footage table
-- Crime scene report stated that the thief left parking lot within 10 minutes of the robbery
SELECT * FROM bakery_security_logs
WHERE license_plate
IN (SELECT license_plate FROM people WHERE id = (SELECT person_id from bank_accounts
    WHERE account_number IN (SELECT account_number FROM atm_transactions
    WHERE atm_location LIKE "%Leggett%"
    AND transaction_type = "withdraw"
    AND month = 7
    AND day = 28)));

-- Idea #2: Search for accomplice that purchased the plane tickets for the robber's escape
-- We know that the robber called the accomplice after the crime
-- Using robber's phone number can look up receiver's phone number in phone_calls table
-- Then cross reference that against the phone numbers in the people table
-- This returns the receiver number
SELECT * FROM phone_calls
WHERE caller = (SELECT phone_number FROM people WHERE id = (SELECT person_id from bank_accounts
WHERE account_number IN (SELECT account_number FROM atm_transactions
WHERE atm_location LIKE "%Leggett%"
AND transaction_type = "withdraw"
AND month = 7
AND day = 28)))
AND day = 28
and duration <= 60;


SELECT * FROM people
WHERE phone_number = (SELECT receiver FROM phone_calls
WHERE caller = (SELECT phone_number FROM people WHERE id = (SELECT person_id from bank_accounts
WHERE account_number IN (SELECT account_number FROM atm_transactions
WHERE atm_location LIKE "%Leggett%"
AND transaction_type = "withdraw"
AND month = 7
AND day = 28)))
AND day = 28
and duration <= 60);










