package com.example.demo;

import jakarta.persistence.*;

@Entity
@Table(name = "accounts")
public class Accounts {
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    @Id
    @Column(name = "account_id", nullable = false)
    private int accountId;

    @Column(name = "loans_num", nullable = false)
    private int loansNum;

    @Column(name = "total_borrowed", nullable = false, precision = 0)
    private Object totalBorrowed;

    @Column(name = "active", nullable = false)
    private byte active;

    @Column(name = "credit", nullable = false, precision = 0)
    private Object credit;

    @ManyToOne
    @JoinColumn(name = "customer_id", nullable = false)
    private Customer customer;

    @Column(name = "password", nullable = false, length = 255)
    private String password;

    public int getAccountId() {
        return accountId;
    }

    public void setAccountId(int accountId) {
        this.accountId = accountId;
    }

    public int getLoansNum() {
        return loansNum;
    }

    public void setLoansNum(int loansNum) {
        this.loansNum = loansNum;
    }

    public Object getTotalBorrowed() {
        return totalBorrowed;
    }

    public void setTotalBorrowed(Object totalBorrowed) {
        this.totalBorrowed = totalBorrowed;
    }

    public byte getActive() {
        return active;
    }

    public void setActive(byte active) {
        this.active = active;
    }

    public Object getCredit() {
        return credit;
    }

    public void setCredit(Object credit) {
        this.credit = credit;
    }

    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }
}
