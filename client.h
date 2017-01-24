#ifndef CLIENT_H
#define CLIENT_H

int TURN_MENU_OPTIONS = 4;

int connect_to_server();

void select_username();

void create_status_memory();

void access_status_memory();

void communication_manager();

void send_status();

int check_username();

void print_turn_options();

void print_locations();

int is_valid_menu_selection(char buffer[]);

void execute_turn_selection(int selection, int sd);

void interrogate_player(int sd);

void guess_player(int sd);

#endif

