# SRMS - Student Record Management System

## Discription
The **Student Record Management System (SRMS)** is a terminal-based C application designed to manage student records efficiently with **role-based access**. It allows users with different roles to perform actions according to their permissions.

- **Roles Supported:** ADMIN, STAFF, USER, GUEST  
- **Data Storage:** `students.txt` and `credentials.txt` files  

## Simulation

### ADMIN
- Add new student records  
- Display all student records  
- Search student by roll number  
- Update student details  
- Delete student records  
- Logout

### STAFF
- Display all student records  
- Search student by roll number  
- Update student details  
- Delete student records  
- Logout

### USER
- Display all student records  
- Search student by roll number  
- Logout

### GUEST
- Display student records (Roll & Name only)  
- Logout

## How to Run
1. Open **Command Prompt** and navigate to the project folder:
   
cd C:\SRMS_Project

2. Compile the program:
   
gcc main.c -o main

3. Run it:
   
./main.exe or just click run option.

4. Enter username/password, and navigate menus according to your role:
   
ADMIN: admin / admin123

STAFF: staff / staff321

USER: user / user999

GUEST: guest / guest111

## File Structure

C:\SRMS_Project

│

├── main.c             // Main C program

├── students.txt       // Student records

├── credentials.txt    // Login credentials

└── README.md          // Project simulation

## Screenshots

<img width="452" height="861" alt="Screenshot 2025-12-03 162757" src="https://github.com/user-attachments/assets/1160e894-ec0f-4573-8c9a-4ebfc74b3eab" />

<img width="455" height="783" alt="Screenshot 2025-12-03 163009" src="https://github.com/user-attachments/assets/dbce8ca8-1aa8-43da-9603-533ff2051422" />

<img width="452" height="679" alt="Screenshot 2025-12-03 163044" src="https://github.com/user-attachments/assets/ce74de30-7561-426d-bd33-c484e1d936e8" />

<img width="453" height="754" alt="Screenshot 2025-12-03 163446" src="https://github.com/user-attachments/assets/95fcdfca-57ff-4ad2-a726-9fdbf670a5c6" />

<img width="459" height="894" alt="Screenshot 2025-12-03 163520" src="https://github.com/user-attachments/assets/8331ac97-5509-456b-86c4-1a3df143bfe3" />

<img width="456" height="190" alt="Screenshot 2025-12-03 163549" src="https://github.com/user-attachments/assets/db8f8491-9b12-488f-8ec3-e46f424cefd6" />

<img width="455" height="690" alt="Screenshot 2025-12-03 163811" src="https://github.com/user-attachments/assets/03b47369-4bac-45ed-a82a-ee378c79b996" />

<img width="452" height="550" alt="Screenshot 2025-12-03 163828" src="https://github.com/user-attachments/assets/c0f5f8cf-39b9-4396-8846-2e1e9b888719" />

## Author
**Ambadipudi Lakshmi Gayatri**  

## Date
3rd December 2025  
