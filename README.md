# Gym Management System

A comprehensive **Gym Management System** written in C++ that provides a seamless interface for both gym members and managers. This system efficiently handles membership management, attendance tracking, and member information updates, making it a valuable asset for any gym facility.

---

## 🌟 Features

### 🏋️ Member Interface
- **New Member Registration**:
  - Allows new members to register and create a unique Member ID.
- **Check-In and Check-Out**:
  - Validates member status before checking in or out.
  - Ensures members cannot check in twice consecutively or check out without a prior check-in.

### 🔑 Manager Interface
- **Password-Protected Access**:
  - Secure terminal requiring a password for access with up to 4 attempts.
- **Member Management**:
  - Update membership type, duration, activity status, and contact details.
  - Search for detailed member records.
- **Generate Reports**:
  - Automatically compiles relevant data to help gym management.
- **Membership Expiry Notifications**:
  - Alerts when memberships expire and offers easy re-registration options.

### 📈 Persistence
- Data is stored and retrieved from external files for:
  - Member records.
  - Attendance tracking.
- Ensures data is preserved between sessions.

---

## 🛠️ Technologies Used
- **C++**: Core programming language for the system.
- **File Handling**: Persistent storage for member and attendance data.
- **OOP Principles**: Utilizes classes and encapsulation to model members and their attributes.

---

## 🚀 Getting Started

### Prerequisites
- C++ Compiler (e.g., g++, MSVC).
- A terminal or IDE to run C++ code.

### Running the Project
1. Clone this repository:
   ```bash
   git clone https://github.com/yourusername/gym-management-system.git
   cd gym-management-system
