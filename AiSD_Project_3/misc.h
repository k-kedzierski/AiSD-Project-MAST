//
//  misc.h
//  AiSD_Project_3
//
//  Created by Kacper Kędzierski on 01/05/2020.
//  Copyright © 2020 Kacper Kędzierski. All rights reserved.
//

#ifndef misc_h
#define misc_h

#define UNDEFINED -1

#ifdef _DEBUG
  #define _DEBUG_PRINTF(...) fprintf(stderr, __VA_ARGS__ );
#else
  #define _DEBUG_PRINTF(...)
#endif

#endif /* misc_h */
