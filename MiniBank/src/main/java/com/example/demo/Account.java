package com.example.demo;

import jakarta.persistence.*;

@Entity
@Table(name = "accounts")
public class Account {
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    @Id
    @Column(name = "account_id", nullable = false)
    private int accountId;

    @Column(name = "active", nullable = false)
    private byte active;

    @Column(name = "credit", nullable = false, precision = 2)
    private Double credit;

    @ManyToOne
    @JoinColumn(name = "customer_id", nullable = false)
    private Customer customer;

    @Column(name = "password", nullable = false, length = 255)
    private String password;

    public Account(Customer customer, String password) {
        setActive((byte) 1);
        setCredit(0.0);
        setPassword(password);

        this.customer = customer;
    }

    public Account() {
    }

    public int getAccountId() {
        return accountId;
    }

    public void setAccountId(int accountId) {
        this.accountId = accountId;
    }

    public boolean getActive() {
        return active == 1;
    }

    public void setActive(byte active) {
        this.active = active;
    }

    public Double getCredit() {
        return credit;
    }

    public void setCredit(Double credit) {
        this.credit = credit;
    }

    public void deposit(double amount) {
        setCredit(amount + getCredit());
    }

    public boolean withdraw(double amount) {
        if (amount > getCredit()) {
            return false;
        }

        setCredit(getCredit() - amount);
        return true;
    }

    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    @Override
    public String toString() {
        return String.format("""
                
                Account ID:     %d
                Owner:          %s %s %s
                Owner ID:       %d
                Credit:         $%.2f
                Active:         %b
                """,
                getAccountId(),
                customer.getFirstName(),
                customer.getMiddleName(),
                customer.getLastName(),
                customer.getCustomerId(),
                getCredit(),
                getActive()
                );
    }
}
