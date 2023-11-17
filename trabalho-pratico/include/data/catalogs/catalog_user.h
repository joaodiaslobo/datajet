#ifndef CATALOG_USER_H
#define CATALOG_USER_H

#include <glib.h>

#include "data/schemas/user.h"

typedef struct catalogUser CatalogUser;

CatalogUser *initialize_users_catalog();

void free_users_catalog(CatalogUser *catalog);

void insert_user(CatalogUser *catalog, User *user, char *key);

int count_users(CatalogUser *catalog);

bool user_exists(CatalogUser *catalog, char *user_id);

User *catalog_get_user_by_id(CatalogUser *catalog, char *user_id);

User *catalog_get_user_by_name(CatalogUser *catalog, char *user_name);

GPtrArray *get_users(CatalogUser *catalog);

int compare_users_array_elements_by_name(gpointer a, gpointer b);

#endif