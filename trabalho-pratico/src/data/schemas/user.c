#include "data/schemas/user.h"

#include <glib.h>
#include <stdint.h>

#include "data/catalogs/catalog_user.h"
#include "data/schemas/schema_data_types.h"
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
  User* user = malloc(sizeof(struct user));

  user->id = g_strdup(id);
  user->name = g_strdup(name);
  user->email = g_strdup(email);
  user->phone_number = g_strdup(phone_number);
  user->birth_date = birth_date;
  user->sex = sex;
  user->passport = g_strdup(passport);
  user->country_code = g_strdup(country_code);
  user->address = g_strdup(address);
  user->account_creation = account_creation;
  user->pay_method = pay_method;
  user->account_status = account_status;

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

int parse_user_and_add_to_catalog(RowReader* reader, void* catalog) {
  char* user_id = reader_next_cell(reader);
  char* user_name = reader_next_cell(reader);
  char* user_email = reader_next_cell(reader);
  char* user_phone_number = reader_next_cell(reader);
  Timestamp user_birth_date = parse_date(reader_next_cell(reader));
  Sex user_sex = parse_sex(reader_next_cell(reader));
  char* user_passport = reader_next_cell(reader);
  char* user_country_code = reader_next_cell(reader);
  char* user_address = reader_next_cell(reader);
  Timestamp user_account_creation = parse_timestamp(reader_next_cell(reader));
  PayMethod user_pay_method = parse_payment_method(reader_next_cell(reader));
  AccountStatus user_account_status =
      parse_account_status(reader_next_cell(reader));

  User* user = create_user(
      user_id, user_name, user_email, user_phone_number, user_birth_date,
      user_sex, user_passport, user_country_code, user_address,
      user_account_creation, user_pay_method, user_account_status);

  insert_user(catalog, user);

  return 0;
}

char* user_get_id(User* user) { return g_strdup(user->id); }

char* user_get_name(User* user) { return g_strdup(user->name); }

char* user_get_email(User* user) { return g_strdup(user->email); }

char* user_get_phone_number(User* user) { return g_strdup(user->phone_number); }

char* user_country_code(User* user) { return g_strdup(user->country_code); }