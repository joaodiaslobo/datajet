#include "data/catalogs/catalog_user.h"

#include "data/schemas/user.h"

struct catalogUser {
  GHashTable *users;
  GPtrArray *users_array;
};

CatalogUser *initialize_users_catalog() {
  CatalogUser *catalog = malloc(sizeof(struct catalogUser));
  catalog->users =
      g_hash_table_new_full(g_str_hash, g_strcmp0, NULL, free_user);
  catalog->users_array = g_ptr_array_new();

  return catalog;
}

void free_users_catalog(CatalogUser *catalog) {
  g_hash_table_destroy(catalog->users);
  g_ptr_array_free(catalog->users_array, TRUE);

  free(catalog);
}

void insert_user(CatalogUser *catalog, User *user, char *key) {
  g_hash_table_insert(catalog->users, key, user);
  g_ptr_array_add(catalog->users_array, user);
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

GPtrArray *get_users(CatalogUser *catalog) { return catalog->users_array; }

int compare_users_array_elements_by_name(gpointer a, gpointer b) {
  User *user_a = *(User **)a;
  User *user_b = *(User **)b;

  char *name_a = user_get_name(user_a);
  char *name_b = user_get_name(user_b);

  int comparison_result_name = strcoll(name_a, name_b);
  g_free(name_a);
  g_free(name_b);
  if (comparison_result_name == 0) {
    char *id_a = user_get_id(user_a);
    char *id_b = user_get_id(user_b);
    int comparison_result_id = strcoll(id_a, id_b);
    g_free(id_a);
    g_free(id_b);
    return comparison_result_id;
  }

  return comparison_result_name;
}
