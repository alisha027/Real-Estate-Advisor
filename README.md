# Real-Estate-Advisor
A simple console-based Real Estate Advisor application developed in C++ that allows users to register/login, view available properties, buy or rent properties, and handles file-based user authentication and property storage.
:

🏡 Real Estate Advisor - C++ Console Application
A simple console-based Real Estate Advisor application developed in C++ that allows users to register/login, view available properties, buy or rent properties, and handles file-based user authentication and property storage.

🔑 Features
🔐 User Authentication
Register or login using username and password, stored securely in a text file (users.txt).

📜 Property Listings
View all properties or only those currently available. Properties are stored in properties.txt with proper status tracking.

🛒 Buy or Rent Properties
Buy or rent a property by providing its ID. The availability status gets updated accordingly.

📂 File Handling
All user and property data is persisted across sessions using simple file I/O.

📁 File Structure
realstate.cpp - Main application logic

users.txt - Stores registered usernames and passwords

properties.txt - Stores property listings with availability status

