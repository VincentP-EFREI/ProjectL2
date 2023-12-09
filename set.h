#ifndef PROJECTL2_SET_H
#define PROJECTL2_SET_H

////Number Level List////
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
} t_d_list;

t_d_list createEmptyList(int max_level);
t_d_cell* createEmptyCell(int value, int nLevels);
void insert(t_d_list *list, int value);
int simpleSearch(t_d_list list, int val);
int levelSearch(t_d_list list, int val);
void displayList(t_d_list list);

#endif //PROJECTL2_SET_H