
#include <iostream>
#include <iomanip>

class BankAccount {
private:
    int accountNumber;
    double balance;
    double interestRate;

public:
    BankAccount(int accNum, double initialBalance) : accountNumber(accNum), balance(initialBalance), interestRate(0.0) {}

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            std::cout << "Сумма " << std::fixed << std::setprecision(2) << amount << " успешно внесена на счет." << std::endl;
        }
        else {
            std::cout << "Ошибка: вы пытаетесь внести отрицательную сумму." << std::endl;
        }
    }

    void withdraw(double amount) {
        if (amount > 0) {
            if (amount <= balance) {
                balance -= amount;
                std::cout << "Сумма " << std::fixed << std::setprecision(2) << amount << " успешно снята со счета." << std::endl;
            }
            else {
                std::cout << "Ошибка: недостаточно средств на счете для снятия." << std::endl;
            }
        }
        else {
            std::cout << "Ошибка: вы пытаетесь снять отрицательную сумму." << std::endl;
        }
    }

    double getBalance() {
        return balance;
    }

    double getInterest() {
        return balance * interestRate * (1.0 / 12);
    }

    void setInterestRate(double newRate) {
        interestRate = newRate;
    }

    int getAccountNumber() {
        return accountNumber;
    }

    friend bool transfer(BankAccount& from, BankAccount& to, double amount);
};

bool transfer(BankAccount& from, BankAccount& to, double amount) {
    if (amount > 0) {
        if (amount <= from.balance) {
            from.balance -= amount;
            to.balance += amount;
            std::cout << "Перевод на сумму " << std::fixed << std::setprecision(2) << amount << " успешно выполнен." << std::endl;
            return true;
        }
        else {
            std::cout << "Ошибка: на первом счете недостаточно средств для перевода." << std::endl;
            return false;
        }
    }
    else {
        std::cout << "Ошибка: попытка перевести отрицательную сумму." << std::endl;
        return false;
    }
}

int main() {
    setlocale(LC_ALL, "");

    BankAccount account1(355, 1000.0);
    BankAccount account2(134, 1000.0);

    BankAccount* currentAccount = &account1;

    while (true) {
        int choice;
        std::cout << "Текущий счет: " << currentAccount->getAccountNumber() << std::endl;
        std::cout << "Баланс: " << std::fixed << std::setprecision(2) << currentAccount->getBalance() << std::endl;
        std::cout << "1. Переключиться на счет 1" << std::endl;
        std::cout << "2. Переключиться на счет 2" << std::endl;
        std::cout << "3. Внести на счет" << std::endl;
        std::cout << "4. Снять со счета" << std::endl;
        std::cout << "5. Перевести между счетами" << std::endl;
        std::cout << "6. Выйти" << std::endl;
        std::cout << "Выберите действие: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            currentAccount = &account1;
            break;
        case 2:
            currentAccount = &account2;
            break;
        case 3:
            double depositAmount;
            std::cout << "Введите сумму для внесения: ";
            std::cin >> depositAmount;
            currentAccount->deposit(depositAmount);
            break;
        case 4:
            double withdrawAmount;
            std::cout << "Введите сумму для снятия: ";
            std::cin >> withdrawAmount;
            currentAccount->withdraw(withdrawAmount);
            break;
        case 5:
            double transferAmount;
            int transferTo;
            std::cout << "Введите сумму для перевода";

               
                std::cin >> transferAmount;
            std::cout << "Перевести на счет#: ";
            std::cin >> transferTo;
            if (transferTo == account1.getAccountNumber()) {
                transfer(*currentAccount, account1, transferAmount);
            }
            else if (transferTo == account2.getAccountNumber()) {
                transfer(*currentAccount, account2, transferAmount);
            }
            else {
                std::cout << "Ошибка: указан неверный счет для перевода." << std::endl;
            }
            break;
        case 6:
            std::cout << "До свидания!" << std::endl;
            return 0;
        default:
            std::cout << "Неверный ввод. Попробуйте снова." << std::endl;
        }
        std::cout << std::endl;
    }

    return 0;
}


