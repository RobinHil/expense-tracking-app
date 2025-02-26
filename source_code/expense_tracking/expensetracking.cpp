#include <QVariant>
#include <QSqlError>
#include <QPair>
#include <QFile>

#include "expensetracking.h"
#include "query.h"

/**
 * @brief Creates an instance of ExpenseTracking with all its member data.
 * @param _username The username of the user.
 * @param database The name of the database.
 * @param connection The connection name.
 */
ExpenseTracking::ExpenseTracking(const QString& _username, const QString& database, const QString& connection)
    : username(_username)
{
    db = QSqlDatabase::addDatabase("QMYSQL", connection);
    db.setHostName("<db_host>");
    db.setDatabaseName(database);
    db.setUserName("<db_username>");
    db.setPassword("<db_password>");
    if(!db.open())
        qDebug() << "Erreur: database";
}

/**
 * @brief Destroys the current instance of ExpenseTracking.
 */
ExpenseTracking::~ExpenseTracking()
{
    QSqlDatabase::database().close();
}

/**
 * @brief Adds a category to the category map.
 * @param category The category to add to the category map.
 */
void ExpenseTracking::addCategory(const Category& category) const{
    Query query(db);
    query.prepare("INSERT INTO Category(name_cat,color,user) VALUES(:name,:color,:user);");
    query.bindValue(":name", category.getName());
    query.bindValue(":color", category.getColor().name());
    query.bindValue(":user",username);
    query.execute();
}

/**
 * @brief Removes a category from the category map.
 * @param i The id of the category to remove in the category map.
 */
void ExpenseTracking::removeCategory(const unsigned int& i) const{
    Query query(db);
    query.prepare("UPDATE Expense SET cat_exp=NULL WHERE cat_exp=?");
    query.addBindValue(i);
    query.execute();
    query.prepare("DELETE FROM Category WHERE id_cat=?;");
    query.addBindValue(i);
    query.execute();
}

/**
 * @brief Updates the data of a category in the database.
 * @param i The id of the category to update in the category map.
 * @param category The new category data.
 */
void ExpenseTracking::updateCategory(const unsigned int& i, const Category& category) const{
    Query query(db);
    query.prepare("UPDATE Category SET name_cat=:name, color=:color WHERE id_cat=:id;");
    query.bindValue(":name", category.getName());
    query.bindValue(":color", category.getColor());
    query.bindValue(":id", i);
    query.execute();
}

/**
 * @brief Retrieves a category from the database.
 * @param id The id of the category to retrieve.
 * @return The category with the given id.
 */
Category ExpenseTracking::getCategory(const int& id) const{
    Query query(db);
    query.prepare("SELECT name_cat, color FROM Category WHERE id_cat=?;");
    query.addBindValue(id);
    query.execute();
    if(query.next())
        return Category(query.value(0).toString(), QColor(query.value(1).toString()));
    return Category();
}

/**
 * @brief Retrieves all categories from the database.
 * @return A constant reference to the category map.
 */
QMap<int,Category> ExpenseTracking::getCategories() const{
    Query query(db);
    QMap<int,Category> categories;
    query.prepare("SELECT id_cat, name_cat, color FROM Category WHERE user=?;");
    query.addBindValue(username);
    query.execute();
    while(query.next())
        categories.insert(query.value(0).toInt(),Category(query.value(1).toString(), QColor(query.value(2).toString())));
    return categories;
}

/**
 * @brief Adds an expense to the expense map.
 * @param expense The expense to add to the expense map.
 */
void ExpenseTracking::addExpense(const Expense& expense) const{
    Query query(db);
    query.prepare("INSERT INTO Expense(name_exp, desc_exp, date_exp, value_exp, cat_exp, user) VALUES(:name,:desc,:date,:value,:cat,:user);");
    query.bindValue(":name", expense.getName());
    query.bindValue(":desc", expense.getDescription());
    query.bindValue(":date", expense.getDate());
    query.bindValue(":value", expense.getValue());
    query.bindValue(":user", username);
    int id = expense.getCategory();
    query.bindValue(":cat", id==0?QVariant():QVariant(id));
    query.execute();
}

/**
 * @brief Removes an expense from the expense map.
 * @param i The id of the expense to remove in the expense map.
 */
void ExpenseTracking::removeExpense(const unsigned int& i) const{
    Query query(db);
    query.prepare("DELETE FROM Expense WHERE id_exp=?;");
    query.addBindValue(i);
    query.execute();
}

/**
 * @brief Updates the data of an expense in the database.
 * @param i The id of the expense to update in the expense map.
 * @param expense The new expense data.
 */
void ExpenseTracking::updateExpense(const unsigned int& i, const Expense& expense) const{
    Query query(db);
    query.prepare("UPDATE Expense SET name_exp=:name, desc_exp=:desc, date_exp=:date, value_exp=:value, cat_exp=:cat WHERE id_exp=:id;");
    query.bindValue(":name", expense.getName());
    query.bindValue(":desc", expense.getDescription());
    query.bindValue(":date",expense.getDate());
    query.bindValue(":value",expense.getValue());
    int cat=expense.getCategory();
    query.bindValue(":cat", cat==0?QVariant():QVariant(cat));
    query.bindValue(":id", i);
    query.execute();
}

/**
 * @brief Retrieves an expense from the database.
 * @param id The id of the expense to retrieve.
 * @return The expense with the given id.
 */
Expense ExpenseTracking::getExpense(const int& id) const
{
    QString sql = "SELECT id_exp, name_exp, desc_exp, date_exp, value_exp, cat_exp FROM Expense WHERE id_exp=?;";

    Query query(db);
    query.prepare(sql);
    query.addBindValue(id);
    query.execute();

    if(query.next()){
        return Expense(query.value(1).toString(), query.value(2).toString(), (query.value(5).isNull() ? 0 : query.value(5).toInt()), query.value(3).toDate(), query.value(4).toDouble());
    }

    return Expense();
}

/**
 * @brief Retrieves all expenses from the database.
 * @param id_cat The id of the category.
 * @param search The search query.
 * @param dateType The type of date filter.
 * @param selectedDate The selected date.
 * @return An expenses vector.
 */
QVector<QPair<int,Expense>> ExpenseTracking::getExpenses(const int& id_cat, const QString& search, const int& dateType, const QDate& selectedDate) const
{
    QString sql = "SELECT id_exp, name_exp, desc_exp, date_exp, value_exp, cat_exp FROM Expense WHERE USER=? AND LOWER(name_exp) LIKE ?";

    if (id_cat != 0)
        sql += " AND cat_exp=?";

    switch (dateType) {
    case 1: // Sort by day
        sql += " AND date_exp = ?";
        break;
    case 2: // Sort by month
    case 3: // Sort by year
        sql += " AND date_exp BETWEEN ? AND ?";
        break;
    }

    sql+=" ORDER BY date_exp;";

    Query query(db);
    query.prepare(sql);
    query.addBindValue(username);
    if(search.isEmpty())
        query.addBindValue(QString('%'));
    else
        query.addBindValue('%' + search.toLower() + '%');

    if (id_cat != 0)
        query.addBindValue(id_cat);

    switch(dateType){
    case 1: // Sort by day
        query.addBindValue(selectedDate);
        break;
    case 2: // Sort by month
        query.addBindValue(QDate(selectedDate.year(), selectedDate.month(), 1));
        query.addBindValue(QDate(selectedDate.year(), selectedDate.month(), selectedDate.daysInMonth()));
        break;
    case 3: // Sort by year
        query.addBindValue(QDate(selectedDate.year(), 1, 1));
        query.addBindValue(QDate(selectedDate.year(), 12, 31));
        break;
    }

    query.execute();

    QVector<QPair<int,Expense>> expenses;
    while (query.next()) {
        Expense e(query.value(1).toString(), query.value(2).toString(), (query.value(5).isNull() ? 0 : query.value(5).toInt()), query.value(3).toDate(), query.value(4).toDouble());
        expenses.push_back(QPair<int,Expense>(query.value(0).toInt(),e));
    }

    return expenses;
}

/**
 * @brief Calculates the sum of expenses for the selected date.
 * @param dateType The type of date filter.
 * @param selectedDate The selected date.
 * @return The sum of expenses.
 */
double ExpenseTracking::getExpensesSum(const int& dateType, const QDate& selectedDate) const
{
    double result=0;
    for(const QPair<int,Expense>& exp: getExpenses(0, "", dateType, selectedDate)){
        result+=exp.second.getValue();
    }
    return result;
}

/**
 * @brief Adds a reminder to the reminder map.
 * @param reminder The reminder to add to the reminder map.
 */
void ExpenseTracking::addReminder(const Reminder& reminder) const{
    Query query(db);
    query.prepare("INSERT INTO Reminder(name_rem, date_rem, user) VALUES(:name,:date,:user);");
    query.bindValue(":name", reminder.getName());
    query.bindValue(":date", reminder.getDate());
    query.bindValue(":user", username);
    query.execute();
}

/**
 * @brief Removes a reminder from the reminder map.
 * @param i The id of the reminder to remove in the reminder map.
 */
void ExpenseTracking::removeReminder(const unsigned int& i) const{
    Query query(db);
    query.prepare("DELETE FROM Reminder WHERE id_rem=?;");
    query.addBindValue(i);
    query.execute();
}

/**
 * @brief Updates the data of a reminder in the database.
 * @param i The id of the reminder to update in the reminder map.
 * @param reminder The new reminder data.
 */
void ExpenseTracking::updateReminder(const unsigned int& i, const Reminder& reminder) const{
    Query query(db);
    query.prepare("UPDATE Reminder SET name_rem=:name, date_rem=:date WHERE id_rem=:id;");
    query.bindValue(":name", reminder.getName());
    query.bindValue(":date",reminder.getDate());
    query.bindValue(":id", i);
    query.execute();
}

/**
 * @brief Retrieves all reminders from the database.
 * @param expired Whether to retrieve expired reminders.
 * @return A constant reference to the reminder map.
 */
QMap<int,Reminder> ExpenseTracking::getReminders(const bool& expired) const{
    QMap<int,Reminder> reminders;
    QString command("SELECT id_rem, name_rem, date_rem FROM Reminder WHERE user=?");
    if(expired)
        command+=" AND date_rem <= ?";
    command+=';';
    Query query(db);
    query.prepare(command);
    query.addBindValue(username);
    if(expired)
        query.addBindValue(QDate::currentDate());
    query.execute();
    while(query.next())
        reminders.insert(query.value(0).toInt(),Reminder(query.value(1).toString(), query.value(2).toDate()));
    return reminders;
}

/**
 * @brief Updates the budget value in the database.
 * @param newbudget The new budget value to set.
 */
void ExpenseTracking::updateBudget(const double& newbudget) const{
    Query query(db);
    query.prepare("UPDATE ETUser SET budget=? WHERE username=?;");
    query.addBindValue(newbudget);
    query.addBindValue(username);
    query.execute();
}

/**
 * @brief Retrieves the current budget value from the database.
 * @return The current budget value as a double.
 */
double ExpenseTracking::getBudget() const{
    double budget=0;
    Query query(db);
    query.prepare("SELECT budget FROM ETUser WHERE username=?;");
    query.addBindValue(username);
    query.execute();
    if(query.next())
        budget=query.value(0).toDouble();
    return budget;
}

/**
 * @brief Adds a line to a CSV file stream with proper formatting.
 * @param stream The QTextStream to write to.
 * @param strList The QStringList containing data to add to the line.
 */
void ExpenseTracking::addLineToCSV(QTextStream& stream, const QStringList& strList) const{
    for(int i=0; i<strList.size(); i++){
        if(i!=0)
            stream << ';';
        stream << '"';
        for(QChar c:strList[i]){
            if(c=='"')
                stream << c;
            stream << c;
        }
        stream << '"';
    }
    stream << Qt::endl;
}

/**
 * @brief Exports expense data to a CSV file at the specified path.
 * @param path The path of the CSV file to export to.
 */
void ExpenseTracking::exportToCSV(const QString& path) const{
    QFile file(path);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream stream(&file);
        QStringList strList;
        strList << "Date" << "Name" << "Description" << "Amount" << "Category";
        addLineToCSV(stream,strList);

        QVector<QPair<int,Expense>> exp = getExpenses();
        for (QVector<QPair<int,Expense>>::iterator it = exp.begin(); it != exp.end(); ++it) {
            const Expense& e = it->second;
            QStringList expList;
            expList << e.getDate().toString("dd/MM/yyyy") << e.getName() << e.getDescription() << QString::number(e.getValue()) << getCategory(e.getCategory()).getName();
            addLineToCSV(stream,expList);
        }
    }
}

/**
 * @brief updateUser modifies user's data.
 * @param email The new user's email address.
 * @param birth The new user's birth date.
 * @param gender The new user's gender.
 */
void ExpenseTracking::updateUser(const QString& email, const QDate& birth, const QString& gender) const
{
    Query query(db);
    query.prepare("UPDATE ETUser SET email=:email, birth=:birth, gender=:gender WHERE username=:username;");
    query.bindValue(":email", email);
    query.bindValue(":birth", birth);
    query.bindValue(":gender", gender);
    query.bindValue(":username", username);
    query.execute();
}

/**
 * @brief removeUser removes the user.
 */
void ExpenseTracking::removeUser() const
{
    Query query(db);
    query.prepare("DELETE FROM ETUser WHERE username=:username;");
    query.bindValue(":username", username);
    query.execute();
}

/**
 * @brief getUser gets the user's information.
 */
User ExpenseTracking::getUser() const
{
    Query query(db);
    query.prepare("SELECT email, birth, gender, budget FROM ETUser WHERE username=:username;");
    query.bindValue(":username", username);
    query.execute();
    User user;
    if(query.next())
        user=User(username, query.value(0).toString(), query.value(1).toDate(), query.value(2).toString(), query.value(3).toDouble());
    return user;
}

/**
 * @brief Gets the user's password.
 * @param password the variable to where to store the password.
 * @return If the function failed or not.
 */
bool ExpenseTracking::getUserPassword(QString& password) const
{
    Query query(db);
    query.prepare("SELECT password FROM ETUser WHERE username = :username");
    query.bindValue(":username", username);
    if (query.exec() && query.next()) {
        password = query.value(0).toString();
        return true;
    }
    return false;
}

/**
 * @brief Updates the user's password.
 * @param newPassword the new password to set.
 * @return If the function failed or not.
 */
bool ExpenseTracking::updatePassword(const QString& newPassword) const
{
    Query query(db);
    query.prepare("UPDATE ETUser SET password = :password WHERE username = :username");
    query.bindValue(":password", newPassword);
    query.bindValue(":username", username);
    return query.exec();
}
