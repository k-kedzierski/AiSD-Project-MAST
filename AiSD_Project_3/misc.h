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

#define DEBUG

#ifdef DEBUG
  #define DEBUG_PRINTF(...) fprintf(stderr, __VA_ARGS__ );
#else
  #define DEBUG_PRINTF(...)
#endif

#endif /* misc_h */
