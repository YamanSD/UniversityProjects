package com.example.demo;

import jakarta.persistence.*;

import java.sql.Timestamp;
import java.util.Date;

@Entity
@Table(name = "loans")
public class Loan {
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    @Id
    @Column(name = "loan_id", nullable = false)
    private int loanId;

    @Column(name = "value", nullable = false)
    private Double value;

    @Column(name = "creation_date", nullable = false)
    private Timestamp creationDate;

    @Column(name = "cancellation_date", nullable = true)
    private Timestamp cancellationDate;

    @Column(name = "total_interest_rate", nullable = false, precision = 2)
    private Double totalInterestRate;

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

    public static Timestamp dateToTimestamp(Date date) {
        return new Timestamp(date.getTime());
    }

    /**
     * No-arg constructor
     * */
    public Loan() {}

    public Loan(Double value, Double totalInterestRate, Timestamp expiryDate, Account account, Customer customer) {
        setValue(value);
        setTotalInterestRate(totalInterestRate);
        setExpiryDate(expiryDate);
        setCreationDate(dateToTimestamp(new Date()));

        this.account = account;
        this.customer = customer;
    }

    public int getLoanId() {
        return loanId;
    }

    public void setLoanId(int loanId) {
        this.loanId = loanId;
    }

    public Double getValue() {
        return value;
    }

    public void setValue(Double value) {
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

    public Double getTotalInterestRate() {
        return totalInterestRate;
    }

    public void setTotalInterestRate(Double totalInterestRate) {
        this.totalInterestRate = totalInterestRate;
    }

    public Timestamp getExpiryDate() {
        return expiryDate;
    }

    public void setExpiryDate(Timestamp expiryDate) {
        this.expiryDate = expiryDate;
    }

    @Override
    public String toString() {
        return String.format("""
                
                Loan ID:        %d
                Owner:          %s %s %s
                Owner ID:       %d
                Value:          $%.2f
                Borrow Date:    %s
                Deadline:       %s
                Total Interest: %.4f%%
                Account ID:     %d
                """,
                getLoanId(),
                customer.getFirstName(),
                customer.getMiddleName(),
                customer.getLastName(),
                customer.getCustomerId(),
                getValue(),
                getCreationDate().toString(),
                getExpiryDate().toString(),
                getTotalInterestRate(),
                account.getAccountId()
        );
    }
}
