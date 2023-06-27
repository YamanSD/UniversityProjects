package com.example.demo;

import jakarta.persistence.*;

import java.sql.Timestamp;

@Entity
@Table(name = "loans")
public class Loans {
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    @Id
    @Column(name = "loan_id", nullable = false)
    private int loanId;

    @Column(name = "value", nullable = false, precision = 0)
    private Object value;

    @Column(name = "creation_date", nullable = false)
    private Timestamp creationDate;

    @Column(name = "cancellation_date", nullable = true)
    private Timestamp cancellationDate;

    @Column(name = "total_interest_rate", nullable = false, precision = 0)
    private Object totalInterestRate;

    @Column(name = "expiry_date", nullable = false)
    private Timestamp expiryDate;

    @ManyToOne
    @JoinColumns({
            @JoinColumn(name = "account_id", referencedColumnName = "account_id", nullable = false),
            @JoinColumn(name = "customer_id", referencedColumnName = "customer_id", nullable = false)
    })
    private Account account;

    @ManyToOne
    @JoinColumn(name = "customer_id", referencedColumnName = "customer_id", nullable = false, insertable = false, updatable = false)
    private Customer customer;

    public int getLoanId() {
        return loanId;
    }

    public void setLoanId(int loanId) {
        this.loanId = loanId;
    }

    public Object getValue() {
        return value;
    }

    public void setValue(Object value) {
        this.value = value;
    }

    public Timestamp getCreationDate() {
        return creationDate;
    }

    public void setCreationDate(Timestamp creationDate) {
        this.creationDate = creationDate;
    }

    public Timestamp getCancellationDate() {
        return cancellationDate;
    }

    public void setCancellationDate(Timestamp cancellationDate) {
        this.cancellationDate = cancellationDate;
    }

    public Object getTotalInterestRate() {
        return totalInterestRate;
    }

    public void setTotalInterestRate(Object totalInterestRate) {
        this.totalInterestRate = totalInterestRate;
    }

    public Timestamp getExpiryDate() {
        return expiryDate;
    }

    public void setExpiryDate(Timestamp expiryDate) {
        this.expiryDate = expiryDate;
    }
}
