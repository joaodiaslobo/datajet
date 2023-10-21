#include "data/schemas/user.h"

#include <glib.h>
#include <stdint.h>

#include "data/schemas/schemas_utilities.h"

struct user {
  char* id;
  char* name;
  char* email;
  char* phone_number;
  Date birth_date;
  Sex sex;
  char* passport;
  char* country_code;
  char* address;
  Date account_creation;
  PayMethod pay_method;
  AccountStatus account_status;
};

User* create_user(char* id, char* name, char* email, char* phone_number,
                  Date birth_date, Sex sex, char* passport, char* country_code,
                  char* address, Date account_creation, PayMethod pay_method,
                  AccountStatus account_status) {
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

void free_user(User* user) {
  g_free(user->id);
  g_free(user->name);
  g_free(user->email);
  g_free(user->phone_number);
  g_free(user->passport);
  g_free(user->country_code);
  g_free(user->address);
  free(user);
}