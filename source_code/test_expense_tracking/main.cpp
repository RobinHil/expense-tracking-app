#include <QCoreApplication>
#include <QTest>
#include <QDebug>
#include <QMap>

#include "categorytest.h"
#include "expensetest.h"
#include "hashtest.h"
#include "remindertest.h"
#include "userdbtest.h"
#include "usertest.h"

/**
 * @brief The main function for running all or specific tests.
 *
 * This function creates a QCoreApplication and a QMap containing all the tests.
 * It then checks the command line arguments to determine whether to run all tests or a specific one.
 *
 * @param argc The number of command line arguments.
 * @param argv The command line arguments.
 *
 * @return The status of the tests run.
 */
int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    /**
     * @brief A QMap containing all the tests.
     *
     * Each key is a command line argument for running a specific test, and each value is a pointer to the corresponding test object.
     */
    QMap<QString, QObject*> testsMap = {
        {"-category", new CategoryTest},
        {"-expense", new ExpenseTest},
        {"-hash", new HashTest},
        {"-reminder", new ReminderTest},
        {"-userdb", new UserDBTest},
        {"-user", new UserTest}
    };

    QString testAlias;
    if (argc>1)
        testAlias = argv[1];

    int status = 0;

    if (testAlias.isEmpty() || testAlias=="-all") {
        int newArgc = argc-1;
        char **newArgv = new char*[newArgc+1];
        newArgv[0] = argv[0];

        for (int i = 1; i < newArgc; ++i)
            newArgv[i] = argv[i+1];

        newArgv[newArgc] = nullptr;

        qInfo() << "\nExécution de tous les tests";

        /**
         * @brief Run all tests if no specific test is specified.
         */
        for (const QString& alias : testsMap.keys()) {
            QObject *test = testsMap[alias];
            qInfo() << "\nTest :" << test->metaObject()->className();
            status = QTest::qExec(test, newArgc, newArgv);
        }

        delete[] newArgv;
    } else if (testsMap.contains(testAlias)) {
        QObject *testInstance = testsMap[testAlias];

        int newArgc = argc-1;
        char **newArgv = new char*[newArgc+1];
        newArgv[0] = argv[0];

        for (int i = 1; i < newArgc; ++i)
            newArgv[i] = argv[i+1];

        newArgv[newArgc] = nullptr;

        qInfo() << "\nExécution du test :" << testInstance->metaObject()->className();

        /**
         * @brief Run a specific test if it is specified.
         */
        status = QTest::qExec(testInstance, newArgc, newArgv);

        delete[] newArgv;
    } else
        qWarning() << "Test non reconnu :" << testAlias;

    /**
     * @brief Clean up all test objects.
     */
    for (QObject *test : testsMap)
        delete test;

    return status;
}
