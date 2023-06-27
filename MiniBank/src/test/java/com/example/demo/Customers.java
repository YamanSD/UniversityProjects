package com.example.demo;

import jakarta.persistence.*;

import java.sql.Timestamp;

@Entity
@Table(name = "customers")
public class Customers {
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    @Id
    @Column(name = "customer_id", nullable = false)
    private int customerId;

    @Column(name = "first_name", nullable = false, length = 255)
    private String firstName;

    @Column(name = "middle_name", nullable = false, length = 255)
    private String middleName;

    @Column(name = "last_name", nullable = false, length = 255)
    private String lastName;

    @Column(name = "join_date", nullable = false)
    private Timestamp joinDate;

    @Column(name = "ssn", nullable = false, length = 9)
    private String ssn;

    @Column(name = "phone_number", nullable = false, length = 45)
    private String phoneNumber;

    @Column(name = "birth_day", nullable = false)
    private Timestamp birthDay;

    public int getCustomerId() {
        return customerId;
    }

    public void setCustomerId(int customerId) {
        this.customerId = customerId;
    }

    public String getFirstName() {
        return firstName;
    }

    public void setFirstName(String firstName) {
        this.firstName = firstName;
    }

    public String getMiddleName() {
        return middleName;
    }

    public void setMiddleName(String middleName) {
        this.middleName = middleName;
    }

    public String getLastName() {
        return lastName;
    }

    public void setLastName(String lastName) {
        this.lastName = lastName;
    }

    public Timestamp getJoinDate() {
        return joinDate;
    }

    public void setJoinDate(Timestamp joinDate) {
        this.joinDate = joinDate;
    }

    public String getSsn() {
        return ssn;
    }

    public void setSsn(String ssn) {
        this.ssn = ssn;
    }

    public String getPhoneNumber() {
        return phoneNumber;
    }

    public void setPhoneNumber(String phoneNumber) {
        this.phoneNumber = phoneNumber;
    }

    public Timestamp getBirthDay() {
        return birthDay;
    }

    public void setBirthDay(Timestamp birthDay) {
        this.birthDay = birthDay;
    }
}
