#ifndef PROJECTL2_SET_H
#define PROJECTL2_SET_H

typedef struct s_d_cell
{
    int value;
    struct s_d_cell **nexts;
} t_d_cell;

typedef struct s_d_list
{
    t_d_cell** heads;
    int max_level;
    int nElement;
    int n;
    int* nLevelArray;
} t_d_list;

t_d_list createEmptyList(int max_level);

t_d_cell* createEmptyCell(int value, int nLevels);

void insert(t_d_list *list, int value);

void setLevel(t_d_list* list);

#endif //PROJECTL2_SET_H