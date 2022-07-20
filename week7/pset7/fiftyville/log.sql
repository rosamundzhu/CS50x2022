-- Keep a log of any SQL queries you execute as you solve the mystery.

-- July 28, 2021 and
-- that it took place on Humphrey Street.

SELECT description
FROM crime_scene_reports
WHERE month = 7 AND day = 28
    AND street = "Humphrey Street";

-- at 10:15am at the Humphrey Street bakery

SELECT name, transcript
FROM interviews
WHERE transcript LIKE "%bakery%";

-- Ruth: within ten minutes of the theft, get into a car in the bakery parking lot and drive away.
-- Eugene: Emma's bakery; Earlier this morning, ATM on Leggett Street and saw the thief there withdrawing some money.
-- Raymond: they were planning to take the earliest flight out of Fiftyville tomorrow. (for less than a minute)
-- Kiana: Richard take a bite out of his pastry at the bakery before his pastry was stolen from him.

SELECT person_id, name, phone_number, passport_number, license_plate
FROM bank_accounts, people
WHERE account_number IN
    (SELECT account_number
    FROM atm_transactions
    WHERE month = 7 AND day = 28 AND year = 2021
        AND atm_location LIKE "Leggett Street"
        AND transaction_type = "withdraw")
    AND bank_accounts.person_id = people.id;

/*
person_id |  name   |  phone_number  | passport_number | license_plate |
+-----------+---------+----------------+-----------------+---------------+
| 686048    | Bruce   | (367) 555-5533 | 5773159633      | 94KL13X       |
| 514354    | Diana   | (770) 555-1861 | 3592750733      | 322W7JE       |
| 458378    | Brooke  | (122) 555-4581 | 4408372428      | QX4YZN3       |
| 395717    | Kenny   | (826) 555-1652 | 9878712108      | 30G67EN       |
| 396669    | Iman    | (829) 555-5269 | 7049073643      | L93JTIZ       |
| 467400    | Luca    | (389) 555-5198 | 8496433585      | 4328GD8       |
| 449774    | Taylor  | (286) 555-6063 | 1988161715      | 1106N58       |
| 438727    | Benista | (338) 555-6650 | 9586786673      | 8X428L0       |
+-----------+---------+----------------+-----------------+---------------+
*/

SELECT license_plate, activity, minute
FROM bakery_security_logs
WHERE month = 7 AND day = 28
    AND year = 2021 AND hour = 10
    AND minute > 15  AND minute < 35
    AND activity = "exit";


SELECT person_id, name, phone_number, passport_number, people.license_plate
FROM bank_accounts, people
    JOIN (SELECT license_plate, activity, minute
        FROM bakery_security_logs
        WHERE month = 7 AND day = 28
            AND year = 2021 AND hour = 10
            AND minute > 15  AND minute < 35
            AND activity = "exit") AS A
        ON people.license_plate = A.license_plate
WHERE account_number IN
    (SELECT account_number
    FROM atm_transactions
    WHERE month = 7 AND day = 28 AND year = 2021
        AND atm_location LIKE "Leggett Street"
        AND transaction_type = "withdraw")
    AND bank_accounts.person_id = people.id;

/*
-----------+-------+----------------+-----------------+---------------+
| person_id | name  |  phone_number  | passport_number | license_plate |
+-----------+-------+----------------+-----------------+---------------+
| 686048    | Bruce | (367) 555-5533 | 5773159633      | 94KL13X       |
| 514354    | Diana | (770) 555-1861 | 3592750733      | 322W7JE       |
| 396669    | Iman  | (829) 555-5269 | 7049073643      | L93JTIZ       |
| 467400    | Luca  | (389) 555-5198 | 8496433585      | 4328GD8       |
+-----------+-------+----------------+-----------------+---------------+
*/

SELECT caller, receiver, duration
FROM phone_calls
WHERE month = 7 AND day = 28
    AND year = 2021 AND duration < 60
    AND caller IN ("(367) 555-5533", "(770) 555-1861", "(829) 555-5269", "(389) 555-5198");
/*
|     caller     |    receiver    | duration |
+----------------+----------------+----------+
| (367) 555-5533 | (375) 555-8161 | 45       |
| (770) 555-1861 | (725) 555-3243 | 49       |
*/
-- Bruce or Diana

SELECT id, abbreviation, full_name
FROM airports
WHERE city = "Fiftyville";

SELECT id, destination_airport_id, hour, minute
FROM flights
WHERE month = 7 AND day = 29
    AND year = 2021
    AND origin_airport_id = (SELECT id
        FROM airports
        WHERE city = "Fiftyville")
ORDER BY hour
LIMIT 1;

SELECT city
FROM airports
WHERE id = 4;

-- New York City

SELECT id
FROM flights
WHERE month = 7 AND day = 29
    AND year = 2021 AND destination_airport_id = 4;

-- 36

SELECT name
FROM people
WHERE passport_number in
    (SELECT passport_number
    FROM passengers
    WHERE flight_id = 36)
    AND (name = "Bruce" OR name = "Diana");

-- Bruce

/*
   caller     |    receiver
+----------------+------------
| (367) 555-5533 | (375) 555-8161
*/

SELECT name
FROM people
WHERE phone_number = "(375) 555-8161";

-- Robin