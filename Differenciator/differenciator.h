#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include "tree.h"

#define MAXLEXEM 100


//---------------------------------------------------------------------
//! Takes a deriative from tree
//!
//! @param[in] pnode pointer to tree
//!
//! @return pointer to tree
//---------------------------------------------------------------------

Node* Deriative(Node* pnode);
