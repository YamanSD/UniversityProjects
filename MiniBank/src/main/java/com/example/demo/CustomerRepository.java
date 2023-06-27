package com.example.demo;

import org.springframework.data.jpa.repository.Query;
import org.springframework.data.repository.CrudRepository;

import java.util.List;
import java.util.Optional;

/**
 * Spring Boot repository for the Customer entities.
 * */
public interface CustomerRepository extends CrudRepository<Customer, Integer> {
    Optional<Customer> findByCustomerId(int id);

    Optional<Customer> findByFirstNameAndMiddleNameAndLastName(String firstName, String middleName, String lastName);

    Optional<Customer> findBySsn(String ssn);

    Optional<Customer> findByPhoneNumber(String phone);

    @Query("SELECT new Customer(c.customerId, c.firstName, c.middleName, c.lastName) " +
            "FROM Customer as c")
    List<Customer> getAllWithNameOnly();

    boolean existsByFirstNameAndMiddleNameAndLastName(String firstName, String middleName,
                                                      String lastName);

    boolean existsByPhoneNumber(String phone);

    int countBySsn(String ssn);
}
