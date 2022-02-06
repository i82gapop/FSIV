#pragma once
#include <string>

#ifdef NDEBUG
#define DEBUG(l, x) while(0){};
#else
#include <iostream>
#include <iomanip>
extern const std::string __Debug_Padding;
extern size_t __Debug_PPL; //Pad per level.
extern int __Debug_Level;

#define DEBUG(l, x) {if (l <= __Debug_Level) std::cerr << '[' << std::setw(3) << l << "] " << __Debug_Padding.substr(0, __Debug_PPL*size_t(std::max(0, (l-1)))) << x;}
#endif

/**
 * @brief Decode a string like "RxC" to set a grid shape.
 * @param[in] str is the string coding the grid shape.
 * @param[out] n_cells a vector with rows and cols.
 * @return True if success.
 */
bool string_to_ncells(const std::string& str, int n_cells[]);
