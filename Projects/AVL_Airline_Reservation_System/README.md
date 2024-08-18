# Airline Reservation System

This is a simple airline reservation system implemented in C++. The system allows users to sign up, sign in, reserve flights, cancel reservations, and view flight information. It also includes an admin panel for administrators to manage flights, view reservations, and delete flights.

## Data Structure: AVL Tree

The system uses an AVL tree data structure to store flight information. An AVL tree is a self-balancing binary search tree that maintains a relatively small height by rotating nodes when the balance factor becomes too large. This ensures efficient search, insert, and delete operations.

## Features

- **User Registration and Login**: Users can sign up and log in to the system.
- **Flight Reservation and Cancellation**: Users can reserve flights and cancel reservations.
- **Flight Information Viewing**: Users can view flight information.
- **Admin Panel**: Administrators can manage flights, view reservations, and delete flights.
- **AVL Tree Data Structure**: Efficient storage and retrieval of flight information.

## How It Works

1. **User Operations**: 
   - Users can sign up and log in.
   - Users can reserve flights and view flight information.

2. **Admin Operations**:
   - Administrators can manage flights.
   - Administrators can view reservations and delete flights.

3. **Data Storage**:
   - The system uses an AVL tree to store flight information, ensuring efficient search, insert, and delete operations.

## Code Structure

The code is organized into several classes:

- **Flight**: Represents a flight with attributes such as flight number, airline, capacity, destination, and departure time.
- **User**: Represents a user with attributes such as username, password, and national code.
- **Reservation**: Represents a reservation with attributes such as flight number, user ID, and reservation code.
- **Admin**: Represents an administrator with attributes such as username and password.
- **Client**: Represents a client with attributes such as username and password.
