#ifndef CATALOG_USER_H
#define CATALOG_USER_H

#include <glib.h>

#include "data/schemas/user.h"

typedef struct catalogUser CatalogUser;

/**
 * @brief Initialize a catalog for managing users
 * @details Allocates memory for a new CatalogUser structure, initializes its
 * internal hash table for mapping user IDs to users, and initializes a GPtrArray
 * to store user pointers in insertion order. Returns a pointer to the created catalog.
 *
 * @return A pointer to the newly initialized CatalogUser structure.
 */
CatalogUser *initialize_users_catalog();

/**
 * @brief Free memory occupied by a CatalogUser structure
 * @details Destroys the internal hash table and frees the memory occupied by
 * the provided CatalogUser structure.
 *
 * @param catalog A pointer to the CatalogUser structure to be freed.
 */
void free_users_catalog(CatalogUser *catalog);

/**
 * @brief Insert a user into the user catalog
 * @details Inserts the provided user into the CatalogUser structure, associating
 * it with the specified key in the internal hash table. Additionally, adds the user
 * pointer to a GPtrArray to maintain insertion order.
 *
 * @param catalog A pointer to the CatalogUser structure.
 * @param user A pointer to the User structure to be inserted.
 * @param key The key to associate with the inserted user in the hash table.
 */
void insert_user(CatalogUser *catalog, User *user, char *key);

/**
 * @brief Get the total count of users in the user catalog
 * @details Returns the total count of users stored in the CatalogUser structure.
 *
 * @param catalog A pointer to the CatalogUser structure.
 * @return The total count of users in the user catalog.
 */
int count_users(CatalogUser *catalog);

/**
 * @brief Check if a user exists in the user catalog
 * @details Checks whether a user with the specified user ID exists in the
 * CatalogUser structure.
 *
 * @param catalog A pointer to the CatalogUser structure.
 * @param user_id The user ID to check for existence.
 * @return true if the user exists, false otherwise.
 */
bool user_exists(CatalogUser *catalog, char *user_id);

/**
 * @brief Retrieve a user by ID from the user catalog
 * @details Returns a pointer to the User structure associated with the specified
 * user ID in the CatalogUser structure.
 *
 * @param catalog A pointer to the CatalogUser structure.
 * @param user_id The ID of the user to retrieve.
 * @return A pointer to the User structure associated with the user ID,
 * or NULL if the user ID is not found.
 */
User *catalog_get_user_by_id(CatalogUser *catalog, char *user_id);

/**
 * @brief Retrieve a user by name from the user catalog
 * @details Returns a pointer to the User structure associated with the specified
 * user name in the CatalogUser structure.
 *
 * @param catalog A pointer to the CatalogUser structure.
 * @param user_name The name of the user to retrieve.
 * @return A pointer to the User structure associated with the user name,
 * or NULL if the user name is not found.
 */
User *catalog_get_user_by_name(CatalogUser *catalog, char *user_name);

/**
 * @brief Retrieve the list of users from the user catalog
 * @details Returns a pointer to the GPtrArray containing User pointers in insertion
 * order from the CatalogUser structure.
 *
 * @param catalog A pointer to the CatalogUser structure.
 * @return A pointer to the GPtrArray containing User pointers in insertion order.
 */
GPtrArray *get_users(CatalogUser *catalog);

/**
 * @brief Compare two user elements based on their names
 * @details Compares two user elements based on their names. If the names are equal,
 * the function further compares the user IDs. Returns a negative value if the name
 * of the first user is lexicographically less than the name of the second user,
 * a positive value if the name of the first user is lexicographically greater than
 * the name of the second user.
 *
 * @param a A pointer to the first User element.
 * @param b A pointer to the second User element.
 * @return A negative value if the name of the first user is lexicographically less than
 *         the name of the second user, a positive value if the name of the first user
 *         is lexicographically greater than the name of the second user.
 */
int compare_users_array_elements_by_name(gpointer a, gpointer b);

#endif