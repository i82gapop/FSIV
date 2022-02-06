#include "debug.hpp"

#ifndef NDEBUG
#include<opencv2/highgui.hpp>
const std::string __Debug_Padding =
"                                                                              "
"                                                                              "
"                                                                              "
"                                                                              "
"                                                                              ";
size_t __Debug_PPL = 3;
#endif

bool
string_to_ncells(const std::string& str, int n_cells[])
{
    bool ret_val = true;
    std::istringstream input(str);
    char sep;
    input >> n_cells[0] >> sep >> n_cells[1];
    if (!input)
        ret_val = false;
    else
        ret_val = ((n_cells[0]*n_cells[1]) > 0);
    return ret_val;
}
