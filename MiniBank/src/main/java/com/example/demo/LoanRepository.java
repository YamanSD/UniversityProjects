package com.example.demo;

import org.springframework.data.repository.CrudRepository;

import java.util.List;
import java.util.Optional;

/**
 * Spring Boot repository for the Loan entities.
 * */
public interface LoanRepository extends CrudRepository<Loan, Integer> {
    Optional<Loan> findByLoanId(int id);

    List<Loan> findAllByAccount(Account account);

    List<Loan> findAllByCustomer(Customer customer);

    List<Loan> findAllByCustomerAndAccount(Customer customer, Account account);

    int countAllByCustomer(Customer customer);

    int countAllByAccount(Account account);

    int countAllByCustomerAndAccount(Customer customer, Account account);

    boolean existsByLoanId(int loanId);
}
