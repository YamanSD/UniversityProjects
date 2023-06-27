package com.example.demo;

import org.springframework.data.repository.CrudRepository;

import java.util.List;
import java.util.Optional;

/**
 * Spring Boot repository for the Account entities.
 * */
public interface AccountRepository extends CrudRepository<Account, Integer> {
    Optional<Account> findByAccountIdAndPassword(int id, String password);

    List<Account> findAllByCustomer(Customer customer);

    int countAllByCustomer(Customer customer);
}
