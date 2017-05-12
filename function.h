//
//  function.h
//  OL12P
//
//  Created by Louise Naudin on 11/05/2017.
//  Copyright © 2017 LNA. All rights reserved.
//

#ifndef function_h
#define function_h


const TIME::Date currentDate() {
    time_t theTime = time(NULL);
    struct tm *aTime = localtime(&theTime);
    TIME::Date t0(aTime->tm_mday,aTime->tm_mon + 1,aTime->tm_year + 1900);
    return t0;
}


#endif /* function_h */
