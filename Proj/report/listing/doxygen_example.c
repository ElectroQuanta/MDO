/**
 * @file App.c
 * @author Jose Pires
 * @date 12 Jan 2019
 *
 * @brief App's module implementation
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <strings.h>
#include "App.h"
#include "list.h"
#include "User.h"
#include "Activity.h"
#include "Menu.h"
#include "Pack.h"
#include "Database.h"
#include "m-utils.h"

/* Menus titles */
#define MENU_LOGIN "LOGIN" /**< Menu title for Login state */
#define MENU_GERENTE "GERENTE" /**< Menu title for Gerente state */
#define MENU_FUNC "FUNCIONARIO" /**< Menu title for Func state */
#define MENU_CLIENTE "CLIENTE" /**< Menu title for Client state */ 
#define MENU_MANAGE_CLI "GERIR CLIENTE" /**< Menu title for ManageClient state */ 
#define MENU_MANAGE_ACT "GERIR ACTIVIDADE" /**< Menu title for ManageActivity state */ 
#define MENU_MANAGE_PACK "GERIR PACK" /**< Menu title for Manage Pack state */ 
#define MENU_EDIT_USER "EDITAR UTILIZADOR" /**< Menu title for Edit User state */ 
#define MENU_EDIT_ACT "EDITAR ACTIVIDADE" /**< Menu title for Edit Activity state */ 
#define MENU_SEARCH_ACT "PROCURAR ACTIVIDADE" /**< Menu title for search Activity state */ 
#define MENU_EDIT_PACK "EDITAR PACK" /**< Menu title for Edit Pack state */ 
#define MENU_ACTIV "ACTIVIDADES" /**< Menu title for Client Activities state */ 

/* Database files */
#define DATABASE_USERS "user.db" /**< Database file for users */
#define DATABASE_ACTIVITIES "act.db" /**< Database file for activities */  
#define DATABASE_PACKS "pack.db" /**< Database file for packs */

/**
 * @brief Constants for the App's states. Used in FSM management.
 */
enum App_state{
    S_Login, /**< Login state */
    S_Gerente, /**< Manager state */
    S_Func,/**< Employee state */
    S_Cliente,/**< Client state */
    S_Manage_Cli,/**< Manage Client state */
    S_Manage_Act,/**< Manage Activity state */
    S_Manage_Pack,/**< Manage Pack state */
    S_Edit_User,/**< Edit User state */
    S_Edit_Act,/**< Edit Activity state */
    S_Edit_Pack,/**< Edit Pack state */
    S_Activities,/**< Client Activities state */
    S_Logout,/**< Logout state */
    S_Quit/**< Quit state */
};

/**
 * @brief App's struct: contains the relevant data members
 */
struct App_T
{
    List_T menus; /**< Menus list */
    List_T users;  /**< Users list */
    List_T activities; /**< Activities list */
    List_T packs; /**< List of available packs */
    User_T cur_user; /**< Current user */
    enum App_state state; /**< App's current state */
    enum App_state prev_state; /**< App's previous state */
    void * userdata; /**< ptr to generic data (used in App_state_functions) */
    Database_T db_user; /**< Users database */
    Database_T db_act; /**< Activities database */
    Database_T db_pack; /**< Packs database */
};

/**
 * @brief Allocates memory for an App's instance
 * @return initialized memory for App
 *
 * It is checked by assert to determine if memory was allocated.
 * If assertion is valid, returns a valid memory address
 */
static App_T App_new()
{
    App_T app = malloc(sizeof(*app));
    assert(app);
    return app;
}
