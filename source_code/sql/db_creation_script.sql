--
-- Tables creation
--

-- Adding the user storage table
CREATE TABLE IF NOT EXISTS ETUser (
    username VARCHAR(150) NOT NULL,
    password TEXT NOT NULL,  -- It's advised to store hashed passwords, not plain text.
    birth DATE NOT NULL,
    email TEXT NOT NULL,
    gender ENUM('m', 'f'),
    budget REAL NOT NULL,
    auth_attempt INT NOT NULL,
    last_auth_attempt TIMESTAMP DEFAULT NULL,
    PRIMARY KEY (username)  -- Makes the username a unique identifier for each user
);

-- Adding the reminders storage table
CREATE TABLE IF NOT EXISTS Reminder (
    id_rem SERIAL PRIMARY KEY,
    name_rem TEXT NOT NULL,
    date_rem DATE NOT NULL,
    user VARCHAR(150) NOT NULL,
    FOREIGN KEY (user) REFERENCES ETUser(username)
);

-- Adding the categories storage table
CREATE TABLE IF NOT EXISTS Category (
    id_cat SERIAL PRIMARY KEY,
    name_cat TEXT NOT NULL,
    color TEXT NOT NULL,
    user VARCHAR(150) NOT NULL,
    FOREIGN KEY (user) REFERENCES ETUser(username)
);

-- Adding the expenses storage table
CREATE TABLE IF NOT EXISTS Expense (
    id_exp SERIAL PRIMARY KEY,
    name_exp TEXT NOT NULL,
    desc_exp TEXT NOT NULL,
    date_exp DATE NOT NULL,
    value_exp REAL NOT NULL,
    cat_exp BIGINT UNSIGNED,
    user VARCHAR(150) NOT NULL,
    FOREIGN KEY (cat_exp) REFERENCES Category(id_cat),
    FOREIGN KEY (user) REFERENCES ETUser(username)
);
