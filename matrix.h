void print_matrix(double **matrix, int row, int col);
void exchange_row(double **matrix, int a, int b, int col);
void gaussian_eliminate(double **matrix, int row, int col, double **lower, double **upper, double **P);
void create_identity_matrix(double **matrix, int row, int col);
double *gaussian_solve(double **matrix, double *b, int row, int col);
void qr(double **A, double **Q, double **R, int row, int col);
double **get_transposed(double **x, int n, int m);
double **at_times_a(double **at, double **a, int n, int m);
double *at_times_b(double **at, double *b, int row, int col);
