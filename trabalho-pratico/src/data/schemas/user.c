#include "data/schemas/schemas_utilities.h"

struct user {
  char* id;
  char* name;
  char* email;
  char* phone_number;
  Date birth_date;
  Sex sex;
  char* passport;
  char* contry_code;
  char* address;
  Date account_creation;
  PayMethod pay_method;
  AccountStatus account_status;
};