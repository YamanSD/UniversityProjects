package com.example.demo;

import org.springframework.boot.CommandLineRunner;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.annotation.Bean;

import java.sql.Timestamp;
import java.time.LocalDate;
import java.time.ZoneId;
import java.util.*;

@SpringBootApplication
public class DemoApplication {
	final LoanRepository loanRepository;
	final AccountRepository accountRepository;
	final CustomerRepository customerRepository;

	public static final Scanner input = new Scanner(System.in);

	public DemoApplication(LoanRepository loanRepository, AccountRepository accountRepository, CustomerRepository customerRepository) {
		this.loanRepository = loanRepository;
		this.accountRepository = accountRepository;
		this.customerRepository = customerRepository;
	}

	public void displaySeparator() {
		System.out.println("-".repeat(70));
	}

	public void displayInfo(String msg, boolean isWarn) {
		System.out.printf(
				"\n\033[%d;1;1m%s\033[0m\n",
				isWarn ? 31 : 33, // red or yellow, respectively
				msg
		);
	}

	public String get(String prompt) {
		System.out.printf("Enter \033[32;1;1m%s\033[0m: ", prompt);
		return input.nextLine();
	}

	public Integer getInt(String prompt, int lower, int upper) {
		if (upper == -1) {
			upper = Integer.MAX_VALUE;
		}

		while (true) {
			try {
				int response = Integer.parseInt(get(
						String.format("%s (%d to %d)",
								prompt,
								lower,
								upper
						)
				));

				if (lower <= response && response <= upper) {
					return response;
				}

				displayInfo(String.format(
						"""
						Invalid input.
						Must be between %d & %d.
						""",
						lower,
						upper
				), true);
			} catch (NumberFormatException ignored) {
				displayInfo(
						"""
						Invalid input.
						Must be an integer.
						""",
						true);
			}
		}
	}

	public Double getDouble(String prompt, double lower, double upper) {
		if (upper < 0) {
			upper = Double.MAX_VALUE;
		}

		final String nFormat = "%s (%.4f to %.4f)";
		final String tFormat = "%s (from %.4f)";

		while (true) {
			try {
				double response = Double.parseDouble(get(
						String.format(upper == Double.MAX_VALUE
										? tFormat : nFormat,
								prompt,
								lower,
								upper
						)
				));

				if (lower <= response && response <= upper) {
					return response;
				}

				displayInfo("""
						Invalid input.
						Must be within specified range.
						""", true);
			} catch (NumberFormatException ignored) {
				displayInfo(
						"""
						Invalid input.
						Must be a number.
						""",
						true);
			}
		}
	}

	public Integer getIntDomain(String prompt, Set<Integer> valid,
								String failPrompt) {
		while (true) {
			try {
				int response = Integer.parseInt(get(prompt));

				if (valid.contains(response)) {
					return response;
				}

				displayInfo(failPrompt, true);
			} catch (NumberFormatException ignored) {
				displayInfo("Invalid input must be an integer.",
						true);
			}
		}
	}

	public int displayMenu(Object[] options) {
		return displayMenu(options, true);
	}

	public int displayMenu(Object[] options, boolean numerate) {
		displaySeparator();

		for (int i = 0; i < options.length; i++) {
			if (numerate) {
				System.out.printf(
						"%d-\t\t%s\n",
						i + 1,
						options[i].toString()
				);
			} else {
				System.out.print(options[i]);
			}
		}

		// Display empty line
		System.out.println();

		return options.length;
	}

	public int displayMenu() {
		return displayMenu(new String[]{
				"Get Customer",
				"Get Account by ID",
				"Get Customer Accounts",
				"Get number of Accounts of a Customer",
				"Get Loans",
				"Get total borrowed by Customer",
				"Create new",
				"Deposit money into account",
				"Withdraw money from account",
				"Exit",
		});
	}

	public Optional<Customer> getCustomer() {
		int customerId = getInt("a customer ID", 0, -1);

		var customer = customerRepository.findById(customerId);

		if (customer.isEmpty()) {
			displayInfo("Customer does not exist", true);
		} else {
			displayInfo(customer.get().toString(), false);
		}

		return customer;
	}

	public Optional<Account> getAccount() {
		int accountId = getInt("an account ID", 0, -1);
		String password = get("account password");

		var account = accountRepository.findByAccountIdAndPassword(accountId, password);

		if (account.isEmpty()) {
			displayInfo("Invalid account ID or password", true);
		} else {
			displayInfo(account.get().toString(), false);
		}

		return account;
	}

	public void getCustomerAccounts() {
		var customer = getCustomer();

		if (customer.isPresent()) {
			var accounts = accountRepository.findAllByCustomer(customer.get());

			if (accounts.isEmpty()) {
				displayInfo("Customer has no accounts yet.", false);
			} else {
				for (var account: accounts) {
					displayInfo(account.toString(), false);
				}
			}
		}
	}

	public void getNumberOfAccounts() {
		var customer = getCustomer();

		if (customer.isPresent()) {
			int count = accountRepository.countAllByCustomer(customer.get());

			displayInfo(String.format(
     				"""
					Customer has %d account%s
					""",
					count,
					count == 1 ? "" : "s"
			), false);
		}
	}

	public void getLoans() {
		int numberOfOptions = displayMenu(new String[]{
				"Get Loans using Customer & Account",
				"Get Loans using Customer",
				"Get Loans using Account",
				"Get Loan using an ID",
		});

		int choice = getInt("an option number", 1, numberOfOptions);

		Optional<Customer> customer = Optional.empty();
		Optional<Account> account = Optional.empty();
		List<Loan> loans = null;

		if (choice == 4) {
			int loanId = getInt("a loan ID", 1, -1);

			var loan = loanRepository.findByLoanId(loanId);

			if (loan.isEmpty()) {
				displayInfo("Loan does not exist", true);
			} else {
				displayInfo(loan.get().toString(), false);
			}

			return;
		}

		switch (choice) {
			case 1:
				// Fall Through
			case 2:
				customer = getCustomer();

				if (customer.isEmpty()) {
					return;
				}

				if (choice == 2) {
					break;
				}
			case 3:
				account = getAccount();

				if (account.isEmpty()) {
					return;
				}
		}

		switch (choice) {
			case 1 ->
				loans = loanRepository.findAllByCustomerAndAccount(
						customer.get(),
						account.get()
				);

			case 2 ->
				loans = loanRepository.findAllByCustomer(customer.get());

			case 3 ->
				loans = loanRepository.findAllByAccount(account.get());
		}

		if (loans == null || loans.size() == 0) {
			displayInfo("No loans exist", false);
			return;
		}

		for (var loan: loans) {
			displayInfo(loan.toString(), false);
		}
	}

	public void getTotalBorrowed() {
		var customer = getCustomer();

		if (customer.isPresent()) {
			List<Loan> loans = loanRepository.findAllByCustomer(customer.get());

			if (loans.isEmpty()) {
				displayInfo("Customer has no loans.", false);
				return;
			}

			double total = 0;

			for (var loan: loans) {
				total += loan.getValue();
			}

			displayInfo(String.format(
     				"""
                     Customer has taken %d loan%s.
                     The total value of the loans is $%.2f""",
					loans.size(),
					loans.size() == 1 ? "" : "s",
					total
					), false
			);
		}
	}

	public Customer getCustomerFromList() {
		List<Customer> customers = customerRepository.getAllWithNameOnly();
		var customerEntries = new ArrayList<String>();

		for (var customer: customers) {
			customerEntries.add(String.format("%d-\t\t%s %s %s\n",
					customer.getCustomerId(),
					customer.getFirstName(),
					customer.getMiddleName(),
					customer.getLastName()
			));
		}

		int numberOfOptions = displayMenu(customerEntries.toArray(), false);
		int choice = getInt("a customer ID", 1, numberOfOptions);
		var result = customerRepository.findByCustomerId(choice);

		return result.orElse(null);

	}

	public Account getAccountFromList(Customer customer) {
		List<Account> accounts = accountRepository.findAllByCustomer(customer);

		if (accounts.isEmpty()) {
			displayInfo("Customer has no accounts!", true);
			return null;
		}

		var validEntries = new HashSet<Integer>();
		var accountsEntries = new ArrayList<String>();

		for (var account: accounts) {
			accountsEntries.add(String.format("ID: %d,\tCredit: $%.2f\n",
					account.getAccountId(),
					account.getCredit()
			));

			if (account.getActive()) {
				validEntries.add(account.getAccountId());
			}
		}

		displayMenu(accountsEntries.toArray(), false);
		int choice = getIntDomain("an account ID",
				validEntries,
				"Account is inactive or does not belong to the customer.");

		String password = get("account password");
		var result = accountRepository.findByAccountIdAndPassword(choice, password);

		return result.orElse(null);
	}

	public Timestamp getDate(String yearPrompt, String monthPrompt, String dayPrompt,
							 int yearLower, int yearUpper) {
		int year = getInt(yearPrompt, yearLower, yearUpper);
		int month = getInt(monthPrompt, 1, 12);

		var temp = LocalDate.of(year, month, 1);

		int day = getInt(dayPrompt, 1, temp.getMonth().length(temp.isLeapYear()));

		return Timestamp.from(LocalDate.of(year, month, day)
				.atStartOfDay().atZone(ZoneId.systemDefault()).toInstant());
	}

	public void create() {
		int numberOfOptions = displayMenu(new String[]{
				"Customer",
				"Account",
				"Loan"
		});

		int choice = getInt("an option number", 1, numberOfOptions);

		switch (choice) {
			case 1 -> {
				String firstName = get("customer first name");
				String middleName = get("customer middle name");
				String lastName = get("customer last name");

				String ssn = null;

				do {
					if (ssn != null) {
						displayInfo("SSN already in use!", true);
					}

					ssn = String.format("%09d",
							getInt("SSN", 0, 999_999_999)
					);
				} while (customerRepository.countBySsn(ssn) != 0);

				if (customerRepository.existsByFirstNameAndMiddleNameAndLastName(
						firstName, middleName, lastName)) {
					displayInfo("Customer already exists!", true);
					return;
				}

				String phoneNumber;
				while (true) {
					 phoneNumber = getInt("phone number", 10_000_000,
							99_999_999).toString();

					if (customerRepository.existsByPhoneNumber(phoneNumber)) {
						displayInfo("Phone number already in use", true);
					} else {
						break;
					}
				}

				var birthDay = getDate("year of birth",
						"month of birth",
						"day of birth",
						1971,
						LocalDate.now().getYear() - 15);

				Customer customer = new Customer(firstName, middleName, lastName,
						ssn, phoneNumber, birthDay);

				var newCustomer = customerRepository.save(customer);

				if (newCustomer.getCustomerId() != 0) {
					displayInfo("Customer created successfully!", false);
					displayInfo(newCustomer.toString(), false);
				} else {
					displayInfo("Customer creation failed!", true);
				}

			}
			case 2 -> {
				displayInfo(
						"Choose a Customer to create an account for: ",
						false
				);
				var customer = getCustomerFromList();
				String password;

				while (true) {
					password = get("account password");

					if (password.length() < 9) {
						displayInfo("Password length must be 9 at least!", true);
					} else {
						break;
					}
				}

				Account account = new Account(customer, password);

				var newAccount = accountRepository.save(account);

				if (newAccount.getAccountId() != 0) {
					displayInfo("Account created successfully!", false);
					displayInfo(newAccount.toString(), false);
				} else {
					displayInfo("Account creation failed!", true);
				}
			}
			case 3 -> {
				var customer = getCustomerFromList();

				if (customer.getCustomerId() == 0) {
					displayInfo("Invalid customer!", true);
					return;
				}

				var account = getAccountFromList(customer);

				if (account == null) {
					displayInfo("Invalid account operation canceled",
							true);
					return;
				} else if (account.getCredit() < 1000) {
					displayInfo("""
							Credit too low to take loan.
							Must have at least $1000.
							""", true);
					return;
				}

				double value = getDouble("loan value in USD", 0,
						account.getCredit() / 2);

				double interest = getDouble("overall interest", 0, 100);
				Timestamp expiry = getDate("expiry year",
						"expiry month",
						"expiry day",
						LocalDate.now().getYear(),
						LocalDate.now().getYear() + 30);

				Loan loan = new Loan(value, interest, expiry, account, customer);

				var newLoan = loanRepository.save(loan);

				if (newLoan.getLoanId() != 0) {
					displayInfo("Loan created successfully!", false);
					displayInfo(newLoan.toString(), false);
				} else {
					displayInfo("Loan creation failed!", true);
				}
			}
		}
	}

	public void deposit() {
		var account = getAccount();

		if (account.isPresent()) {
			double amount = getDouble("amount to deposit", 0, -1);
			account.get().deposit(amount);
			accountRepository.save(account.get());
			displayInfo("Deposit successful!", false);
		}
	}

	public void withdraw() {
		var account = getAccount();

		if (account.isPresent()) {
			if (account.get().getCredit() == 0) {
				displayInfo("Account has no deposits!", true);
				return;
			}

			double amount = getDouble("amount to withdraw", 0,
					account.get().getCredit().intValue());

			if (account.get().withdraw(amount)) {
				accountRepository.save(account.get());

				displayInfo("Withdraw successful!", false);
			} else {
				displayInfo("Withdraw failed!", true);
			}

		}
	}

	public boolean areYouSure() {
		System.out.println("\nAre you sure?");
		return get("Y or N").equalsIgnoreCase("y");
	}

	public static void main(String[] args) {
		SpringApplication.run(DemoApplication.class);
	}

	@Bean
	public CommandLineRunner start() {
		return (args) -> {
			int choice;

			do {
				 final int numberOfOptions = displayMenu();

				choice = getInt("an option number",1, numberOfOptions);

				// Use switch statement to call appropriate functions based on user's choice
				switch (choice) {
					case 1 -> getCustomer(); // Discard
					case 2 -> getAccount(); // Discard
					case 3 -> getCustomerAccounts();
					case 4 -> getNumberOfAccounts();
					case 5 -> getLoans();
					case 6 -> getTotalBorrowed();
					case 7 -> create();
					case 8 -> deposit();
					case 9 -> withdraw();
					case 10 -> {
						if (!areYouSure()) {
							choice++;
						}
					}
					default -> displayInfo("Invalid option key.", true);
				}
			} while (choice != 10);
		};
	}
}
