# Bank Management Project

This project implements a **management system for a bank**.

---

## Entities

1. **Customer**
2. **Employee (Clerk)**
3. **Account**
4. **Loan**
5. **Bank**

---

## Customer

- Attributes:  
  - Name, Last Name  
  - Unique National ID  
  - Date of Birth  
  - Username, Password  

- Operations:  
  - Login to the system  
  - Deposit / Withdraw money  
  - Request loan if account balance ≥ **1,000,000 T**  

- Loan Rules:  
  - Loan amount = `Balance × Number of Days ≥ 1,000,000 T`  
  - Example: balance = 1,200,000 T for 3 days → Loan = `1,200,000 × 3 = 3,600,000`  
  - Days are counted per program run (1 run = 1 day).  
  - Loan installments:  
    - 12 installments → 4% interest  
    - 24 installments → 8% interest  
    - 36 installments → 12% interest  

- Notes:  
  - Each customer can own multiple accounts.  
  - Each account may independently qualify for a loan.  
  - Must provide method to display full customer info.  

---

## Employee (Clerk)

- Attributes:  
  - Name, Last Name  
  - Unique 3-digit Personnel ID  
  - Date of Birth  
  - Base Salary  
  - Username, Password  
  - Time Off Hours, Overtime Hours  

- Operations:  
  - **Time Off:**  
    - Max 15 hrs/month.  
    - Exceeding 15 hrs → Salary reduced by 100,000 T/hour.  
  - **Overtime:**  
    - Max 12 hrs/month.  
    - Salary increases by 120,000 T/hour.  
  - Open customer accounts (min deposit = 50,000 T).  
  - Activate/Deactivate accounts.  
  - View full customer info by National ID.  

---

## Manager

- Special Employee type.  
- Operations:  
  - View employee info by Personnel ID.  
  - Hire/Fire employees.  
- Bank must have a Manager initially.  

---

## Credit Officer (Amour-e Tasilat)

- Manages **loan requests queue**.  
- Operations:  
  - View loan requests.  
  - Approve/Reject loans (1 per day).  
  - Block all customer accounts.  
  - View loan status by Serial Number.  

---

## Bank

- Attributes:  
  - Employees  
  - Customers  
  - Branch Name, Branch Code  
- Must have:  
  - One Manager  
  - One Credit Officer  

---

## Account

- Attributes:  
  - Account Number (unique)  
  - Owner’s National ID  
  - Opening Date  
  - Balance  
  - Days balance ≥ 1,000,000 T  
  - Active/Inactive flag  

- Notes:  
  - Deposits allowed on all accounts.  
  - Withdrawals allowed only on **Active** accounts.  

---

## Loan

- Attributes:  
  - Linked Account Number  
  - Date of Issue  
  - Loan Amount, Interest Rate  
  - Total Installments (default = 24)  
  - Amount per Installment  
  - Paid Installments, Overdue Installments  
  - 8-digit Serial Number (unique)  

- Installment Formula:  

g++ -I include `
>>     src/account.cpp src/bank.cpp src/customer.cpp src/date.cpp src/employee.cpp `
>>     src/facilityemployee.cpp src/loan.cpp src/main.cpp src/manager.cpp src/report.cpp `
>>     -o build/BankingSystemApp.exe -std=c++17