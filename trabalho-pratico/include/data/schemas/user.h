/**
 * @file user.h
 * @brief User schema.
 */
#ifndef USER_H
#define USER_H

#include <stdint.h>

#include "data/schemas/schema_data_types.h"
#include "io/parsing/reader.h"

typedef struct user User;

/**
 * @brief Creates user.
 * @details Initializes user parameters, creating a new user.
 *
 * @param id User id.
 * @param name Name.
 * @param email Email.
 * @param phone_number Phone number.
 * @param birth_date Birth date.
 * @param sex Sex.
 * @param passport Passport.
 * @param country_code Country code.
 * @param address Address.
 * @param account_creation Account creation.
 * @param pay_method Pay method.
 * @param account_status Account status.
 * @return New user.
 */
User* create_user(char* id, char* name, char* email, char* phone_number,
                  Timestamp birth_date, Sex sex, char* passport,
                  char* country_code, char* address, Timestamp account_creation,
                  PayMethod pay_method, AccountStatus account_status);

/**
 * @brief Initializes user.
 * @return User.
 */
User* initialize_user();

/**
 * @brief Frees user.
 * @param user_ptr User pointer.
 */
void free_user(void* user_ptr);

/**
 * @brief Parses user and add to catalog.
 * @param reader Reader to be used to read the datasets.
 * @param catalog
 * @param database Main database.
 * @return 0 if the execution succeeded, 1 if it failed.
 */
int parse_user_and_add_to_catalog(RowReader* reader, void* catalog,
                                  void* database);

/**
 * @brief Gets user's id.
 * @param user User.
 * @return User's id.
 */
char* user_get_id(User* user);

/**
 * @brief Sets user's id.
 * @param user User.
 * @param id Id.
 */
void user_set_id(User* user, char* id);

/**
 * @brief Gets user's name.
 * @param user User.
 * @return User's name.
 */
char* user_get_name(User* user);

/**
 * @brief Sets user's name.
 * @param user User.
 * @param name Name.
 */
void user_set_name(User* user, char* name);

/**
 * @brief Gets user's email.
 * @param user User.
 * @return User's email.
 */
char* user_get_email(User* user);

/**
 * @brief Sets user's email.
 * @param user User.
 * @param email Email.
 */
void user_set_email(User* user, char* email);

/**
 * @brief Gets user's phone number.
 * @param user User.
 * @return User's phone number.
 */
char* user_get_phone_number(User* user);

/**
 * @brief Sets user's phone number.
 * @param user User.
 * @param phone_number Phone number.
 */
void user_set_phone_number(User* user, char* phone_number);

/**
 * @brief Gets user's birth date.
 * @param user User.
 * @return User's birth date.
 */
Timestamp user_get_birth_date(User* user);

/**
 * @brief Sets user's birth date.
 * @param user User.
 * @param birth_date Birth date.
 */
void user_set_birth_date(User* user, Timestamp birth_date);

/**
 * @brief Gets user's sex.
 * @param user User.
 * @return User's sex.
 */
Sex user_get_sex(User* user);

/**
 * @brief Sets user's sex.
 * @param user User.
 * @param sex Sex.
 */
void user_set_sex(User* user, Sex sex);

/**
 * @brief Gets user's passport.
 * @param user User.
 * @return User's passport.
 */
char* user_get_passport(User* user);

/**
 * @brief Sets user's passport.
 * @param user User.
 * @param passport Passport.
 */
void user_set_passport(User* user, char* passport);

/**
 * @brief Gets user's country code.
 * @param user User.
 * @return User's country code.
 */
char* user_get_country_code(User* user);

/**
 * @brief Sets user's country code.
 * @param user User.
 * @param country_code Country code.
 */
void user_set_country_code(User* user, char* country_code);

/**
 * @brief Gets user's address.
 * @param user User.
 * @return User's address.
 */
char* user_get_address(User* user);

/**
 * @brief Sets user's address.
 * @param user User.
 * @param address Address.
 */
void user_set_address(User* user, char* address);

/**
 * @brief Gets user's account creation time.
 * @param user User.
 * @return User's account creation time.
 */
Timestamp user_get_account_creation(User* user);

/**
 * @brief Sets user's account creation.
 * @param user User.
 * @param account_creation Account creation.
 */
void user_set_account_creation(User* user, Timestamp account_creation);

/**
 * @brief Gets user's pay method.
 * @param user User.
 * @return User's pay method.
 */
PayMethod user_get_pay_method(User* user);

/**
 * @brief Sets user's pay method.
 * @param user User.
 * @param pay_method Pay method.
 */
void user_set_pay_method(User* user, PayMethod pay_method);

/**
 * @brief Gets user's account status.
 * @param user User.
 * @return User's account status.
 */
AccountStatus user_get_account_status(User* user);

/**
 * @brief Sets user's account status.
 * @param user User.
 * @param account_status Account status.
 */
void user_set_account_status(User* user, AccountStatus account_status);

#endif