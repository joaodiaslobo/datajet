#include "data/catalogs/catalog_user.h"

#include "data/schemas/user.h"

struct catalogUser {
  GPtrArray *users;
};

CatalogUser *initialize_users_catalog() {
  CatalogUser *catalog = malloc(sizeof(struct catalogUser));
  catalog->users = g_ptr_array_new_with_free_func(free_user);

  return catalog;
}

void free_users_catalog(CatalogUser *catalog) {
  g_ptr_array_free(catalog->users, TRUE);

  free(catalog);
}

void insert_user(CatalogUser *catalog, User *user) {
  g_ptr_array_add(catalog->users, user);
}

int count_users(CatalogUser *catalog) { return catalog->users->len; }

User *catalog_get_user_by_id(CatalogUser *catalog, int user_id) {
  return (User *)catalog->users->pdata[user_id];
}