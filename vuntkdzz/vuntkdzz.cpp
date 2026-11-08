
#include <iostream>
#include <stdexcept>
using namespace std;

// неправильная сумма
class InvalidAmountException : public runtime_error {
public:
    InvalidAmountException(const string& message)
        : runtime_error(message) {
    }

    const char* what() const noexcept override {
        return runtime_error::what();
    }
};

//недостаточно  средств на балансе
class InsufficientFundsException : public runtime_error {
public:
    InsufficientFundsException(const string& message)
        : runtime_error(message) {
    }

    const char* what() const noexcept override {
        return runtime_error::what();
    }
};

//  лимит превышен
class LimitExceededException : public runtime_error {
public:
    LimitExceededException(const string& message)
        : runtime_error(message) {
    }
    const char* what() const noexcept override {
        return runtime_error::what();
    }
};

// Класс банкомата
class ATM {
private:
    int balance;
    int dailyLimit;
    int withdrawnToday;

public:
    ATM(int b, int limit) {
        balance = b;
        dailyLimit = limit;
        withdrawnToday = 0;
    }

    void withdraw(int amount) {
        if (amount % 100 != 0) {
            throw InvalidAmountException("Сума повинна бути кратною 100!");
        }

        if (amount > balance) {
            throw InsufficientFundsException("Недостатньо коштів на балансі!");
        }

        if (withdrawnToday + amount > dailyLimit) {
            throw LimitExceededException("Перевищено добовий ліміт!");
        }

        balance -= amount;
        withdrawnToday += amount;

        cout << "Гроші успішно знято: " << amount << '\n';
        cout << "Залишок на рахунку: " << balance << '\n';
    }
};

int main() {
    ATM atm(10000, 5000);

    int amount;

    cout << "Введіть суму для зняття: ";
    cin >> amount;

    try {
        atm.withdraw(amount);
    }
    catch (const InvalidAmountException& e) {
        cout << "Помилка: " << e.what() << '\n';
    }
    catch (const InsufficientFundsException& e) {
        cout << "Помилка: " << e.what() << '\n';
    }
    catch (const LimitExceededException& e) {
        cout << "Помилка: " << e.what() << '\n';
}
