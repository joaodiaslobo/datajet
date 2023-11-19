/**
 * @file batch.h
 * @brief Responsible for triggering batch mode logic such as populating the
 * database and executing the commands.
 */

#ifndef BATCH_H
#define BATCH_H

#include "data/database.h"

/**
 * @brief Batch worker logic
 * @details Responsible for triggering batch mode logic such as populating the
 * database and executing the commands.
 *
 * @param argv Arguments given to the program on startup.
 * @param database Main database.
 * @return 0 if the execution succeeded.
 */
int batch_worker(char **argv, Database *database);

#endif