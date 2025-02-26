# 💰 Expense Tracker Application

A comprehensive personal expense management solution built with Qt/C++.

## 👥 Development Team

- **AKARDJOUDJE Rayan** - Product Owner / Developer
- **BATISTA Thomas** - SCRUM Master / Developer
- **HILAIRE Robin** - Developer
- **EL YAMOUNI Sohaib** - Developer
- **MANAVANANA Noa** - Developer

## ✨ Features

- 📊 Track and categorize personal expenses
- 📝 Add, edit, and delete expenses with detailed descriptions
- 🏷️ Create custom categories with color coding
- 📅 Filter expenses by day, month, or year
- 💸 Set and manage budgets with alerts for overspending
- 📈 Visualize spending patterns with charts and graphs
- 🔔 Create reminders for recurring expenses
- 🔐 Secure user authentication with Argon2id password hashing
- 📱 Responsive user interface
- 📤 Export data to CSV format

## 🛠️ Technologies

- **Frontend & Backend**: Qt/C++ Framework
- **Database**: MySQL
- **Security**: libsodium (Argon2id hashing)
- **Charts**: QtCharts
- **Testing**: QTest

## 🔧 Setup and Installation

### Prerequisites

- Qt Creator (Qt 5 or higher)
- MySQL
- libsodium library

### Database Driver Installation

#### Linux
```sh
sudo apt-get install libqt5sql5-mysql  # Ubuntu/Debian
sudo dnf install qt-mysql              # Fedora
sudo pacman -S qt5-mysql               # Arch Linux
```

#### macOS
```sh
brew install qt-mysql
```

#### Windows
Download the Qt MySQL driver from [qt_mysql_driver](https://github.com/thecodemonkey86/qt_mysql_driver) GitHub repository and place it in your Qt installation's `sqldrivers` directory.

### libsodium Installation

#### Linux
```sh
sudo apt-get install libsodium-dev  # Ubuntu/Debian
sudo dnf install libsodium-devel    # Fedora
sudo pacman -S libsodium            # Arch Linux
```

#### macOS
```sh
brew install libsodium
```

#### Windows
Download the library from [libsodium releases](https://download.libsodium.org/libsodium/releases/), extract it, and place it in the `resources/libsodium` directory of the application.

## ▶️ Running the Application

1. Open Qt Creator
2. Open the project file `source_code/expense_tracking/expense_tracking.pro`
3. Configure the kit for your compiler and Qt version
4. Run the application

## 🗃️ Database Setup

The database creation script is available in `sql/db_creation/db_creation_script.sql`. Execute this script on your MySQL server to create the necessary database structure.

## 🧪 Running Tests

The application includes a comprehensive suite of unit tests. To run them:

1. Open Qt Creator
2. Open the project file `source_code/test_expense_tracking/test_expense_tracking.pro`
3. Run the tests

You can also run specific tests from the command line:

```sh
# Run all tests
./test_expense_tracking -all

# Run a specific test group
./test_expense_tracking -category

# Run a specific test
./test_expense_tracking -category test_category_empty_create
```

## 📚 Documentation

To generate the documentation locally:

```sh
cd doxygen
doxygen Doxyfile
```

This will create a `html` directory containing the documentation files.

## 📋 Project Structure

The main source code is organized as follows:

```
source_code/
├── expense_tracking/        # Main application code
│   ├── accountdialog.*      # Account management
│   ├── budgetdialog.*       # Budget management
│   ├── category.*           # Category model
│   ├── chartsdialog.*       # Charts visualization
│   ├── expense.*            # Expense model
│   ├── expensedialog.*      # Expense management
│   ├── expensetracking.*    # Core tracking functionality
│   ├── hash.*               # Password hashing
│   ├── logindialog.*        # Login interface
│   ├── mainwindow.*         # Main application window
│   ├── reminder.*           # Reminder model
│   └── user.*               # User model
├── test_expense_tracking/   # Unit tests
└── sql/                     # SQL scripts for database setup
```

## 🔄 Application Workflow

1. **User Authentication**: Login or register to access the application
2. **Dashboard**: View and filter expenses, check budget status
3. **Expense Management**: Add, edit, or delete expenses
4. **Categorization**: Create and manage custom categories
5. **Reporting**: Generate charts and export data for analysis

## 🔒 Security Features

- Password hashing using Argon2id (via libsodium)
- Account lockout after multiple failed login attempts
- Secure database connections