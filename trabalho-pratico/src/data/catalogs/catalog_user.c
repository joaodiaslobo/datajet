#include "data/catalogs/catalog_user.h"

#include "data/schemas/user.h"

struct catalogUser {
  GHashTable *users;
};

CatalogUser *initialize_users_catalog() {
  CatalogUser *catalog = malloc(sizeof(struct catalogUser));
  catalog->users =
      g_hash_table_new_full(g_str_hash, g_strcmp0, NULL, free_user);

  return catalog;
}

void free_users_catalog(CatalogUser *catalog) {
  g_hash_table_destroy(catalog->users);

  free(catalog);
}

void insert_user(CatalogUser *catalog, User *user, char *key) {
  g_hash_table_insert(catalog->users, key, user);
}

int count_users(CatalogUser *catalog) {
  return g_hash_table_size(catalog->users);
}

bool user_exists(CatalogUser *catalog, char *user_id) {
  return g_hash_table_contains(catalog->users, user_id);
}

User *catalog_get_user_by_id(CatalogUser *catalog, char *user_id) {
  return g_hash_table_lookup(catalog->users, user_id);
}

User *catalog_get_user_by_name(CatalogUser *catalog, char *user_name) {
  return g_hash_table_lookup(catalog->users, user_name);
}
