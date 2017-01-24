#ifndef CLIENT_H
#define CLIENT_H

int TURN_MENU_OPTIONS = 3;

int connect_to_server();

void select_username();

void create_status_memory();

void access_status_memory();

void communication_manager();

int check_username();

void print_turn_options();

void print_locations();

int is_valid_menu_selection(char buffer[]);

void execute_turn_selection(int selection);

#endif

