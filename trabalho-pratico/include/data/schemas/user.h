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
 * @brief Gets user's name.
 * @param user User.
 * @return User's name.
 */
char* user_get_name(User* user);

/**
 * @brief Gets user's email.
 * @param user User.
 * @return User's email.
 */
char* user_get_email(User* user);

/**
 * @brief Gets user's phone number.
 * @param user User.
 * @return User's phone number.
 */
char* user_get_phone_number(User* user);

/**
 * @brief Gets user's birth date.
 * @param user User.
 * @return User's birth date.
 */
Timestamp user_get_birth_date(User* user);

/**
 * @brief Gets user's sex.
 * @param user User.
 * @return User's sex.
 */
Sex user_get_sex(User* user);

/**
 * @brief Gets user's passport.
 * @param user User.
 * @return User's passport.
 */
char* user_get_passport(User* user);

/**
 * @brief Gets user's country code.
 * @param user User.
 * @return User's country code.
 */
char* user_get_country_code(User* user);

/**
 * @brief Gets user's address.
 * @param user User.
 * @return User's address.
 */
char* user_get_address(User* user);

/**
 * @brief Gets user's account creation time.
 * @param user User.
 * @return User's account creation time.
 */
Timestamp user_get_account_creation(User* user);

/**
 * @brief Gets user's pay method.
 * @param user User.
 * @return User's pay method.
 */
PayMethod user_get_pay_method(User* user);

/**
 * @brief Gets user's account status.
 * @param user User.
 * @return User's account status.
 */
AccountStatus user_get_account_status(User* user);

#endif