#include "data/schemas/user.h"

#include <glib.h>
#include <stdint.h>

#include "data/catalogs/catalog_user.h"
#include "data/schemas/schema_data_types.h"
#include "data/schemas/validation/generic_validation.h"
#include "data/schemas/validation/user_validation.h"
#include "io/parsing/reader.h"

struct user {
  char* id;
  char* name;
  char* email;
  char* phone_number;
  Timestamp birth_date;
  Sex sex;
  char* passport;
  char* country_code;
  char* address;
  Timestamp account_creation;
  PayMethod pay_method;
  AccountStatus account_status;
};

User* create_user(char* id, char* name, char* email, char* phone_number,
                  Timestamp birth_date, Sex sex, char* passport,
                  char* country_code, char* address, Timestamp account_creation,
                  PayMethod pay_method, AccountStatus account_status) {
  User* user = initialize_user();

  user_set_id(user, id);
  user_set_name(user, name);
  user_set_birth_date(user, birth_date);
  user_set_sex(user, sex);
  user_set_passport(user, passport);
  user_set_country_code(user, country_code);
  user_set_account_creation(user, account_creation);
  user_set_account_status(user, account_status);

  return user;
}

User* initialize_user() {
  User* user = malloc(sizeof(struct user));
  user->id = NULL;
  user->name = NULL;
  user->email = NULL;
  user->phone_number = NULL;
  user->passport = NULL;
  user->country_code = NULL;
  user->address = NULL;

  return user;
}

void free_user(void* user_ptr) {
  User* user = (User*)user_ptr;
  g_free(user->id);
  g_free(user->name);
  g_free(user->email);
  g_free(user->phone_number);
  g_free(user->passport);
  g_free(user->country_code);
  g_free(user->address);
  free(user);
}

int parse_user_and_add_to_catalog(RowReader* reader, void* catalog,
                                  void* database) {
  char* user_id = reader_next_cell(reader);
  if (is_empty_value(user_id)) return 1;

  char* user_name = reader_next_cell(reader);
  if (is_empty_value(user_name)) return 1;

  char* user_email = reader_next_cell(reader);
  if (invalid_email(user_email)) return 1;

  char* user_phone_number = reader_next_cell(reader);
  if (is_empty_value(user_phone_number)) return 1;

  char* user_birth_date_string = reader_next_cell(reader);
  if (invalid_date(user_birth_date_string)) return 1;
  Timestamp user_birth_date = parse_date(user_birth_date_string);

  char* user_sex_string = reader_next_cell(reader);
  if (is_empty_value(user_sex_string)) return 1;
  Sex user_sex = parse_sex(user_sex_string);

  char* user_passport = reader_next_cell(reader);
  if (is_empty_value(user_passport)) return 1;

  char* user_country_code = reader_next_cell(reader);
  if (invalid_value_length(2, user_country_code)) return 1;

  char* user_address = reader_next_cell(reader);
  if (is_empty_value(user_address)) return 1;

  char* user_account_creation_string = reader_next_cell(reader);
  if (invalid_timestamp(user_account_creation_string)) return 1;
  Timestamp user_account_creation =
      parse_timestamp(user_account_creation_string);

  if (user_birth_date.date >= user_account_creation.date) return 1;

  char* user_pay_method_string = reader_next_cell(reader);
  if (is_empty_value(user_pay_method_string)) return 1;
  PayMethod user_pay_method = parse_payment_method(user_pay_method_string);

  char* user_account_status_string = reader_next_cell(reader);
  if (invalid_account_status(user_account_status_string)) return 1;

  AccountStatus user_account_status =
      parse_account_status(user_account_status_string);

  char* user_key = g_strdup(user_id);

  User* user = create_user(
      user_id, user_name, user_email, user_phone_number, user_birth_date,
      user_sex, user_passport, user_country_code, user_address,
      user_account_creation, user_pay_method, user_account_status);

  insert_user(catalog, user, user_key);

  return 0;
}

char* user_get_id(User* user) { return g_strdup(user->id); }

void user_set_id(User* user, char* id) { user->id = g_strdup(id); }

char* user_get_name(User* user) { return g_strdup(user->name); }

void user_set_name(User* user, char* name) { user->name = g_strdup(name); }

char* user_get_email(User* user) { return g_strdup(user->email); }

void user_set_email(User* user, char* email) { user->email = g_strdup(email); }

char* user_get_phone_number(User* user) { return g_strdup(user->phone_number); }

void user_set_phone_number(User* user, char* phone_number) {
  user->phone_number = g_strdup(phone_number);
}

Timestamp user_get_birth_date(User* user) { return user->birth_date; }

void user_set_birth_date(User* user, Timestamp birth_date) {
  user->birth_date = birth_date;
}

Sex user_get_sex(User* user) { return user->sex; }

void user_set_sex(User* user, Sex sex) { user->sex = sex; }

char* user_get_passport(User* user) { return g_strdup(user->passport); }

void user_set_passport(User* user, char* passport) {
  user->passport = g_strdup(passport);
}

char* user_get_country_code(User* user) { return g_strdup(user->country_code); }

void user_set_country_code(User* user, char* country_code) {
  user->country_code = g_strdup(country_code);
}

char* user_get_address(User* user) { return g_strdup(user->address); }

void user_set_address(User* user, char* address) {
  user->address = g_strdup(address);
}

Timestamp user_get_account_creation(User* user) {
  return user->account_creation;
}

void user_set_account_creation(User* user, Timestamp account_creation) {
  user->account_creation = account_creation;
}

PayMethod user_get_pay_method(User* user) { return user->pay_method; }

void user_set_pay_method(User* user, PayMethod pay_method) {
  user->pay_method = pay_method;
}

AccountStatus user_get_account_status(User* user) {
  return user->account_status;
}

void user_set_account_status(User* user, AccountStatus account_status) {
  user->account_status = account_status;
}