CREATE DATABASE banking_system;
USE banking_system;

CREATE TABLE customers (
    customer_id INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(100),
    email VARCHAR(100),
    phone VARCHAR(20)
);

CREATE TABLE accounts (
    account_id INT AUTO_INCREMENT PRIMARY KEY,
    customer_id INT,
    account_number VARCHAR(20) UNIQUE,
    balance DECIMAL(12,2) DEFAULT 0,
    FOREIGN KEY (customer_id) REFERENCES customers(customer_id)
);

CREATE TABLE transactions (
    transaction_id INT AUTO_INCREMENT PRIMARY KEY,
    account_number VARCHAR(20),
    transaction_type VARCHAR(20),
    amount DECIMAL(12,2),
    transaction_date TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);