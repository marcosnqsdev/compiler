void verify_principal();

void verify_inteiro();

void verify_decimal();

void verify_caractere();

void validate_variable(int type);

void check_data_length(int type);

void verify_funcao();

void check_func_name();

void check_parameters();

void check_expression();

void verify_escrita();

void verify_leia();

void exist_principal();

void verify_se();

void check_balance();

void check_finisher();

void check_aspas();

int exist_variable(char *word);

extern const char *reserved_words[];

extern char *file_array;

extern int char_index;

extern int char_count;

extern char *scope;

extern int scope_state;

extern int line_index;