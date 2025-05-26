# ✈️ Airline Reservation System

## 📖 Overview  
The Airline Reservation System is a C-based console application designed for managing flight bookings. It allows users to register, log in, search for flights, book, view, modify, and cancel bookings. The system also includes administrative features for managing flights and bookings.

---

## 🌟 Features

### 👤 User Features:
- 🔐 **Registration & Login** – New users can register, and existing users can log in.  
- 🔍 **Flight Search** – Search available flights based on origin, destination, and date.  
- 🎫 **Booking Flights** – Book flights by selecting available options.  
- 📄 **View Bookings** – Users can view their booking details.  
- ✏️ **Modify Booking** – Modify existing bookings.  
- ❌ **Cancel Booking** – Users can cancel their bookings.  

### 🛠️ Admin Features:
- 🧾 **Flight Management** – Admin can add, modify, or delete flights.  
- 📋 **Booking Management** – Admin can view, modify, or cancel any booking.  

---

## 🖥️ System Requirements
- 🛠️ **Compiler**: GCC or any C compiler  
- 🧑‍💻 **Operating System**: Windows  
- 📝 **Text Editor/IDE**: Dev Embarcadero or any C IDE  

---

## ▶️ How to Run
1. 📥 Download the repository.  
2. 📂 Extract it.  
3. 🧭 Open it in Dev Embarcadero.  
4. 🏁 Press `F11` to compile and run the program.  

---

## 📁 File Structure

### 🧾 Source Code Files:
- `main_project.c` – Entry point; handles main menu and navigation  
- `registration.c` – User registration; stores credentials in `user_info.txt`  
- `admin.c` – Admin functions: manage flights and bookings  
- `user.c` – User operations: search flights, book, view history  
- `validation.c` – Input checks, login validation, and flight availability  

### 📂 Data Files:
- `flight.txt` – Stores flight info (flight number, origin, destination, etc.)  
- `user_info.txt` – Stores user credentials  
- `user_bookings.txt` – Tracks user bookings (flight, class, ticket count)  

---

## 👨‍💻 Contributors

### 👨‍💻 Faizan Basheer
- Designed the login menu, including registration, user/admin login, and password recovery  
- Implemented the admin menu with features to add, delete, modify, search, and view flights  

### 👨‍💻 Syed Muhammad Sufyan
- Developed the user menu: booking, modifying, canceling flights, viewing details, and user-specific bookings  
- Implemented automatic deletion of departed flights  

### 👨‍💻 Abdur Rehman Khan
- Managed error detection and data validation for reliable performance  
- Developed features to display specific user details  

---

## 🪪 License
This project is **open-source**. Feel free to use and modify it for educational purposes.
