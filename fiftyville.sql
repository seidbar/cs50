-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Get an overview over crimes on Chamberlin Street
SELECT * FROM crime_scene_reports WHERE street = "Chamberlin Street";

-- Record 295 mentions three witnesses and the courthouse. Find all logs from the courthouse of that day.
SELECT * FROM courthouse_security_logs WHERE day = 28 AND month = 7 AND year = 2020;

-- The witness repot mentioned the time of the crime at 10:15am
SELECT * FROM courthouse_security_logs WHERE day = 28 AND month = 7 AND year = 2020 AND hour = 10;

-- The license plates could be of interest. I will try to find out which persons are behind them
SELECT name FROM courthouse_security_logs JOIN people ON people.license_plate = courthouse_security_logs.license_plate WHERE day = 28 AND month = 7 AND year = 2020 AND hour = 10;

-- The list might be of interest, but I will look into the interviews for more details
SELECT name, transcript FROM interviews WHERE day = 28 AND month = 7 AND year = 2020;

-- The three relevant witness seem to be Ruth, Eugene and Raymond. Ruth claims the thief left within ten minutes via the parking lot (10:25 latest)
-- Eugene claims he saw the person earlier at the ATM on Fifer Street withdrawing money
-- Raymond claims there was a call shorter than a minute. The accomplice was asked to purchase a ticket for the earliest flight out of Fiftyvielle the next morning (29th)

-- With the information the previous query can be refined
SELECT * FROM courthouse_security_logs JOIN people ON people.license_plate = courthouse_security_logs.license_plate 
WHERE activity = "exit" AND day = 28 AND month = 7 AND year = 2020 AND hour = 10 AND minute > 14 AND minute < 26;

-- We are now down to 8 suspects. Let's match this to people who withdrew money earlier at the ATM
SELECT * FROM atm_transactions WHERE transaction_type = "withdraw" AND year = 2020 AND month = 7 AND day = 28 AND atm_location = "Fifer Street";

-- We need to match the accounts to names
SELECT * FROM bank_accounts JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number 
JOIN people ON people.id = bank_accounts.person_id
WHERE transaction_type = "withdraw" AND year = 2020 AND month = 7 AND day = 28 AND atm_location = "Fifer Street";

-- Now we have a list of people who withdrew on that day. We can match that to the people who left the parking lot at the suggested time
SELECT * FROM courthouse_security_logs JOIN people ON people.license_plate = courthouse_security_logs.license_plate 
WHERE activity = "exit" AND day = 28 AND month = 7 AND year = 2020 AND hour = 10 AND minute > 14 AND minute < 26 AND people.id IN 
(SELECT person_id FROM bank_accounts JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number 
JOIN people ON people.id = bank_accounts.person_id
WHERE transaction_type = "withdraw" AND year = 2020 AND month = 7 AND day = 28 AND atm_location = "Fifer Street");

-- There are four suspects left. Let's check who made a phone call at the suggested time.
SELECT * FROM phone_calls JOIN people ON phone_calls.caller = people.phone_number WHERE year = 2020 AND month = 7 AND day = 28 AND duration < 60;

-- Let's match that against the previous list
SELECT * FROM courthouse_security_logs JOIN people ON people.license_plate = courthouse_security_logs.license_plate 
WHERE activity = "exit" AND day = 28 AND month = 7 AND year = 2020 AND hour = 10 AND minute > 14 AND minute < 26 AND people.id IN 
(SELECT person_id FROM bank_accounts JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number 
JOIN people ON people.id = bank_accounts.person_id
WHERE transaction_type = "withdraw" AND year = 2020 AND month = 7 AND day = 28 AND atm_location = "Fifer Street")
AND people.id IN (SELECT people.id FROM phone_calls JOIN people ON phone_calls.caller = people.phone_number WHERE year = 2020 AND month = 7 AND day = 28 AND duration < 60);

-- We now have two suspects left. Let's see if either of them was on a flight on the 29th
SELECT * FROM passengers WHERE flight_id IN (SELECT id FROM flights WHERE month = 7 AND day = 29);

-- Let's match that against our previous query
SELECT * FROM courthouse_security_logs JOIN people ON people.license_plate = courthouse_security_logs.license_plate 
WHERE activity = "exit" AND day = 28 AND month = 7 AND year = 2020 AND hour = 10 AND minute > 14 AND minute < 26 AND people.id IN 
(SELECT person_id FROM bank_accounts JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number 
JOIN people ON people.id = bank_accounts.person_id
WHERE transaction_type = "withdraw" AND year = 2020 AND month = 7 AND day = 28 AND atm_location = "Fifer Street")
AND people.id IN (SELECT people.id FROM phone_calls JOIN people ON phone_calls.caller = people.phone_number WHERE year = 2020 AND month = 7 AND day = 28 AND duration < 60)
AND people.passport_number IN (SELECT passport_number FROM passengers WHERE flight_id IN (SELECT id FROM flights WHERE month = 7 AND day = 29 ORDER BY hour LIMIT 1));

-- The thief is Ernest. Let's find where he escaped to
SELECT * FROM airports WHERE id IN (SELECT destination_airport_id FROM passengers JOIN flights ON flights.id = passengers.flight_id WHERE passport_number = 5773159633);

-- Last, we need to see who he called
SELECT name FROM people WHERE phone_number IN 
(SELECT receiver FROM phone_calls JOIN people ON phone_calls.caller = people.phone_number WHERE name = "Ernest" AND day = 28 AND month = 7 AND duration < 60);
