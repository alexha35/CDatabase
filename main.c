#include <stdio.h>
#include <stdlib.h>

/* Hold the structure of a contact */
typedef struct record
{
	char phone[20];
	char firstName[20];
	char lastName[20];
} record_t;

/* Hold the information of a database */
typedef struct database
{
	record_t *records;
	record_t *last_record;
	int num_records;
	int max_records;
	int num_changes;
} database_t;

/* Display a menu for the user */
void display_menu()
{
	printf("MENU\n");
	printf("====\n");
	printf("1. Print all records\n");
	printf("2. Print number of records\n");
	printf("3. Print size of database\n");
	printf("4. Add record\n");
	printf("5. Delete record\n");
	printf("6. Print number of accesses to database (number of changes)\n");
	printf("7. Exit\n");
}

/* Initialize the database storage */
database_t *init_database()
{
	database_t *records_db;

	/* Prepare a 20 records slots for storing contacts */
	records_db = malloc(sizeof(database_t));
	records_db->max_records = 20;
	records_db->records = malloc(sizeof(record_t) * records_db->max_records);
	records_db->num_records = 0;
	records_db->num_changes = 0;

	return records_db;
}

/* Delete the memory used by the database */
void delete_database(database_t *records_db)
{
	free(records_db->records);
	free(records_db);
}

/* Display all records */
void print_records(database_t *records_db)
{
	int i;
	record_t *current_record;

	printf("%-15s%-25s%-25s\n", "Phone", "First Name", "Last Name");
	printf("%-15s%-25s%-25s\n", "-----", "----------", "---------");

	current_record = records_db->records;

	for (i = 0; i < records_db->num_records; i++)
	{
		printf("%-15s%-25s%-25s\n",
			current_record->phone,
			current_record->firstName,
			current_record->lastName);
		current_record++;
	}
}

/* Double the size of the of the database records */
void expand_database(database_t *records_db)
{
	record_t *new_records;
	record_t *current_record;

	int i;
	int new_max_records;

	new_max_records = records_db->max_records * 2;
	new_records = malloc(sizeof(record_t) * new_max_records);

	/* Copy the values from the old records to the new records */
	current_record = records_db->records;

	for (i = 0; i < records_db->num_records; i++)
		*new_records = *current_record;

	/* Delete the old records and replace it with a new one */
	free(records_db->records);
	records_db->records = new_records;
	records_db->max_records = new_max_records;
	records_db->num_changes++;
}

/* Add a new record to the database */
void add_record(database_t *records_db)
{
	record_t *current_record;
	int i;

	/* Expand database storage capacity if */
	if (records_db->num_records >= records_db->max_records)
		expand_database(records_db);

	/* Get the last record where to put the new entry */
	current_record = records_db->records;

	for (i = 0; i < records_db->num_records; i++)
		current_record++;

	/* Okay we can now enter record details */
	printf("Enter Phone Number: ");
	scanf("%s", current_record->phone);

	printf("Enter First Name: ");
	scanf("%s", current_record->firstName);

	printf("Enter Last Name: ");
	scanf("%s", current_record->lastName);

	records_db->num_records++;
	records_db->num_changes++;

	printf("New record added.");
}

/* Delete the last record from the database */
void delete_record(database_t *records_db)
{
	if (records_db->num_records == 0)
	{
		printf("There are no records to delete.\n");
		return;
	}

	records_db->num_records--;
	printf("Last record deleted.");
}

/* Entry point of the program */
int main()
{
	int option;
	database_t *records_db;

	/* Initialize the database we will use to store records */
	records_db = init_database();

	do
	{
		/* Ask the user what to do */
		display_menu();
		printf("Option: ");
		scanf("%d", &option);

		/* Execute the appropriate user option */
		if (option == 1)
			print_records(records_db);
		else if (option == 2)
			printf("Number of Records: %d\n", records_db->num_records);
		else if (option == 3)
			printf("Size of Database: %lu bytes\n", sizeof(record_t) * records_db->num_records);
		else if (option == 4)
			add_record(records_db);
		else if (option == 5)
			delete_record(records_db);
		else if (option == 6)
			printf("Database Number of Changes: %d\n", records_db->num_changes);

		printf("\n");
	} while(option != 7);

	/* Free used memory */
	delete_database(records_db);

	return 0;
}
