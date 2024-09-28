CREATE DATABASE IF NOT EXISTS GameDB;
USE GameDB;


CREATE TABLE Player (
    player_id INT AUTO_INCREMENT PRIMARY KEY,
    username VARCHAR(50) NOT NULL,
    password VARCHAR(50) NOT NULL
);

CREATE TABLE `Match` (
    match_id INT AUTO_INCREMENT PRIMARY KEY,
    finish_time DATETIME NOT NULL,
    duration INT NOT NULL,
    winner_id INT,
    FOREIGN KEY (winner_id) REFERENCES Player(player_id)
);


CREATE TABLE Player_Match (
    match_id INT,
    player_id INT,
    PRIMARY KEY (match_id, player_id),
    FOREIGN KEY (match_id) REFERENCES `Match`(match_id),
    FOREIGN KEY (player_id) REFERENCES Player(player_id)
);

INSERT INTO Player (username, password) VALUES ('player1', 'password1');
INSERT INTO Player (username, password) VALUES ('player2', 'password2');
INSERT INTO Player (username, password) VALUES ('player3', 'password3');


INSERT INTO `Match` (finish_time, duration, winner_id) VALUES ('2023-09-15 18:30:00', 90, 2);
INSERT INTO `Match` (finish_time, duration, winner_id) VALUES ('2023-09-16 19:45:00', 120, 3);

INSERT INTO Player_Match (match_id, player_id) VALUES (1, 1);
INSERT INTO Player_Match (match_id, player_id) VALUES (1, 2);
INSERT INTO Player_Match (match_id, player_id) VALUES (2, 1);
INSERT INTO Player_Match (match_id, player_id) VALUES (2, 3);

