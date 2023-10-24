#ifndef CATALOG_USER_H
#define CATALOG_USER_H

#include <glib.h>

#include "data/schemas/user.h"

typedef struct catalogUser CatalogUser;

CatalogUser *initialize_users_catalog();

void free_users_catalog(CatalogUser *catalog);

void insert_user(CatalogUser *catalog, User *user);

int count_users(CatalogUser *catalog);

User *catalog_get_user_by_id(CatalogUser *catalog, int user_id);

#endif